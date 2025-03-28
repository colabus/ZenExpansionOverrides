modded class ExpansionBookMenu : ExpansionScriptViewMenu
{
	static string DONATE_PLAYERS = "";
	static float DONATE_DOLLARS = 0.0;

	ref Widget m_DonateRootWidget;
	ref MultilineTextWidget m_DonateTitleWidget;
	ref ProgressBarWidget m_DonateProgressBar;
	ref MultilineTextWidget m_DonateDescriptionWidget;
	ref MultilineTextWidget m_DonateNamesWidget;
	ref ButtonWidget m_DonateButtonWidget;

	override void UpdateBookTabs()
	{
		super.UpdateBookTabs();

		m_DonateRootWidget			= GetGame().GetWorkspace().CreateWidgets("ZenExpansionOverrides/data/gui/layouts/expansion_book.layout");
		m_DonateTitleWidget			= MultilineTextWidget.Cast(m_DonateRootWidget.FindAnyWidget("DonateTitleWidget"));
		m_DonateProgressBar			= ProgressBarWidget.Cast(m_DonateRootWidget.FindAnyWidget("DonateProgressBarWidget"));
		m_DonateDescriptionWidget	= MultilineTextWidget.Cast(m_DonateRootWidget.FindAnyWidget("DonateDescriptionWidget"));
		m_DonateNamesWidget			= MultilineTextWidget.Cast(m_DonateRootWidget.FindAnyWidget("DonateNamesWidget"));
		m_DonateButtonWidget		= ButtonWidget.Cast(m_DonateRootWidget.FindAnyWidget("DonateButtonWidget"));

		m_DonateNamesWidget.SetText(DONATE_PLAYERS);
		m_DonateTitleWidget.SetText("This Quarter's Donations: $" + MiscGameplayFunctions.TruncateToS(DONATE_DOLLARS) + "/$1,320");
		m_DonateProgressBar.SetCurrent(DONATE_DOLLARS);

		m_DonateRootWidget.Show(true);
	}

	override void ShowBookMainContent(bool state)
	{
		super.ShowBookMainContent(state);

		m_DonateRootWidget.Show(state);
	}

	override void OnHide()
	{
		super.OnHide();

		m_DonateRootWidget.Show(false);
	}

	void OnDonateButtonClick()
	{
		GetGame().OpenURL("https://hardcoredayz.com/donate");
	}

	/*override bool OnClick(Widget w, int x, int y, int button)
	{
		ZenFunctions.DebugMessage("ONCLICK: " + w.GetName());

		return super.OnClick(w, x, y, button);;
	}*/
}