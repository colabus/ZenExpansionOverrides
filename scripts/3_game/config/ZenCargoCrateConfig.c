class ZenCargoCrateConfig
{
	// Static constant config version (is NOT saved to json)
	static const string CONFIG_VERSION = "1";

	// Config location
	private const static string zenModFolder = "$profile:\\Zenarchist\\";
	private const static string zenConfigName = "ZenCargoCrateConfig.json";

	// Default Values
	string ConfigVersion = "";
	int CrateLifetime = 604800;
	int MaxMilitaryCrates = 2;
	int MaxContaminationCrates = 2;
	ref array<ref ZenCargoCrate> MilitaryCrateLocations = new array<ref ZenCargoCrate>;
	ref array<ref ZenCargoCrate> ContaminationCrateLocations = new array<ref ZenCargoCrate>;

	// Load config file or create default file if config doesn't exsit
	void Load()
	{
		if (FileExist(zenModFolder + zenConfigName))
		{ 
			// If config exists, load file
			JsonFileLoader<ZenCargoCrateConfig>.JsonLoadFile(zenModFolder + zenConfigName, this);

			// If version mismatch, backup old version of json before replacing it
			if (ConfigVersion != CONFIG_VERSION)
			{
				JsonFileLoader<ZenCargoCrateConfig>.JsonSaveFile(zenModFolder + zenConfigName + "_old", this);
			}
			else
			{
				// Config exists and version matches, stop here.
				return;
			}
		}

		// File does not exist, create file
		ConfigVersion = CONFIG_VERSION;

		// Standard mil crates
		ref ZenCargoCrate MilCrates = new ZenCargoCrate("Zen_ExpansionMilitaryCargo");
		MilCrates.Locations.Insert("4122.234863 238.172501 10475.60351");
		MilCrates.Locations.Insert("7914.691895 321.144318 9869.152344");
		MilCrates.Locations.Insert("5528.710938 311.412415 8778.377930");
		MilCrates.Locations.Insert("2069.243408 287.762848 11154.42480");
		MilCrates.Locations.Insert("9823.300781 209.240875 8498.847656");
		MilCrates.Locations.Insert("8273.872070 205.247696 11213.25195");
		MilCrates.Locations.Insert("7647.728027 233.098206 5964.469238");
		MilCrates.Locations.Insert("4400.915527 316.276306 6727.407715");
		MilCrates.Locations.Insert("8950.358398 472.819031 2042.154053");
		MilCrates.Locations.Insert("11487.10742 212.614929 451.7177120");
		MilCrates.Locations.Insert("5165.859375 517.131531 2250.245361");
		MilCrates.Locations.Insert("819.0301510 531.329468 1197.525146");
		MilCrates.Locations.Insert("649.0715330 531.427246 1143.498779");
		MilCrates.Locations.Insert("7811.800293 339.452484 10117.843750");
		MilitaryCrateLocations.Insert(MilCrates);
		
		// Contamination crates
		ref ZenCargoCrate ContamCrates = new ZenCargoCrate("Zen_ExpansionMilitaryCargo_Contam");
		ContamCrates.Locations.Insert("4079.014404 238.260147 10199.63136");
		ContamCrates.Locations.Insert("7548.596680 228.710037 6113.625488");
		ContamCrates.Locations.Insert("11585.77246 212.432480 376.2210690");
		ContamCrates.Locations.Insert("3827.582520 558.792480 1831.223755");
		ContamCrates.Locations.Insert("7358.534668 287.023926 2637.290771");
		ContaminationCrateLocations.Insert(ContamCrates);

		Save();
	}

	void Save()
	{
		if (!FileExist(zenModFolder))
		{ 
			// If config folder doesn't exist, create it.
			MakeDirectory(zenModFolder);
		}

		JsonFileLoader<ZenCargoCrateConfig>.JsonSaveFile(zenModFolder + zenConfigName, this);
	}
}

class ZenCargoCrate
{
	string Type;
	string AirdropType;
	ref array<vector> Locations;

	void ZenCargoCrate(string p_type, string p_dropType = "Military")
	{
		Type = p_type;
		Locations = new array<vector>;
		AirdropType = p_dropType;
	}
}

ref ZenCargoCrateConfig m_ZenCargoCrateConfig;

static ZenCargoCrateConfig GetZenCargoCrateConfig()
{
	if (!m_ZenCargoCrateConfig)
	{
		m_ZenCargoCrateConfig = new ZenCargoCrateConfig;
		m_ZenCargoCrateConfig.Load();
	}

	return m_ZenCargoCrateConfig;
}