class ZenQuestExpConfig
{
	// Config location
	private const static string zenModFolder = "$profile:\\ExpansionMod\\Quests\\";
	private const static string zenConfigName = "ZenQuestExpConfig.json";
	private const static string CURRENT_VERSION = "1";

	// Saved to json
	string CONFIG_VERSION = "";
	ref array<ref ExpansionQuestEXP> Quests;

	void Load()
	{
		if (!GetGame().IsDedicatedServer())
			return;

		if (FileExist(zenModFolder + zenConfigName))
		{
			JsonFileLoader<ZenQuestExpConfig>.JsonLoadFile(zenModFolder + zenConfigName, this);

			if (CONFIG_VERSION != CURRENT_VERSION)
			{
				// Mismatch, back up old version
				JsonFileLoader<ZenQuestExpConfig>.JsonSaveFile(zenModFolder + zenConfigName + "_old", this);
			}
			else
			{
				// Config exists and version matches, shuffle array and stop here.
				return;
			}
		}

		CONFIG_VERSION = CURRENT_VERSION;

		if (!Quests)
			Quests = new array<ref ExpansionQuestEXP>;

		Quests.Clear();
		Quests.Insert(new ExpansionQuestEXP(-1, "Hunting", 0));

		Save();
	};

	void Save()
	{
		if (!FileExist(zenModFolder))
		{
			MakeDirectory(zenModFolder);
		}

		JsonFileLoader<ZenQuestExpConfig>.JsonSaveFile(zenModFolder + zenConfigName, this);
	}

	ExpansionQuestEXP GetQuestReward(int questID)
	{
		foreach (ExpansionQuestEXP quest : Quests)
		{
			if (quest.QuestID == questID)
				return quest;
		}

		return NULL;
	}
}

class ExpansionQuestEXP
{
	int QuestID;
	string Skill;
	int EXP;

	void ExpansionQuestEXP(int qid, string skid, int xp)
	{
		QuestID = qid;
		Skill = skid;
		EXP = xp;
	}
}

ref ZenQuestExpConfig m_ZenQuestExpConfig;

static ZenQuestExpConfig GetZenQuestExpConfig()
{
	if (!m_ZenQuestExpConfig)
	{
		m_ZenQuestExpConfig = new ZenQuestExpConfig;
		m_ZenQuestExpConfig.Load();
	}

	return m_ZenQuestExpConfig;
};