class AngryGuardsConfig
{
	// Config location
	private const static string zenModFolder = "$profile:\\Zenarchist\\Expansion\\";
	private const static string zenConfigName = "AngryGuardsConfig.json";
	private const static string CURRENT_VERSION = "1";

	// Consts 
	static const int OFFENSE_MURDER = 0;
	static const int OFFENSE_MELEE_ASSAULT = 1;
	static const int OFFENSE_GUN_ASSAULT = 2;

	// Saved to json
	string CONFIG_VERSION = "";

	int ForgetTimeSecs = 2629800 * 3; // 3 months
	int GuardAngryTimeMurderSecs = 604800 * 2; // 2 weeks
	int GuardsAngryTimeGunAssaultSecs = 86400; // 1 day
	int GuardsAngryTimeMeleeAssaultSecs = 3600; // 1 hour
	ref array<ref NaughtyPlayer> NaughtyPlayers;

	void Load()
	{
		// Don't load JSON on server
		if (!GetGame().IsDedicatedServer())
			return;

		if (FileExist(zenModFolder + zenConfigName))
		{
			JsonFileLoader<AngryGuardsConfig>.JsonLoadFile(zenModFolder + zenConfigName, this);

			if (CONFIG_VERSION != CURRENT_VERSION)
			{
				// Mismatch, back up old version
				JsonFileLoader<AngryGuardsConfig>.JsonSaveFile(zenModFolder + zenConfigName + "_old", this);
			}
			else
			{
				ValidateAngryPlayers();

				// Loaded fine, stop here
				return;
			}
		}

		CONFIG_VERSION = CURRENT_VERSION;

		if (!NaughtyPlayers)
			NaughtyPlayers = new array<ref NaughtyPlayer>;

		NaughtyPlayers.Clear();

		Save();
	};

	void Save()
	{
		if (!FileExist(zenModFolder))
		{
			MakeDirectory(zenModFolder);
		}

		JsonFileLoader<AngryGuardsConfig>.JsonSaveFile(zenModFolder + zenConfigName, this);
	}

	void ValidateAngryPlayers()
	{
		if (NaughtyPlayers.Count() == 0)
			return;

		int timestamp = JMDate.Now(false).GetTimestamp();
		for (int i = NaughtyPlayers.Count() - 1; i >= 0; i--)
		{
			NaughtyPlayer np = NaughtyPlayers.Get(i);
			if (timestamp > np.RecordExpiry)
			{
				ZenModLogger.Log("[AngryGuardsConfig] Delete naughty player record=" + np.SteamID, "AngryGuards");
				NaughtyPlayers.Remove(i);
			}
		}

		Save();
	}

	NaughtyPlayer GetNaughtyPlayer(string steamID)
	{
		foreach (NaughtyPlayer np : NaughtyPlayers)
		{
			if (np.SteamID == steamID)
			{
				return np;
			}
		}

		return NULL;
	}

	NaughtyPlayer SaveAngryGuardTimer(string steamID, int offenseType)
	{
		if (steamID == string.Empty)
			return NULL;

		int timestamp = JMDate.Now(false).GetTimestamp();
		NaughtyPlayer np;

		foreach (NaughtyPlayer npf : NaughtyPlayers)
		{
			if (npf.SteamID == steamID)
			{
				np = npf;
				break;
			}
		}

		if (!np)
		{
			np = new NaughtyPlayer(steamID);
			NaughtyPlayers.Insert(np);
		}

		float multi = 1.0;
		float expiryAddSecs;

		if (offenseType == OFFENSE_MURDER)
		{
			np.MostRecentOffense = "Murder";
			np.MurderCount = np.MurderCount + 1;

			if (np.MeleeAssaultCount >= 2)
				multi = multi * 1.5;

			expiryAddSecs = np.MurderCount * GuardAngryTimeMurderSecs * multi;

			if (IsServerPVE())
				expiryAddSecs = 3600 * 4;
		}
		else
		if (offenseType == OFFENSE_MELEE_ASSAULT)
		{
			np.MostRecentOffense = "Assault";
			np.MeleeAssaultCount = np.MeleeAssaultCount + 1;

			if (np.MeleeAssaultCount >= 3)
				multi = multi * 2;

			expiryAddSecs = np.MeleeAssaultCount * GuardsAngryTimeMeleeAssaultSecs * multi;

			if (IsServerPVE())
				expiryAddSecs = 3600;
		}
		else
		if (offenseType == OFFENSE_GUN_ASSAULT)
		{
			np.MostRecentOffense = "Grievous Bodily Harm";
			np.GunAssaultCount = np.GunAssaultCount + 1;

			if (np.GunAssaultCount >= 2)
				multi = multi * 2;

			if (np.GunAssaultCount >= 3)
				multi = multi * 2;

			expiryAddSecs = np.GunAssaultCount * GuardsAngryTimeGunAssaultSecs * multi;

			if (IsServerPVE())
				expiryAddSecs = 3600 * 2;
		}

		np.BanishmentExpiry = timestamp + expiryAddSecs;
		np.RecordExpiry = timestamp + ForgetTimeSecs + expiryAddSecs;

		ZenModLogger.Log("[AngryGuardsConfig] Updated naughty player record=" + np.SteamID + " | Offense=" + np.MostRecentOffense + " | BanishmentExpiry=" + ExpansionStatic.GetTimeString(np.BanishmentExpiry - timestamp), "AngryGuards");

		Save();
		return np;
	}
}

class NaughtyPlayer
{
	string SteamID;
	int MurderCount = 0;
	int GunAssaultCount = 0;
	int MeleeAssaultCount = 0;
	int BanishmentExpiry;
	int RecordExpiry;
	string MostRecentOffense;

	void NaughtyPlayer(string stid)
	{
		SteamID = stid;
	}
}

ref AngryGuardsConfig m_AngryGuardsConfig;

static AngryGuardsConfig GetAngryGuardsConfig()
{
	if (!m_AngryGuardsConfig)
	{
		m_AngryGuardsConfig = new AngryGuardsConfig;
		m_AngryGuardsConfig.Load();
	}

	return m_AngryGuardsConfig;
};