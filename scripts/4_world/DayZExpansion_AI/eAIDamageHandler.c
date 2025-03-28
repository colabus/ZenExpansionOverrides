modded class eAIDamageHandler
{
	override bool OnDamageCalculated(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
	#ifdef DIAG
		m_HitCounter++;

		EXTrace.PrintHit(EXTrace.AI, m_Entity, ToString() + "::OnDamageCalculated[" + m_HitCounter + "]", damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
	#endif

		DayZPlayerImplement sourcePlayer;
		if (source)  //! Source can be null if actual source is not an EntityAI but (e.g.) a static object during a vehicle collision
			sourcePlayer = DayZPlayerImplement.Cast(source.GetHierarchyRootPlayer());

		if (!m_ProcessDamage)
		{
			float damageMultiplier = 1.0;

			DayZPlayerImplement player;
			bool isPlayerItem;
			if (Class.CastTo(player, m_Entity.GetHierarchyRootPlayer()))
			{
				if (m_Entity.IsInventoryItem())
				{
					//! Entity is item on player

					if (player.m_eAI_DamageHandler.m_ProcessDamage)
						return true;  //! Process damage if player processes damage

					isPlayerItem = true;
				}

				if (player.IsAI())
					damageMultiplier *= player.m_eAI_DamageReceivedMultiplier;
			}

			if (sourcePlayer)
			{
				switch (damageType)
				{
					case DT_FIRE_ARM:
						eAIBase ai;
						if (Class.CastTo(ai, sourcePlayer))
						{
							if (sourcePlayer == m_Entity)
							{
								//! This shouldn't be possible because AI don't use suicide emote
								EXPrint(ToString() + " WARNING: Game encountered an impossible state (AI damage source is firearm in AI's own hands)");
								return false;
							}

							damageMultiplier *= ai.m_eAI_DamageMultiplier;
						}

						break;

					case DT_CLOSE_COMBAT:
						eAIGroup group = sourcePlayer.GetGroup();
						if (group)
						{
							eAIFaction faction = group.GetFaction();
							float yeetForce;

							if (!isPlayerItem)
							{
								yeetForce = faction.GetMeleeYeetForce();
								eAIMeleeCombat.eAI_ApplyYeetForce(m_TargetInformation, yeetForce, sourcePlayer.GetPosition(), faction.GetMeleeYeetFactors());
							}

							//! @note for player targets, melee dmg mult above 1 and yeet are mutually exclusive
							//! since you can't send players flying in the moment of death
							float meleeDamageMultiplier = faction.GetMeleeDamageMultiplier();
							if (meleeDamageMultiplier < 1.0 || (meleeDamageMultiplier > 1.0 && (!player || (!isPlayerItem && !yeetForce))))
								damageMultiplier *= meleeDamageMultiplier;
						}

						break;
				}
			}

			if (damageMultiplier != 1.0)
			{
				damageMultiplier *= speedCoef;

			#ifdef DIAG
				EXTrace.Print(EXTrace.AI, m_Entity, ToString() + "::OnDamageCalculated[" + m_HitCounter + "] override dmg coef " + speedCoef + " -> " + damageMultiplier);
			#endif

				if (!isPlayerItem && damageMultiplier != 0.0)
				{
					//! Need to use Call() to avoid inconsistent damage
					GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Call(ProcessDamage, damageType, source, sourcePlayer, dmgZone, ammo, modelPos, damageMultiplier);
				}

				return false;
			}
		}
		else
		{
			m_ProcessDamage = false;
		}

		//m_Entity = target 
		//sourcePlayer = aggressor

		// Tweaked to be a little more forgiving - player must deal at least 6 damage or kill/shoot a player to trigger guard aggro
		if (m_Entity.IsMan() && sourcePlayer && sourcePlayer != m_Entity)
		{
			PlayerBase sourcePlayerBase = PlayerBase.Cast(sourcePlayer);
			if (sourcePlayerBase)
			{
				eAIBase aiNpc = eAIBase.Cast(m_Entity);
				if (aiNpc != NULL && sourcePlayerBase.GetDamageCausedInSanctuary() >= PlayerBase.MINIMUM_DMG_GUARD_ALERT)
				{
					if (aiNpc.GetGroup() && aiNpc.GetGroup().GetFaction() && aiNpc.GetGroup().GetFaction().IsGuard())
						sourcePlayerBase.m_eAI_LastAggressionTime = ExpansionStatic.GetTime(true); //! Aggro guards in area (if any)
				}
			}
		}

		return true;
	}
}