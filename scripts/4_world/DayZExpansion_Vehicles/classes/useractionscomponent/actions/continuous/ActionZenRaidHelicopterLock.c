class ActionZenRaidHelicopterLockCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(ActionZenRaidHelicopterLock.UNLOCK_TIME);
	}
};

class ActionZenRaidHelicopterLock : ActionContinuousBase
{
	static const float UNLOCK_TIME = 90.0; // 1.5 mins

	void ActionZenRaidHelicopterLock()
	{
		m_CallbackClass = ActionZenRaidHelicopterLockCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTCursor(UAMaxDistances.DEFAULT);
	}

	override string GetText()
	{
		return "#unlock";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (player.InSanctuary()) // safezone
			return false;

		ExpansionHelicopterScript helicopter;
		if (!Class.CastTo( helicopter, target.GetParentOrObject()))
			return false;

		ExpansionPropaneTorch torch = ExpansionPropaneTorch.Cast(item);
		if (!torch || !torch.GetCompEM())
			return false;

		if (torch.GetEnergy() < torch.GetCompEM().GetEnergyUsage() * UNLOCK_TIME)
			return false;

		return helicopter.HasKey() && helicopter.IsLocked();
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		ExpansionHelicopterScript helicopter = ExpansionHelicopterScript.Cast(action_data.m_Target.GetParentOrObject());
		if (!helicopter)
			return;

		ExpansionPropaneTorch torch = ExpansionPropaneTorch.Cast(action_data.m_MainItem);
		if (!torch || !torch.GetCompEM())
			return;

		array<ExpansionCarKey> keys = new array<ExpansionCarKey>;

		if (helicopter)
		{
			ExpansionCarKey.GetKeysForVehicle(helicopter, keys);
			helicopter.ResetKeyPairing();
		}

		for (int i = 0; i < keys.Count(); ++i)
			keys[i].Unpair(true);

		torch.GetCompEM().SetEnergy(0);
		torch.SetSynchDirty();
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