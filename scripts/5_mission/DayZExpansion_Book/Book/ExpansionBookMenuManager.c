modded class ExpansionBookMenuManager
{
	//ref ExpansionBookMenuTabQuests m_QuestsTab;

	override void DestroyBookMenuTabs()
	{
		if (ExpansionBookMenuTabCraftingResultEntry.m_Tooltip)
		{
			ExpansionBookMenuTabCraftingResultEntry.m_Tooltip.Destroy();
		}

		super.DestroyBookMenuTabs();
	}

	/*override void RegisterBookMenuTabs(ExpansionBookMenu book_menu)
	{
		super.RegisterBookMenuTabs(book_menu);

		m_QuestsTab = new ExpansionBookMenuTabQuests(book_menu);
		m_Tabs.Insert(m_QuestsTab);
	};*/
}
