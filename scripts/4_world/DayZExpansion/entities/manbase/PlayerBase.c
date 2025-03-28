modded class PlayerBase
{
	bool m_WasDriverOfCarZen = false;

	int m_LastThermometerCheck;

	bool m_IsBanished = false;
	bool m_HasGpsLastCheck;
	int m_LastGpsCheck;
	float m_DamageCausedInSanctuary = 0;
	static const float MINIMUM_DMG_GUARD_ALERT = 6.0; // 3 light melee hits = aggro AND assault banishment

	private float m_CaveLaugherSoundDelta = 0;
	private EffectSound m_CaveLaughter;

#ifndef SERVER
	override void OnScheduledTick(float deltaTime)
	{
		super.OnScheduledTick(deltaTime);

		// Caves
		if (vector.Distance(GetPosition(), "7373.231445 4980.018555 2566.168701") <= 150)
		{
			m_CaveLaugherSoundDelta += deltaTime;
			if (m_CaveLaugherSoundDelta < 10) // 10% chance to play a laugh/cry sfx every 10 secs
				return;

			m_CaveLaugherSoundDelta = 0;

			if (Math.RandomFloat01() <= 0.1)
			{
				vector soundPos = ZenFunctions.GetRandomPointInCircle(GetPosition(), 50, 20, false);
				SEffectManager.PlaySound("Zen_QuestCaveLaughs_SoundSet", soundPos);
			}
		}
	}
#endif

	override static void Expansion_AddPlayer(PlayerBase player, PlayerIdentity identity)
	{
		if (!player)
			return;

		if (identity)
		{
			player.m_PlayerUID = identity.GetId();
			player.m_PlayerSteam = identity.GetPlainId();
			player.m_PlayerName = identity.GetName();

#ifdef SERVER
			if (player.m_charProfile)
				player.m_PlayerName = player.m_charProfile.m_name; // syberia name
			else
				Print("[ZenExpansionOverrides] !TODO: Char profile not loaded for Expansion_AddPlayer - need to do GetGame().CallQueue()?");
#endif
		}

		if (player.m_PlayerUID != "")
		{
			s_Expansion_AllPlayersUID.Set(player.m_PlayerUID, player);
			s_Expansion_AllPlayersUID2PlainID.Set(player.m_PlayerUID, player.m_PlayerSteam);
		}
	}

	override void OnVehicleSeatDriverEnter()
	{
		super.OnVehicleSeatDriverEnter();

		m_WasDriverOfCarZen = true;
	}

	override void OnVehicleSwitchSeat(int seatIndex)
	{
		super.OnVehicleSwitchSeat(seatIndex);

		if (seatIndex != 0)
			m_WasDriverOfCarZen = false;
		else 
			m_WasDriverOfCarZen = true;
	}

	void SetBanished(bool b)
	{
		m_IsBanished = b;
	}

	float GetDamageCausedInSanctuary()
	{
		return m_DamageCausedInSanctuary;
	}

	override bool HasItemGPS()
	{
		return Expansion_GetInventoryCount(ItemPDA) > 0 || Expansion_GetInventoryCount(GPSReceiver, true) > 0 || Expansion_GetInventoryCount(ExpansionGPS, true) > 0;
	}

	bool HasItemPDA()
	{
		ItemPDA pdaItem = ItemPDA.Cast(GetItemInHands());
        if (pdaItem && !pdaItem.IsRuined() && pdaItem.HasEnergyManager() && pdaItem.GetCompEM().CanWork())
			return true;

		pdaItem = ItemPDA.Cast(FindAttachmentBySlotName("Armband"));
        if (pdaItem && !pdaItem.IsRuined() && pdaItem.HasEnergyManager() && pdaItem.GetCompEM().CanWork())
            return true;

		return false;
	}

	// Super dodgy but I can't get regular GPS to work with expansion's way of tracking items in/out of inventory for some reason. Meh, it works.
	bool HasItemGPS_Zen()
	{
		if (HasItemPDA())
		{
			m_HasGpsLastCheck = true;
			return true;
		}

		ItemBase gpsItem = GetItemInHands();
        if (gpsItem && !gpsItem.IsRuined() && (gpsItem.IsInherited(GPSReceiver) || gpsItem.IsInherited(ItemPDA)))
        {
            if(gpsItem.GetCompEM() && gpsItem.GetCompEM().IsWorking())
			{
				m_HasGpsLastCheck = true;
				return true;
			}
        }

		// Check every 5 secs and 'cache' gps check because scanning inventory is apparently costly (read it somewhere in vanilla script files)
		// and so it may affect FPS slightly if called in a constant loop. Works just fine, it's only for the ingame map displaying our position anyway
		if (GetGame().GetTime() - m_LastGpsCheck < 5000)
			return m_HasGpsLastCheck;

		m_LastGpsCheck = GetGame().GetTime();
        array<EntityAI> itemsArray = new array<EntityAI>;
		GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
            	    
        for (int i = 0; i < itemsArray.Count(); i++)
		{
            if (itemsArray.Get(i) && (itemsArray.Get(i).IsInherited(GPSReceiver) || itemsArray.Get(i).IsInherited(ItemPDA)))
			{
				gpsItem = ItemBase.Cast(itemsArray.Get(i));

				if (gpsItem.IsInherited(ItemPDA) && gpsItem.HasEnergyManager() && gpsItem.GetCompEM().CanWork())
				{
					m_HasGpsLastCheck = true;
					return true;
				}

				if (!gpsItem.IsRuined() && gpsItem.GetCompEM() && gpsItem.GetCompEM().IsWorking())
				{
					m_HasGpsLastCheck = true;
					return true;
				}
            }
        }

		m_HasGpsLastCheck = false;
		return false;
	}

	ExpansionTerritoryModule ZenGetExpansionTerritoryModule()
	{
		return m_TerritoryModule;
	}

	override void SetActions(out TInputActionMap InputActionMap)
	{
		super.SetActions(InputActionMap);
		AddAction(ActionClimbOnBoat, InputActionMap);
		AddAction(ZenActionPauseGuitar, InputActionMap);
	}

	///////// START AI EXTRAS ////////
	//#ifdef ENFUSION_AI_PROJECT

	override void OnEnterZone(ExpansionZoneType type)
	{
		if (IsAI() && type == ExpansionZoneType.SAFE)
			return;

		super.OnEnterZone(type);
	}

	// Don't send notification when entering Expansion SafeZone
	override void OnEnterSafeZone()
	{
		//! Avoid exploit where you are just outside safezone, get shot uncon, fall backwards into safezone,
		//! then disconnect and reconnect to dupe your character
		//! (your other unconscious body will still be on the ground inside safezone due to having gained godmode from it)
		if (IsUnconscious() || IsGuardAggro())
			return;

		EXPrint(ToString() + "::OnEnterSafeZone");
		Print(m_Expansion_LeavingSafeZone);
		Print(m_Expansion_IsInSafeZone);
		Print(m_Expansion_IsInSafeZoneSynchRemote);

		m_Expansion_IsInSafeZone = true;
		m_Expansion_LeavingSafeZone = false;

		#ifdef SERVER
		m_Expansion_IsInSafeZoneSynchRemote = true;
		SetSynchDirty();
		#endif

		#ifdef ENFUSION_AI_PROJECT
		if (IsAI())
		{
			//! If this is AI, we still want it to be able to raise hands in safezones so it can reload its weapon
			return;
		}
		#endif

		SetCanRaise(false);

		if (GetGame().IsClient())
			return;

		/*if (IsRestrained())
		{
			SetRestrained(false);

			EntityAI item_in_hands = GetItemInHands();
			if (item_in_hands)
				MiscGameplayFunctions.TransformRestrainItem(item_in_hands, null, null, this);
		}*/
		
		if ( GetIdentity() )
		{
			//ExpansionNotification("STR_EXPANSION_SAFEZONE_TITLE", "STR_EXPANSION_SAFEZONE_ENTER", EXPANSION_NOTIFICATION_ICON_INFO, COLOR_EXPANSION_NOTIFICATION_AMETHYST).Create(GetIdentity());
			
			if ( GetExpansionSettings().GetLog().Safezone )
				GetExpansionSettings().GetLog().PrintLog("[Safezone] Player \"" + GetIdentity().GetName() + "\" (id=" + GetIdentity().GetId() + " pos=" + GetPosition() + ")" + " Entered the safezone" );
		}
	}

	override void OnExitZone(ExpansionZoneType type)
	{
#ifdef EXPANSIONTRACE
		auto trace = CF_Trace_0(ExpansionTracing.PLAYER, this, "OnExitZone");
#endif

		if (type == ExpansionZoneType.SAFE)
		{
			if (GetGame().IsClient())
			{
				// OnLeftSafeZone needs to be called on client
				OnLeftSafeZone();
				return;
			}

			m_Expansion_LeavingSafeZone = true;

			//if ( GetIdentity() )
			//	ExpansionNotification("STR_EXPANSION_SAFEZONE_TITLE", "STR_EXPANSION_SAFEZONE_LEAVING", EXPANSION_NOTIFICATION_ICON_INFO, COLOR_EXPANSION_NOTIFICATION_AMETHYST).Create(GetIdentity());
				
			//TODO: expose to settings

			//! Remove any previous call to OnLeftSafeZone from the queue
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(OnLeftSafeZone);

			//! Delay actually leaving the safezone by 10 seconds
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(OnLeftSafeZone, 10000, false);
		}
	}

	override void OnLeftSafeZone()
	{
#ifdef EXPANSIONTRACE
		auto trace = CF_Trace_0(ExpansionTracing.PLAYER, this, "OnLeftSafeZone");
#endif

		if (GetGame().IsClient())
		{
			m_Expansion_IsInSafeZone = false;
			SetCanRaise(true);
			return;
		}

		if (!m_Expansion_LeavingSafeZone)
			return;
		
		m_Expansion_LeavingSafeZone = false;

		m_Expansion_IsInSafeZone = false;

#ifdef SERVER
		m_Expansion_IsInSafeZoneSynchRemote = false;
		SetSynchDirty();
#endif

#ifdef ENFUSION_AI_PROJECT
		if (IsAI())
		{
			return;
		}
#endif

		SetCanRaise(true);
	
		if ( GetIdentity() )
		{
			//ExpansionNotification("STR_EXPANSION_SAFEZONE_TITLE", "STR_EXPANSION_SAFEZONE_LEFT", EXPANSION_NOTIFICATION_ICON_INFO, COLOR_EXPANSION_NOTIFICATION_AMETHYST).Create(GetIdentity());
	
			if ( GetExpansionSettings().GetLog().Safezone )
				GetExpansionSettings().GetLog().PrintLog("[Safezone] Player \"" + GetIdentity().GetName() + "\" (id=" + GetIdentity().GetId() + " pos=" + GetPosition() + ")" + " Left the safezone" );
		}
	}

	override bool Expansion_CanBeDamaged(string ammo = string.Empty)
	{
		bool canBeDamaged;

#ifdef SERVER
			canBeDamaged = GetAllowDamage();
#else
			canBeDamaged = m_Expansion_AllowDamage;
#endif

		return canBeDamaged && (!m_Expansion_IsInSafeZone || IsGuardAggro()) && !m_Expansion_DisabledAmmoDamage[ammo];
	}

	bool IsGuardAggro()
	{
		if (m_eAI_LastAggressionTimeout > 0)
			return true;

		return false;
	}

	override bool CanReceiveAttachment(EntityAI attachment, int slotId)
	{
		#ifdef EXPANSIONMODGROUPS
		if (attachment && (attachment.IsKindOf("Armband_ZenLoneWolf") || attachment.IsKindOf("Armband_ZenLoneWolfBlack")))
		{
			if (m_Expansion_PartyID != -1)
				return false;
		}
		#endif

		#ifndef SERVER
		// Don't allow players to wear this armband
		if (attachment.GetType().Contains("ZenYellowKing"))
			return false;
		#endif

		return super.CanReceiveAttachment(attachment, slotId);
	}

	override void Expansion_SetPartyPlayerData(ExpansionPartyPlayerData partyPlayerData)
	{
		super.Expansion_SetPartyPlayerData(partyPlayerData);

		if (m_Expansion_PartyID != -1)
		{
			// get armband slot, if it's a lone wolf armband, drop it!
			ItemBase lwab = ItemBase.Cast(FindAttachmentBySlotName("Armband"));
			if (lwab && (lwab.IsKindOf("Armband_ZenLoneWolf") || lwab.IsKindOf("Armband_ZenLoneWolfBlack"))) 
			{
				GetInventory().DropEntity(InventoryMode.SERVER, this, lwab);
			}
		}
	}

	override void SetCombatLogTimer(PlayerBase attacker = NULL, PlayerBase victim = NULL)
	{
		super.SetCombatLogTimer(attacker, victim);

		if (attacker != this)
			return;

		Zen_TriggerGuardAggro();
	}

	bool m_GunDamageRecordPaused = false;

	void ResetGunDamageRecordPaused()
	{
		m_GunDamageRecordPaused = false;
	}

	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

		if (vector.Distance(GetPosition(), "5647.100586 180.683914 10611.924805") > 300)
			return;

		if (!source || source == this || !damageResult)
			return;

		float damage = damageResult.GetDamage(dmgZone, "Health");
		if (damage <= 0)
			damage = damageResult.GetDamage(dmgZone, "Shock");

		if (damage <= 0)
			return;

		// If this player got hit by vehicle, attack driver
		CarScript vehicle = CarScript.Cast(source);
		if (vehicle)
		{
			PlayerBase driver = PlayerBase.Cast(vehicle.CrewMember(0));
			if (driver)
			{
				// Did we start shit? If so, don't penalize other player.
				if (DidWeStartCombatWith(driver))
					return;

				float speed = 0.0;

				Car car;
				if (Class.CastTo(car, vehicle))
					speed = car.GetSpeedometer();
				else
					speed = GetVelocity(vehicle).Length() * 3.6;

				if (speed > 1 && damage > 1)
				{
					driver.Zen_TriggerGuardAggro(150, damage);
				}

				return;
			}
		}

		PlayerBase aggressor = PlayerBase.Cast(source);
		if (!aggressor)
			aggressor = PlayerBase.Cast(source.GetHierarchyRootPlayer());

		if (!aggressor || aggressor.IsAI() || !aggressor.GetIdentity())
			return;

		ammo.ToLower();

		aggressor.m_DamageCausedInSanctuary += damage;
		if (aggressor.m_DamageCausedInSanctuary >= MINIMUM_DMG_GUARD_ALERT)
		{
			// Did we start shit? If so, don't penalize other player.
			if (DidWeStartCombatWith(aggressor))
				return;

			aggressor.Zen_TriggerGuardAggro(150, 3600);
			ZenModLogger.Log("Player " + aggressor.GetIdentity().GetName() + "(" + aggressor.GetIdentity().GetPlainId() + ") assaulted " + GetIdentity().GetName() + "(" + GetIdentity().GetPlainId() + ") at Sanctuary with " + ammo, "AngryGuards");

			// Check for melee first 
			if (ammo.Contains("melee"))
			{
				aggressor.InformPlayerOfBanishment(GetAngryGuardsConfig().SaveAngryGuardTimer(aggressor.GetIdentity().GetPlainId(), AngryGuardsConfig.OFFENSE_MELEE_ASSAULT));
			}
			else 
			// Check for grievous bodily harm
			if (ammo.Contains("bullet"))
			{
				if (!m_GunDamageRecordPaused)
				{
					m_GunDamageRecordPaused = true;
					GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(ResetGunDamageRecordPaused, 30000.0, false);
					aggressor.InformPlayerOfBanishment(GetAngryGuardsConfig().SaveAngryGuardTimer(aggressor.GetIdentity().GetPlainId(), AngryGuardsConfig.OFFENSE_GUN_ASSAULT));
				}
			}
			else 
			// Unknown cause but damage was done so banish them for assault 
			{
				aggressor.InformPlayerOfBanishment(GetAngryGuardsConfig().SaveAngryGuardTimer(aggressor.GetIdentity().GetPlainId(), AngryGuardsConfig.OFFENSE_MELEE_ASSAULT));
			}
		}
	}

	// We were killed by 'killer'
	override void EEKilled(Object killer)
	{
		super.EEKilled(killer);

		if (IsAI())
		{
			if (killer != NULL)
			{
				Grenade_Base grenade = Grenade_Base.Cast(killer);
				if (grenade != NULL)
				{
					// check unpinner
					if (grenade.GetZenUnpinPlayer() != NULL)
					{
						CheckAssignedObjectivesForEntity(grenade.GetZenUnpinPlayer());
					}
				}

				TrapBase trap = TrapBase.Cast(killer);
				if (trap != NULL)
				{
					// check unpinner
					if (trap.GetZenPlayerTrapper() != NULL)
					{
						CheckAssignedObjectivesForEntity(trap.GetZenPlayerTrapper());
					}
				}
			}

			// Don't check the rest for AI
			return;
		}

		if (vector.Distance(GetPosition(), "5647.100586 180.683914 10611.924805") > 300)
			return;

		if (!killer || killer == this)
			return;

		EntityAI murderer = EntityAI.Cast(killer);
		if (!murderer)
			return;

		PlayerBase player = PlayerBase.Cast(murderer);
		if (!player)
			player = PlayerBase.Cast(murderer.GetHierarchyRootPlayer());

		if (!player || !player.GetIdentity())
			return;

		// Did we start shit? If so, don't penalize other player.
		if (DidWeStartCombatWith(player))
			return;

		ZenModLogger.Log("Player " + player.GetIdentity().GetName() + "(" + player.GetIdentity().GetPlainId() + ") killed " + GetIdentity().GetName() + "(" + GetIdentity().GetPlainId() + ") at Sanctuary with " + killer.GetType(), "AngryGuards");
		player.InformPlayerOfBanishment(GetAngryGuardsConfig().SaveAngryGuardTimer(player.GetIdentity().GetPlainId(), AngryGuardsConfig.OFFENSE_MURDER));

		// Trigger nearby party members guard aggro
		/*if (player.Expansion_GetPartyID() != -1)
		{
			array<Man> players();
			GetGame().GetPlayers(players);
			foreach (Man man: players)
			{
				PlayerBase pb = PlayerBase.Cast(man);
				if (pb && vector.Distance(pb.GetPosition(), player.GetPosition()) < 200)
				{
					pb.Zen_TriggerGuardAggro(200, 10);
				}
			}
		}*/
	}

	bool IsSanctuaryBanished()
	{
		return m_IsBanished;
	}

	// Notify player
	string InformPlayerOfBanishment(NaughtyPlayer np)
	{
		int secsExpiry = np.BanishmentExpiry - JMDate.Now(false).GetTimestamp();
		string timeFormat = ExpansionStatic.GetTimeString(secsExpiry);
		string msg = "You are banished from Sanctuary for " + timeFormat + " for " + np.MostRecentOffense + "!";
		GetSyberiaRPC().SendToClient(SyberiaRPC.SYBRPC_SCREEN_MESSAGE, GetIdentity(), new Param1<string>(msg));
		return msg;
	}

	void Zen_TriggerGuardAggro(int distance = 150, float time = 3600.0)
	{
		if (vector.Distance(GetPosition(), "5647.100586 180.683914 10611.924805") > distance)
			return;

		// Trigger sanctuary guard timer!
		m_eAI_LastAggressionTime = ExpansionStatic.GetTime(true);
		m_eAI_LastAggressionTimeout = ExpansionStatic.GetTime(true);
		eAI_UpdateAgressionTimeout(time); // 1 hour
	}

	//#endif
	///// END AI EXTRAS /////

	////// DOG SAVING FOR LOGIN SCREEN! //////
	static string DOG_TYPE = "";

	override void EEItemAttached(EntityAI item, string slot_name)
	{
		super.EEItemAttached(item, slot_name);

		if (!GetGame().IsClient())
			return;

		if (!IsControlledPlayer())
			return;

		if (slot_name == "Dog")
			SaveDogForLogoutScreen();
	}

	override void EEItemDetached(EntityAI item, string slot_name)
	{
		super.EEItemDetached(item, slot_name);

		if (!GetGame().IsClient())
			return;

		if (!IsControlledPlayer())
			return;

		if (slot_name == "Dog")
			DOG_TYPE = "";
	};

	void SaveDogForLogoutScreen()
	{
		EntityAI dogslot = FindAttachmentBySlotName("Dog");
		if (!dogslot)
		{
			DOG_TYPE = "";
			return;
		};

		DOG_TYPE = dogslot.GetType();
	}

	override void OnPlayerLoaded()
	{
		super.OnPlayerLoaded();

		if (IsAI())
			return;

		// Server-side stuff
#ifdef SERVER
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(CheckLogoutTerritory, 10000.0, false);
#endif

		// Client-side stuff
		if (!GetGame().IsClient())
			return;

		if (!IsControlledPlayer())
			return;

		// Save dog for login screen
		GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater(SaveDogForLogoutScreen, 1000.0, false);
	}
	///// END DOG SAVING FOR LOGIN SCREEN! //////

	//! TERRITORY FLAG LOGIN 
	bool CheckLogoutTerritory()
	{
		if (!GetIdentity() || GetGame().IsClient())
			return false;

		float territorySize = GetExpansionSettings().GetTerritory().TerritorySize + 1;

		if (IsInTerritory() && !IsInsideOwnTerritory())
		{
			TerritoryFlag baseFlag = ZenFindNearestFlag(territorySize);
			if (!baseFlag)
				return false;

			float hitFraction, randomX, randomZ;
			vector hitPosition, hitNormal, to;
			Object hitObject;
			PhxInteractionLayers collisionLayerMask = PhxInteractionLayers.ITEM_LARGE | PhxInteractionLayers.BUILDING | PhxInteractionLayers.VEHICLE;
			vector playerPos = GetPosition();
			int distanceIncrease = 0;
			vector movePos = baseFlag.GetPosition();

			for (int i = 0; i < 100; i++)
			{
				// Calculate random position
				randomX = territorySize + Math.RandomFloatInclusive(1, 25 + distanceIncrease);
				randomZ = territorySize + Math.RandomFloatInclusive(1, 25 + distanceIncrease);
				distanceIncrease += 1; // Each loop, increase distance slightly in case we're in a zone with lots of objects/roofs around

				if (Math.RandomFloat01() <= 0.5)
					randomX = randomX * -1;

				if (Math.RandomFloat01() <= 0.5)
					randomZ = randomZ * -1;

				movePos[0] = movePos[0] + randomX;
				movePos[2] = movePos[2] + randomZ;
				movePos[1] = GetGame().SurfaceY(movePos[0], movePos[2]);
				to = movePos + "0 25 0";

				if (!DayZPhysics.RayCastBullet(movePos, to, collisionLayerMask, null, hitObject, hitPosition, hitNormal, hitFraction))
				{
					DeveloperTeleport.SetPlayerPosition(this, movePos);

					int liquidType;
					string surfaceType;
					GetGame().SurfaceUnderObject(this, surfaceType, liquidType);
					if (liquidType != LIQUID_WATER)
					{
						ZenModLogger.Log("Moved player out of territory: " + GetIdentity().GetName() + " (" + GetIdentity().GetPlainId() + ") - took " + i + " roof checks");
						ExpansionNotification(new StringLocaliser("BASE TERRITORY", "BASE TERRITORY"), "You have logged on inside a Territory you don't belong to and have been moved!").Error(GetIdentity());
						return true;
					}
				}
			}
		}

		return false;
	}

	TerritoryFlag ZenFindNearestFlag(float radius)
	{
		vector pos = GetPosition();
		array<Object> objects = new array<Object>;
		GetGame().GetObjectsAtPosition3D( pos, radius, objects, NULL );
		float distance;
		TerritoryFlag nearestFlag;
		
		if ( objects && objects.Count() > 0 )
		{
			for ( int i = 0; i < objects.Count(); ++i )
			{
				TerritoryFlag flag;
				if ( Class.CastTo( flag, objects.Get( i ) ) )
				{
					distance = vector.Distance( pos, flag.GetPosition() );
					if ( distance < radius && flag.GetTerritoryID() != -1 && flag.m_RefresherActive )
					{
						radius = distance;
						nearestFlag = flag;
					}
				}
			}
		}

		return nearestFlag;
	}

	protected int m_ShowZenExpansionMapTimer = 0;
	protected bool m_ShowZenExpansionMap = false;

	void SetZenToggleExpansionMap(bool setMapToggle)
	{
		m_ShowZenExpansionMap = setMapToggle;

		if (setMapToggle)
			m_ShowZenExpansionMapTimer = GetGame().GetTime() + 60000;
	}

	bool ZenToggleExpansionMap()
	{
		return m_ShowZenExpansionMap;
	}

	override bool HasItemMap()
	{
		return super.HasItemMap() || GetGame().GetTime() < m_ShowZenExpansionMapTimer;
	}

	override bool HasItemCompass()
	{
		return super.HasItemCompass() || GetGame().GetTime() < m_ShowZenExpansionMapTimer;
	}
}