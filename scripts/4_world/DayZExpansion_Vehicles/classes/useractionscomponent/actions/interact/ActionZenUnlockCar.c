class ActionZenUnlockCar: ActionInteractBase
{	
	void ActionZenUnlockCar()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
		m_LockTargetOnUse = false;
		m_Text = "#unlock";
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem		= new CCINone;
		m_ConditionTarget	= new CCTNone;
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		//! reach check from outside of car
		if (!IsInReach(player, target, UAMaxDistances.DEFAULT))
		{
			return false;
		}

		//! player is outside of vehicle
		CarScript car = null;
		if (Class.CastTo(car, target.GetParent()))
		{
			return car.IsTraderLockedSyncCheck();
		}
		
		return false;
	}
	
	override void OnStartServer(ActionData action_data)
	{
		if (!action_data.m_Target)
			return;

		CarScript car = null;
		if (!Class.CastTo(car, action_data.m_Target.GetParent()))
			return;

		if (car.IsTraderLocked(action_data.m_Player))
		{
			// Out of sanctuary - let anyone unlock car
			if (vector.Distance(car.GetPosition(), "5638.0 180.0 10607.0") > 80)
			{
				car.UnlockTraderCar();
			}
			else
			{
				string notifyTxt = "Only the owner can unlock vehicles!";
				ExpansionNotification("VEHICLE LOCKED", notifyTxt).Error(action_data.m_Player.GetIdentity());
			}
		}
		else
		{
			car.UnlockTraderCar();
		}
	}
};