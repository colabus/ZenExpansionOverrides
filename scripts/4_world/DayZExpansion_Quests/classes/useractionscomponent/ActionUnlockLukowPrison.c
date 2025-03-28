class ActionUnlockLukowPrison : ActionContinuousBase
{
	void ActionUnlockLukowPrison()
	{
		m_CallbackClass = ActionLockDoorsCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_Text = "#unlock";
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTCursor;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!target) return false;
		if (player.GetPosition()[1] < 5000) return false; // Prison is in sky
		if (!IsBuilding(target)) return false;
		if (!IsInReach(player, target, UAMaxDistances.DEFAULT)) return false;

		Building building;
		if (Class.CastTo(building, target.GetObject()))
		{
			if (building.GetType().Contains("Land_Underground_Storage_Prison"))
			{
				int doorIndex = building.GetDoorIndex(target.GetComponentIndex());
				if (doorIndex == 4) // 4 = prison cell with npc ai in it
					return building.IsDoorLocked(doorIndex);
			}
		}

		return false;
	}

	protected void UnlockDoor(ActionTarget target)
	{
		Building building;

		if (Class.CastTo(building, target.GetObject()))
		{
			int doorIndex = building.GetDoorIndex(target.GetComponentIndex());
			if (doorIndex != -1)
			{
				building.UnlockDoor(doorIndex);
			}
		}
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		UnlockDoor(action_data.m_Target);

		if (action_data.m_MainItem)
		{
			action_data.m_MainItem.SetAllowDamage(true);
			action_data.m_MainItem.SetHealth(0);
		}
		//! TODO: Play voice effect - Thank you survivor! I just need to grab some things from my laboratory and I'll be right with you. I'll meet you outside. <ALSO PLAY AS DEFAULT TEXT>
	}
}

modded class ActionUnlockDoors : ActionContinuousBase
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!super.ActionCondition(player, target, item))
			return false;

		// Prison cell
		if (player.GetPosition()[1] >= 5000)
		{
			Building building;
			if (Class.CastTo(building, target.GetObject()))
			{
				if (building.GetType().Contains("Land_Underground_Storage_Prison"))
				{
					return false;
				}
			}
		}

		return true;
	}
}