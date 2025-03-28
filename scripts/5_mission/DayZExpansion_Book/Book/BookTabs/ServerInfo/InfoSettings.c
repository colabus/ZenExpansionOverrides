modded class ExpansionBookMenuTabServerInfoSetting
{
	override void UpdateSetting(string name, string desc, string setting)
	{
		super.UpdateSetting(name, desc, setting);

		switch (name)
		{
			#ifdef EXPANSIONMODBASEBUILDING
			//! Territory
			case "Expansion.Settings.Territory.TerritorySize":
				m_Name = "#STR_EXPANSION_SETTINGS_T_TERRITORYSIZE";
				m_Desc = "The size of a territory in meters. Enemy survivors cannot build within this zone.";
				m_Setting = GetExpansionSettings().GetTerritory().TerritorySize.ToString() + "m";
				break;
			case "Expansion.Settings.Territory.UseWholeMapForInviteList":
				m_Name = "#STR_EXPANSION_SETTINGS_P_USEWHOLEMAPFORINVITELIST";
				m_Setting = BoolToString(GetExpansionSettings().GetTerritory().UseWholeMapForInviteList);
				break;
			case "Expansion.Settings.Territory.MaxTerritoryPerPlayer":
				m_Name = "Maximum territories per player";
				m_Desc = "Maximum number of Territory Flags a player can have.";
				m_Setting = GetExpansionSettings().GetTerritory().MaxTerritoryPerPlayer.ToString();
				break;
			case "Expansion.Settings.Territory.MaxMembersInTerritory":
				m_Name = "Max members of territory";
				m_Desc = "Max number of players that can be invited to a territory.";
				m_Setting = GetExpansionSettings().GetTerritory().MaxMembersInTerritory.ToString();
				break;
			#endif
		}
	}
}