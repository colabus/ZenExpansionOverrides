modded class ExpansionBookMenuTabServerInfo
{
	static int CLIENTSIDE_PLAYER_COUNT = 0;
	static int CLIENTSIDE_PLAYER_COUNT_DB = 0;
	static int CLIENTSIDE_PLAYER_COUNT_ACTIVE_DB = 0;

	// Add how many days since wipe
	override void AddSettings()
	{
		int daysSinceWipe = 1;

		for (int i = 0; i < GetExpansionSettings().GetBook().SettingCategories.Count(); i++)
		{
			ExpansionBookSettingCategory category = GetExpansionSettings().GetBook().SettingCategories[i];
			ExpansionBookMenuTabServerInfoSettingCategory settingCategory = new ExpansionBookMenuTabServerInfoSettingCategory(this, category.CategoryName);
			foreach (ExpansionBookSetting setting: category.Settings)
			{
				if (setting.SettingTitle == "World days")
				{
					setting.SettingValue = GetWipeDays(TIMESTAMP_WIPE, false);
				}
				else 
				if (setting.SettingTitle == "Next season change")
				{
					setting.SettingText = "How many days until the next season change happens";
					setting.SettingValue = GetWipeDays(TIMESTAMP_SEASON, true);
				}
				else 
				if (setting.SettingTitle == "Active characters")
				{
					//string totalCharacters = CLIENTSIDE_PLAYER_COUNT_DB.ToString(); 
					//string totalCharactersText = totalCharacters.Substring(0, 1) + "," + totalCharacters.Substring(1, 3);
					setting.SettingValue = CLIENTSIDE_PLAYER_COUNT_ACTIVE_DB.ToString() + " / " + CLIENTSIDE_PLAYER_COUNT_DB.ToString();
				}
				else
				if (setting.SettingTitle == "Survivors online")
				{
					setting.SettingValue = CLIENTSIDE_PLAYER_COUNT.ToString() + " / 40";
				}

				ExpansionBookMenuTabServerInfoSetting categorySetting = new ExpansionBookMenuTabServerInfoSetting(setting.SettingTitle, setting.SettingText, setting.SettingValue);
				settingCategory.AddSetting(categorySetting);
			}
			
			m_ServerInfoTabController.SettingsCategories.Insert(settingCategory);
		}
	}

	string GetWipeDays(int timestampInitial, bool future)
	{
		int time_seconds = 0;
		int timestampNow = JMDate.Now(false).GetTimestamp();
		if (future)
		{
			time_seconds = timestampInitial - timestampNow;
		}
		else 
		{
			time_seconds = timestampNow - timestampInitial;
		}

		if (time_seconds <= 0)
		{
			return "0 #STR_EXPANSION_BOOK_STATUS_CHARACTER_STATS_DAYS ERROR";
		}

		string time_string;
		int days = time_seconds / 86400;
		time_string += ExpansionStatic.GetValueString(days) + " #STR_EXPANSION_BOOK_STATUS_CHARACTER_STATS_DAYS";

		return time_string;
	}
}