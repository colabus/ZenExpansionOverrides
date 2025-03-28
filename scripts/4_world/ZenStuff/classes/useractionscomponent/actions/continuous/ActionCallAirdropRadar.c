class ActionCallAirdropRadarCB: ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(12.0);
	}
}

class ActionCallAirdropRadar : ActionContinuousBase
{
	void ActionCallAirdropRadar()
	{
		m_CallbackClass 	= ActionCallAirdropRadarCB;
		m_CommandUID 		= DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody 			= true;
		m_StanceMask 		= DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_SpecialtyWeight 	= UASoftSkillsWeight.PRECISE_LOW;
		m_Text 				= "Call Airdrop";
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

		return targetObj.GetType() == "Zen_AirdropRadar_Static";
	}
	
	override void OnFinishProgressServer(ActionData action_data)
	{	
		super.OnFinishProgressServer(action_data);

		Object radarDish = action_data.m_Target.GetObject();
		if (!radarDish)
			return;

		action_data.m_MainItem.DeleteSafe();
		ExpansionMissionModule.s_Instance.CallAirdrop(ZenFunctions.GetRandomPointInCircle(radarDish.GetPosition(), 100, 20));
		ExpansionNotification("U.N. AIRDROP CALLED", "Message received, survivor. Stand by, we've dispatched an airdrop to your location. It should arrive in a few minutes.", EXPANSION_NOTIFICATION_ICON_INFO, COLOR_EXPANSION_NOTIFICATION_AMETHYST).Create(action_data.m_Player.GetIdentity());
	}
}
