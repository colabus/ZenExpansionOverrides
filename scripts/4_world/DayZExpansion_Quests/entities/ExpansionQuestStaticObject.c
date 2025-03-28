modded class ExpansionQuestStaticObject
{
	protected bool m_ZenHidden = false;

	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();

		CheckIfHidden();
	}

	bool ZenIsHiddenStatic()
	{
		return m_ZenHidden;
	}

	void CheckIfHidden()
	{
		m_ZenHidden = false;

		ExpansionQuestObject hideConfig = GetZenQuestHideNpcConfig().GetQuestHideConfig(m_QuestNPCID);
		if (!hideConfig || !GetGame().IsClient())
			return;

		PlayerBase clientPlayer = PlayerBase.Cast(GetGame().GetPlayer());
		if (hideConfig.RequiredQuestToShowID != -1)
		{
			m_ZenHidden = !ExpansionQuestModule.GetModuleInstance().HasCompletedQuest(hideConfig.RequiredQuestToShowID, clientPlayer.GetIdentity().GetId());
		} else
		if (hideConfig.RequiredQuestToHideID != -1)
		{
			m_ZenHidden = ExpansionQuestModule.GetModuleInstance().HasCompletedQuest(hideConfig.RequiredQuestToHideID, clientPlayer.GetIdentity().GetId());
		} else
		if (hideConfig.StartedQuestToShowID != -1)
		{
			m_ZenHidden = !ExpansionQuestModule.GetModuleInstance().Zen_HasStartedQuest(hideConfig.StartedQuestToShowID, clientPlayer.GetIdentity().GetId());
		} else
		if (hideConfig.StartedQuestToHideID != -1)
		{
			m_ZenHidden = ExpansionQuestModule.GetModuleInstance().Zen_HasStartedQuest(hideConfig.StartedQuestToHideID, clientPlayer.GetIdentity().GetId());
		}
	}
}