class ActionRepairPolanaRadioTowerCB: ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(12.0);
	}
}

class ActionRepairPolanaRadioTower: ActionContinuousBase
{
	void ActionRepairPolanaRadioTower()
	{
		m_CallbackClass 	= ActionRepairPolanaRadioTowerCB;
		m_CommandUID 		= DayZPlayerConstants.CMD_ACTIONFB_CRAFTING;
		m_FullBody 			= true;
		m_StanceMask 		= DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight 	= UASoftSkillsWeight.PRECISE_LOW;
		m_Text 				= "#repair";
	}
	
	override void CreateConditionComponents()  
	{		
		m_ConditionItem 	= new CCINonRuined();
		m_ConditionTarget	= new CCTCursor(UAMaxDistances.DEFAULT);
	}
	
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		Object targetObj = target.GetObject();

		if (!targetObj)
			return false;

		return targetObj.GetType() == "Zen_ControlPanel1";
	}
	
	override void OnFinishProgressServer(ActionData action_data)
	{	
		super.OnFinishProgressServer(action_data);
		action_data.m_MainItem.DeleteSafe();
	}
}
