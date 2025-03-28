#ifdef ENFUSION_AI_PROJECT
modded class eAIPlayerTargetInformation
{
	/*override float CalculateThreat(eAIBase ai = null)
	{
		float threat = super.CalculateThreat(ai);

		if (!ai)
			return super.CalculateThreat(ai);

		float distance = GetDistance(ai, true) + 0.1;

		string groupName = "";
		if (ai && ai.GetGroup())
		{
			groupName = ai.GetGroup().GetName();
			groupName.ToLower();
		}
		
		if (groupName == "" || !groupName.Contains("sanctuary"))
			return threat;

		if (distance > 350)
			return threat;

		if (m_Player.eAI_GetLastAggressionCooldown() > 0)
			threat += 100.0;

		return threat;
	}*/

	float m_TimeWasRaisedAt = 0;

	override float CalculateThreat(eAIBase ai = null)
	{
		if (m_Player.IsDamageDestroyed())
			return 0.0;

		float levelFactor = 0.1;

		if (ai)
		{
			if (ai == m_Player)
				return 0.0;

			#ifdef DIAG
			auto hitch = new EXHitch(ai.ToString() + " eAIPlayerTargetInformation::CalculateThreat ", 20000);
			#endif

			// the further away the player, the less likely they will be a threat
			float distance = GetDistance(ai, true) + 0.1;

			if (m_Player.IsUnconscious() || m_Player.IsRestrained())
				return ExpansionMath.LinearConversion(0, 100, distance, 0.15, 0.1);

			if (distance <= 100.0 && m_Player.GetParent() != ai.GetParent())
			{
				//! Any AI, even passive, will react if vehicle is speeding towards them
				//! Vehicles WITHOUT drivers are handled by vehicle target info
				levelFactor = ProcessVehicleThreat(ai, distance);
				if (levelFactor > 0.0)
					return levelFactor;
			}

			bool isPlayerMoving;
			if (!ai.PlayerIsEnemy(m_Player, false, isPlayerMoving))
			{
				//! They eyeball you menacingly if you move, or if another friendly AI moves that is not in same group
				if (isPlayerMoving && (!m_Player.IsAI() || m_Player.GetGroup() != ai.GetGroup()))
					return ExpansionMath.PowerConversion(0.5, 30, distance, 0.152, 0.1, 0.1);

				return 0.1;
			}

			vector fromTargetDirection = vector.Direction(m_Player.GetPosition(), ai.GetPosition()).Normalized();
			float fromTargetDot = vector.Dot(m_Player.Expansion_GetAimDirection(), fromTargetDirection);

			//! Enemy weapon
			auto enemyHands = ItemBase.Cast(m_Player.GetHumanInventory().GetEntityInHands());

			PlayerBase pb;
			Class.CastTo(pb, m_Player);

			//! Threat handling for guards and observers
			//! Guards won't aggro until the other player raises their weapon in their direction, starts melee fighting or shoots another player
			//! Observers will never aggro and just look at the player
			if (ai.GetGroup())
			{
				bool canEnterFightingState = false;

				// Adjust guard AI to be a little more forgiving until player does something stupid
				if (ai.GetGroup().GetFaction().IsGuard())
				{
					// Guards are aggro - attack!
					if (distance < 300 && m_Player.eAI_GetLastAggressionCooldown() > 0)
					{
						return 1000.0;
					} else
					if (m_Player.IsRaised() && fromTargetDot >= 0.9 && ((enemyHands && enemyHands.IsWeapon())))
					{
						m_TimeWasRaisedAt += 0.5;

						if (m_TimeWasRaisedAt >= 5.0)
						{
							canEnterFightingState = true; // TODO: Don't shoot at ADS, just aim back
						}

						return m_TimeWasRaisedAt;
					} else
					if (m_Player.eAI_UpdateAgressionTimeout(150.0 - distance))
					{
						canEnterFightingState = true;
					}

					if (!canEnterFightingState && m_Player.IsRaised())
					{
						//! They aim at you
						return ExpansionMath.PowerConversion(0.5, 30, distance, 0.2, 0.0, 0.1);
					}

					if (!m_Player.IsRaised())
						m_TimeWasRaisedAt = 0;
				}
				else 
				if (!ai.GetGroup().GetFaction().IsObserver() && !m_Player.Expansion_IsInSafeZone())
				{
					canEnterFightingState = true;
				}

				if (!canEnterFightingState)
				{
					//! They eyeball you menacingly
					return ExpansionMath.PowerConversion(0.5, 30, distance, 0.152, 0.1, 0.1);
				}
			}

			levelFactor = 10 / distance;

			if (distance > 30)
			{
				if (pb)
					levelFactor *= ExpansionMath.LinearConversion(1.0, 3.0, pb.Expansion_GetMovementSpeed(), Math.Max(0.2, pb.GetVisibilityCoef()), 1.0);

				//! Check if target is facing AI or AI is facing target when not in near range (30 m)
				vector toTargetDirection = vector.Direction(ai.GetPosition(), m_Player.GetPosition()).Normalized();
				float toTargetDot = vector.Dot(ai.GetAimDirection(), toTargetDirection);
				if (fromTargetDot < 0.75 && toTargetDot < 0.75)  //! Target is facing away and AI is facing away
					return Math.Clamp(levelFactor, 0.0, 1000000.0);
			}

			//! Enemy is within 30 m, or farher than 30 m but looking in our direction,
			//! or we are looking in their direction

			//! Only adjust threat level based on enemy weapon if AI has a weapon in hands to fight back to begin with
			//! Threat level from lowest to highest:
			//! AI bare fists: Distance, look direction and enemy weapon if close affect threat level
			//! AI weapon, enemy bare fists or unraised weapon: Distance, look direction and AI weapon affect threat level
			//! AI weapon, enemy raised weapon: Distance, look direction, AI weapon and enemy weapon affect threat level
			//! This should ensure that AI doesn't take fist fights over long distances or against armed enemies unless they are close,
			//! and prioritizes enemies with raised weapons
			auto hands = ai.GetHumanInventory().GetEntityInHands();
			bool hasLOS;
			if (ai.eAI_HasLOS(this))  //! It's OK if LOS state is stale at this point
				hasLOS = true;

			if ((hands && AdjustThreatLevelBasedOnWeapon(hands, distance, levelFactor, hasLOS)) || distance <= 30 || hasLOS)
			{
				if (enemyHands)
				{
					//! Enemy weapon is raised or enemy is close
					if (m_Player.IsRaised() || distance <= 30 || hasLOS)
					{
						AdjustThreatLevelBasedOnWeapon(enemyHands, distance, levelFactor, hasLOS);

						if (m_Player.IsRaised())
							levelFactor *= ExpansionMath.LinearConversion(0, 1000, distance, 2.0, 1.0);
					}
				}
			}

			levelFactor *= ai.Expansion_GetVisibility(distance);
		}

		return Math.Clamp(levelFactor, 0.0, 1000000.0);
	}

	override float ProcessVehicleThreat(eAIBase ai, float distance)
	{
		// Stop guards shooting players for driving towards them
		if (distance > 2.0)
			return 0.0;

		return super.ProcessVehicleThreat(ai, distance);
	}
}
#endif