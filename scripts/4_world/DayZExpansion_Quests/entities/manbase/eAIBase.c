modded class eAIBase
{
	void ~eAIBase()
	{
		if (Expansion_IsQuestVIP() && GetGame().IsClient() && IsAlive())
		{
			if (GetType() == "eAI_SurvivorM_Quinn")
			{
				CheckHermitQuest();
			}
		}
	}

	void CheckHermitQuest()
	{
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (!player)
			return;

		array<Object> nearest_objects = new array<Object>;
		GetGame().GetObjectsAtPosition3D(player.GetPosition(), 25, nearest_objects, NULL);

		for (int i = 0; i < nearest_objects.Count(); ++i)
		{
			Object object = nearest_objects.Get(i);
				
			if (object.GetType() == "Zen_HermitQuestTent")
			{
				if (ExpansionQuestModule.GetModuleInstance().Zen_HasStartedQuest(38, player.GetIdentity().GetId()))
				{
					SEffectManager.PlaySoundOnObject("Zen_QuestHermit2_SoundSet", player);
					ZenFunctions.ZenClientMessage("Hermit: Thank you survivor. Here, take this. Sebastian will know what to do with it. Good luck out there.");
				}
			}
		}
	}
}

modded class InjuryAnimationHandler
{
	override eInjuryHandlerLevels GetInjuryLevel(float health)
	{
		eAIBase ai = eAIBase.Cast(m_Player);
		if (ai != NULL)
		{
			if (ai.Expansion_IsQuestVIP() && ai.GetType() == "eAI_SurvivorM_Quinn")
				return eInjuryHandlerLevels.BADLY_DAMAGED;
		}
		
		return super.GetInjuryLevel(health);
	}
}