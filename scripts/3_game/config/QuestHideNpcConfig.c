class ZenQuestHideNpcConfig
{
	// Config location
	private const static string zenModFolder = "$profile:\\ExpansionMod\\Quests\\";
	private const static string zenConfigName = "ZenQuestHideNpcConfig.json";
	private const static string CURRENT_VERSION = "1";

	// Saved to json
	string CONFIG_VERSION = "";
	bool DebugOn = false;
	ref array<ref ExpansionQuestObject> QuestObjects;
	ref array<ref ExpansionHideQuest> HideQuests;
	ref array<ref ExpansionHideQuestMarker> HideQuestMarkers;

	void Load()
	{
		// Prepare arrays required by client + server
		if (!QuestObjects)
			QuestObjects = new array<ref ExpansionQuestObject>;

		if (!HideQuests)
			HideQuests = new array<ref ExpansionHideQuest>;

		if (!GetGame().IsDedicatedServer())
			return;

		// Load server config
		if (FileExist(zenModFolder + zenConfigName))
		{
			JsonFileLoader<ZenQuestHideNpcConfig>.JsonLoadFile(zenModFolder + zenConfigName, this);

			if (CONFIG_VERSION != CURRENT_VERSION)
			{
				// Mismatch, back up old version
				JsonFileLoader<ZenQuestHideNpcConfig>.JsonSaveFile(zenModFolder + zenConfigName + "_old", this);
			}
			else
			{
				// Config exists and version matches, shuffle array and stop here.
				return;
			}
		}

		CONFIG_VERSION = CURRENT_VERSION;

		// Client/server config
		QuestObjects.Insert(new ExpansionQuestObject(5, -1, 11));
		QuestObjects.Insert(new ExpansionQuestObject(6, -1, 11));
		HideQuests.Insert(new ExpansionHideQuest(12, 11));

		// Server-only config
		HideQuestMarkers = new array<ref ExpansionHideQuestMarker>;
		HideQuestMarkers.Insert(new ExpansionHideQuestMarker(40, 1));

		Save();
	};

	void Save()
	{
		if (!FileExist(zenModFolder))
		{
			MakeDirectory(zenModFolder);
		}

		JsonFileLoader<ZenQuestHideNpcConfig>.JsonSaveFile(zenModFolder + zenConfigName, this);
	}

	ExpansionQuestObject GetQuestHideConfig(int questObjID)
	{
		foreach (ExpansionQuestObject quest : QuestObjects)
		{
			if (quest.QuestObjectID == questObjID)
				return quest;
		}

		return NULL;
	}
}

class ExpansionQuestObject
{
	int QuestObjectID;
	int RequiredQuestToShowID;
	int RequiredQuestToHideID;
	int StartedQuestToShowID = -1;
	int StartedQuestToHideID = -1;

	void ExpansionQuestObject(int qid, int showID, int hideID)
	{
		QuestObjectID = qid;
		RequiredQuestToShowID = showID;
		RequiredQuestToHideID = hideID;
	}
}

class ExpansionHideQuest
{
	int QuestHideID;
	int QuestCompletedID;

	void ExpansionHideQuest(int p_qhid, int p_qcid)
	{
		QuestHideID = p_qhid;
		QuestCompletedID = p_qcid;
	}
}

class ExpansionHideQuestMarker
{
	int QuestID;
	int QuestObjectiveHideIndex;

	void ExpansionHideQuestMarker(int p_qhid, int p_qidx)
	{
		QuestID = p_qhid;
		QuestObjectiveHideIndex = p_qidx;
	}
}

ref ZenQuestHideNpcConfig m_ZenQuestHideNpcConfig;

static ZenQuestHideNpcConfig GetZenQuestHideNpcConfig()
{
	if (!m_ZenQuestHideNpcConfig)
	{
		m_ZenQuestHideNpcConfig = new ZenQuestHideNpcConfig;
		m_ZenQuestHideNpcConfig.Load();
	}

	return m_ZenQuestHideNpcConfig;
};