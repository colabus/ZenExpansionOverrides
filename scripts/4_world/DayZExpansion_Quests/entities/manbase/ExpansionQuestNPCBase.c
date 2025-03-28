modded class ExpansionQuestNPCBase
{
	override void Init()
	{
		super.Init();
		SetEventMask(EntityEvent.INIT|EntityEvent.POSTFRAME|EntityEvent.FRAME);
	}

	protected bool m_ZenHidden = false;

	bool ZenIsHidden()
	{
		return m_ZenHidden;
	}

	void CheckIfHidden()
	{
		m_ZenHidden = false;

		ExpansionQuestObject hideConfig = GetZenQuestHideNpcConfig().GetQuestHideConfig(m_QuestNPCID);
		if (!hideConfig)
			return;

		PlayerBase clientPlayer = PlayerBase.Cast(GetGame().GetPlayer());
		if (hideConfig.RequiredQuestToShowID != -1)
			m_ZenHidden = !ExpansionQuestModule.GetModuleInstance().HasCompletedQuest(hideConfig.RequiredQuestToShowID, clientPlayer.GetIdentity().GetId());
		else
		if (hideConfig.RequiredQuestToHideID != -1)
			m_ZenHidden = ExpansionQuestModule.GetModuleInstance().HasCompletedQuest(hideConfig.RequiredQuestToHideID, clientPlayer.GetIdentity().GetId());
		else
		if (hideConfig.StartedQuestToShowID != -1)
			m_ZenHidden = !ExpansionQuestModule.GetModuleInstance().Zen_HasStartedQuest(hideConfig.StartedQuestToShowID, clientPlayer.GetIdentity().GetId());
		else
		if (hideConfig.StartedQuestToHideID != -1)
			m_ZenHidden = ExpansionQuestModule.GetModuleInstance().Zen_HasStartedQuest(hideConfig.StartedQuestToHideID, clientPlayer.GetIdentity().GetId());
	}

	override void EOnPostFrame(IEntity other, int extra)
	{
		super.EOnPostFrame(other, extra);

		#ifndef SERVER
		CheckIfHidden();
		if (!m_ZenHidden)
			return;

		ClearFlags(EntityFlags.VISIBLE|EntityFlags.SOLID|EntityFlags.ACTIVE, true);
		SetScale(0);
		dBodySetInteractionLayer(this, PhxInteractionLayers.NOCOLLISION);
		DisableSimulation(true);
		#endif
	};
}