modded class ExpansionQuestMenu
{
	protected bool m_ShowCompleteButton = true;

	override void PlayVoiceAudioZen(string voiceSoundSet, Object npc, bool fade = true)
	{
		if (!npc)
			return;

		ExpansionQuestNPCAIBase npcAI = ExpansionQuestNPCAIBase.Cast(npc);
		if (npcAI && npcAI.ZenIsHidden())
			return;

		super.PlayVoiceAudioZen(voiceSoundSet, npc, fade);
	}

	override void SetQuest(ExpansionQuestConfig quest)
	{
		super.SetQuest(quest);

		CancelLable.SetText("Reset Quest");

		// We allow checking weekly quests and taking them from base radio, but don't allow completing them without visiting Sancutary
		if (ExpansionQuestModule.VIEWING_QUESTS_ON_BASE_RADIO)
		{
			Complete.Show(false);
		}
	}
}
