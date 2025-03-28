modded class ExpansionAirdropContainerBase
{
	void ~ExpansionAirdropContainerBase()
	{
		ExpansionAirdropContainerManager manager = ExpansionAirdropContainerManagers.Find( this );
		if ( manager )
			manager.StopUpdateNoise();
	}

	override void CheckAirdrop()
	{
		#ifdef EXPANSION_MISSION_EVENT_DEBUG
		auto trace = EXTrace.Start(EXTrace.MISSIONS, this);
		#endif

		if ( IsMissionHost() && !m_IsLooted && IsEmpty() )
		{
			m_IsLooted = true;

			ToggleLight();

			// Don't stop zombie attraction noise upon looting
			//ExpansionAirdropContainerManager manager = ExpansionAirdropContainerManagers.Find( this );
			//if ( manager )
			//	manager.StopUpdateNoise();
		}
	}

    override void EEInit()
	{
		super.EEInit();

        if (!GetGame().IsDedicatedServer()) 
            return;

        vector position = GetPosition();
        if (position[0] <= 0 && position[1] <= 0 && position[2] <= 0) 
            return;

        // Notify players of airdrop release
        NotifyRadiosOfAirdropRelease(position[0], position[2]);
    }

    static void NotifyRadiosOfAirdropRelease(float x, float z)
    {
		// Calculate these here so they're consistent to all players
		float personalRadioX = x + Math.RandomFloatInclusive(-1500, 1500);
		float personalRadioZ = z + Math.RandomFloatInclusive(-1500, 1500);
		float baseRadioX = x + Math.RandomFloatInclusive(-500, 500);
		float baseRadioZ = z + Math.RandomFloatInclusive(-500, 500);

		array<Man> players = new array<Man>;
		GetGame().GetWorld().GetPlayerList(players);

		for (int i = 0; i < players.Count(); i++)
		{
			PlayerBase pb = PlayerBase.Cast(players.Get(i));
			if (pb && pb.IsAlive() && !pb.IsUnconscious() && !pb.IsPlayerDisconnected())
			{
				EntityAI radio = GetAirdropRadio(pb);
				if (radio != NULL)
				{
					if (radio.GetType() == "Spacecat_PersonalRadio_Mil")
					{
						ExpansionNotification("U.N. Airdrop", "Airdrop away near grid coordinates: " + personalRadioX + "/" + personalRadioZ + "\n\nGood luck survivors.", EXPANSION_NOTIFICATION_ICON_ERROR, COLOR_EXPANSION_NOTIFICATION_ERROR, 7, ExpansionNotificationType.TOAST).Create(pb.GetIdentity());
					}
					else 
					{
						ExpansionNotification("U.N. Airdrop", "Airdrop away near grid coordinates: " + baseRadioX + "/" + baseRadioZ + "\n\nGood luck survivors.", EXPANSION_NOTIFICATION_ICON_ERROR, COLOR_EXPANSION_NOTIFICATION_ERROR, 7, ExpansionNotificationType.TOAST).Create(pb.GetIdentity());
					}
				}
			}
		}	
    }

	static void NotifyRadiosOfAirdropInbound(string msg)
    {
		array<Man> players = new array<Man>;
		GetGame().GetWorld().GetPlayerList(players);

		for (int i = 0; i < players.Count(); i++)
		{
			PlayerBase pb = PlayerBase.Cast(players.Get(i));
			if (pb && pb.IsAlive() && !pb.IsUnconscious() && !pb.IsPlayerDisconnected())
			{
				ItemBase radio = GetAirdropRadio(pb);
				if (radio != NULL)
				{
					ExpansionNotification("U.N. Airdrop", msg, EXPANSION_NOTIFICATION_ICON_ERROR, COLOR_EXPANSION_NOTIFICATION_ERROR, 7, ExpansionNotificationType.TOAST).Create(pb.GetIdentity());
				}
			}
		}	
    }

	static ItemBase GetAirdropRadio(PlayerBase player)
	{
		ItemBase radio;
		int i;

		// Search for nearby base radio
		array<Object> objectsNearPlayer = new array<Object>;
		GetGame().GetObjectsAtPosition3D(player.GetPosition(), 10, objectsNearPlayer, NULL);
		for (i = 0; i < objectsNearPlayer.Count(); i++)
		{
			radio = ItemBase.Cast(objectsNearPlayer.Get(i));
			if (radio && (radio.IsInherited(BaseRadio) || radio.IsInherited(Zen_RaidAlarmStation)) && radio.GetCompEM() && radio.GetCompEM().IsWorking())
			{
				return radio;
			}
		}

		// Search inventory for base radio
		array<EntityAI> itemsArray = new array<EntityAI>;
		player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
		for (i = 0; i < itemsArray.Count(); i++)
		{
			if (itemsArray.Get(i) && itemsArray.Get(i).IsInherited(TransmitterBase))
			{
				radio = ItemBase.Cast(itemsArray.Get(i));
				if (radio && (radio.IsInherited(BaseRadio) || radio.GetType() == "Spacecat_PersonalRadio_Mil") && radio.GetCompEM() && radio.GetCompEM().IsWorking())
				{
					return radio;
				}
			}
		}

		return NULL;
	}
}

modded class ExpansionAirdropPlane
{
	
}