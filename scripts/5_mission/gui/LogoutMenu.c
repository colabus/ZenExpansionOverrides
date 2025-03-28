modded class LogoutMenu
{
	override void UpdateInfo()
	{
		super.UpdateInfo();

		if (!GetGame())
			return;

		// Get player
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (!player)
			return;

		player.SaveDogForLogoutScreen();

		if (player.WillBePunishedForCombatLogging() <= 0) // If this is not a combat log, check for territory
		{
			if (player.CheckLogoutTerritory())
			{
				m_DescriptionText.SetText("#STR_ZenTerritoryLogout");
				m_DescriptionText.SetColor(ARGB(255, 255, 0, 0));
				GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(EnableLogoutButton);
				GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(EnableLogoutButton, player.GetDisableExitButtonSecs() * 1000, false);
			}
		}
	}
};