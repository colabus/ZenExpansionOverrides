modded class ActionPushCar : ActionContinuousBase
{
	//private const float MAX_WATER_DEPTH = 2.5;

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (player.GetPerkBoolValue(SyberiaPerkType.SYBPERK_STRENGTH_FLIPCAR) == false)
			return false;

		if (target && target.GetObject())
		{
			CarScript car = GetCar(target);
			if (car && target.GetObject().GetType().Contains("Boat"))
			{
				if (!player.IsPlayerInStance(DayZPlayerConstants.STANCEMASK_ERECT|DayZPlayerConstants.STANCEMASK_CROUCH))
					return false;

				vector boatPos = target.GetObject().GetPosition();

				/*
				float surfaceY = g_Game.SurfaceY(boatPos[0], boatPos[2]);
				float groundDepth = boatPos[1] - surfaceY;

				ZenFunctions.DebugMessage("BOAT DEPTH=" + groundDepth);
				if (groundDepth >= MAX_WATER_DEPTH)
				{
					//return false;
				}
				*/

				if (!player.CanConsumeStamina(EStaminaConsumers.PUSH))
					return false;

				// Client - raycast beneath player
				if (GetGame().IsClient())
				{
					m_Text = "Push boat";

					// Check we're not standing on the boat
					vector start = player.GetPosition();
					vector end = player.GetPosition() - "0 1 0";
					float raycastRadius = 0.3; // tiny ray radius to allow standing on jetties
					RaycastRVParams rayInput = new RaycastRVParams(start, end, player, raycastRadius);
					rayInput.flags = CollisionFlags.ALLOBJECTS;
					array<ref RaycastRVResult> results = new array<ref RaycastRVResult>;

					if (DayZPhysics.RaycastRVProxy(rayInput, results))
					{
						for (int i = 0; i < results.Count(); i++)
						{
							if (results.Get(i).obj.IsInherited(CarScript))
							{
								//ZenFunctions.DebugMessage("STANDING ON BOAT IDIOT!");
								return false;
							}
						}
					}
				}

				// Server
				return true;
			}
		}

		return super.ActionCondition(player, target, item);
	}
}