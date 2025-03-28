class ActionZenOpenCargoCrateCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(ActionZenOpenCargoCrate.UNLOCK_TIME);
	}
};

class ActionZenOpenCargoCrate : ActionContinuousBase
{
	static const float UNLOCK_TIME = 30.0;

	void ActionZenOpenCargoCrate()
	{
		m_CallbackClass = ActionZenOpenCargoCrateCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH;
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTCursor(UAMaxDistances.DEFAULT);
	}

	override string GetText()
	{
		return "#open";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		Zen_ExpansionMilitaryCargo crate = Zen_ExpansionMilitaryCargo.Cast(target.GetObject());

		if (!crate)
			return false;

		ExpansionPropaneTorch torch = ExpansionPropaneTorch.Cast(item);
		if (torch)
		{
			if (torch.GetEnergy() < torch.GetCompEM().GetEnergyUsage() * UNLOCK_TIME)
				return false;
		}

		return crate.CanBreakOpen();
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		PlayerBase player = action_data.m_Player;

		Zen_ExpansionMilitaryCargo crate = Zen_ExpansionMilitaryCargo.Cast(action_data.m_Target.GetObject());

		if (!crate)
			return;

		crate.UnlockInventory();
		crate.SetLifetime(1800);

		// If not torch, ruin bolt cutters
		ExpansionPropaneTorch torch = ExpansionPropaneTorch.Cast(action_data.m_MainItem);
		if (!torch)
			action_data.m_MainItem.SetHealth(0);
	}

	override void OnStartAnimationLoop(ActionData action_data)
	{
		super.OnStartAnimationLoop(action_data);

		if (!GetGame().IsDedicatedServer())
			return;

		ExpansionPropaneTorch torch = ExpansionPropaneTorch.Cast(action_data.m_MainItem);
		if (!torch)
			return;

		torch.GetCompEM().SwitchOn();
	}
	
	override void OnEnd(ActionData action_data)
	{
		super.OnEnd(action_data);

		if (!GetGame().IsDedicatedServer())
			return;

		ExpansionPropaneTorch torch = ExpansionPropaneTorch.Cast(action_data.m_MainItem);
		if (!torch)
			return;

		torch.GetCompEM().SwitchOff();
	}
};