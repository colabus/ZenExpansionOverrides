#ifdef ENFUSION_AI_PROJECT
modded class ExpansionBookMenuTabFactions
{
	override void SetView()
	{
		OpenQuests();
	};

	protected void OpenQuests()
	{
		if (!GetExpansionSettings().GetQuest(false).IsLoaded() || !GetExpansionSettings().GetQuest().EnableQuests)
			return;

		ExpansionUIManager uiManager = GetDayZGame().GetExpansionGame().GetExpansionUIManager();	//! Reference to expansion ui manager
		ScriptView menu = uiManager.GetMenu();	//! Reference to current opened script view menu

		ExpansionQuestMenu questMenu = ExpansionQuestMenu.Cast(menu);
		if (!questMenu)
		{
			uiManager.CreateSVMenu("ExpansionQuestMenu");
			questMenu = ExpansionQuestMenu.Cast(uiManager.GetMenu());
			if (questMenu)
			{
				questMenu.SetLogMode(true);
				questMenu.SetQuestLogView();
			}
		}
		else 
		if (questMenu && questMenu.IsVisible())
		{
			uiManager.CloseMenu();
		}
	}

	override string GetTabName()
	{
		return "Quests";
	}

	override string GetTabIconName()
	{
		return "Questionmark";
	}
};
#endif