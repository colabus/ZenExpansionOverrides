class ActionOpenStaticZenMap : ActionInteractBase
{
	void ActionOpenStaticZenMap()
	{
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
		m_Text = "#unfold_map";
	}

	override bool IsInstant()
	{
		return true;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return true;
	}

	override void OnStartClient(ActionData action_data)
	{
		action_data.m_Player.SetZenToggleExpansionMap(true);
	}
}
