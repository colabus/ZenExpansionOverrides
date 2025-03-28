class ZenExtraExpansionConfig
{
	// Config location
	private const static string zenModFolder = "$profile:\\ExpansionMod\\";
	private const static string zenConfigName = "ZenExtraExpansionConfig.json";
	private const static string CURRENT_VERSION = "1";

	// Saved to json
	string CONFIG_VERSION = "";

	// Config 
	static int MaxBasebuildingObjects = 200;
	static int MaxCargoItems = 1000;

	void Load()
	{
		if (!GetGame().IsDedicatedServer())
			return;

		if (FileExist(zenModFolder + zenConfigName))
		{
			JsonFileLoader<ZenExtraExpansionConfig>.JsonLoadFile(zenModFolder + zenConfigName, this);

			if (CONFIG_VERSION != CURRENT_VERSION)
			{
				// Mismatch, back up old version
				JsonFileLoader<ZenExtraExpansionConfig>.JsonSaveFile(zenModFolder + zenConfigName + "_old", this);
			}
			else
			{
				// Config exists and version matches, shuffle array and stop here.
				return;
			}
		}

		CONFIG_VERSION = CURRENT_VERSION;

		// Set default Config
		Save();
	};

	void Save()
	{
		if (!FileExist(zenModFolder))
		{
			MakeDirectory(zenModFolder);
		}

		JsonFileLoader<ZenExtraExpansionConfig>.JsonSaveFile(zenModFolder + zenConfigName, this);
	}
}

ref ZenExtraExpansionConfig m_ZenExtraExpansionConfig;

static ZenExtraExpansionConfig GetZenExtraExpansionConfig()
{
	if (!m_ZenExtraExpansionConfig)
	{
		m_ZenExtraExpansionConfig = new ZenExtraExpansionConfig;
		m_ZenExtraExpansionConfig.Load();
	}

	return m_ZenExtraExpansionConfig;
};