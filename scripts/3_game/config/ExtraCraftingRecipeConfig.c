class ZenExtraCraftingRecipes
{
	// Config location
	private const static string zenModFolder = "$profile:\\Zenarchist\\Expansion\\";
	private const static string zenConfigName = "ZenExtraCraftingRecipes.json";
	private const static string CURRENT_VERSION = "1";

	// Saved to json
	string CONFIG_VERSION = "";
	ref array<ref ZenCraftingRecipe> ZenCraftingRecipes;

	void Load()
	{
		// Don't load JSON on server
		if (!GetGame().IsDedicatedServer())
			return;

		if (FileExist(zenModFolder + zenConfigName))
		{
			JsonFileLoader<ZenExtraCraftingRecipes>.JsonLoadFile(zenModFolder + zenConfigName, this);

			if (CONFIG_VERSION != CURRENT_VERSION)
			{
				// Mismatch, back up old version
				JsonFileLoader<ZenExtraCraftingRecipes>.JsonSaveFile(zenModFolder + zenConfigName + "_old", this);
			}
			else
			{
				// Loaded fine, stop here
				return;
			}
		}

		CONFIG_VERSION = CURRENT_VERSION;

		if (!ZenCraftingRecipes)
			ZenCraftingRecipes = new array<ref ZenCraftingRecipe>;

		ZenCraftingRecipes.Clear();

		Save();
	};

	void Save()
	{
		if (!FileExist(zenModFolder))
		{
			MakeDirectory(zenModFolder);
		}

		JsonFileLoader<ZenExtraCraftingRecipes>.JsonSaveFile(zenModFolder + zenConfigName, this);
	}
}

class ZenCraftingRecipe
{
	/*string Result;
	ref array<string> 

	void ZenCraftingRecipe(string Result, int time)
	{
		SteamID = stid;
		AggressionTime = time;
	}*/
}

ref ZenExtraCraftingRecipes m_ZenExtraCraftingRecipes;

static ZenExtraCraftingRecipes GetZenExtraCraftingRecipes()
{
	if (!m_ZenExtraCraftingRecipes)
	{
		m_ZenExtraCraftingRecipes = new ZenExtraCraftingRecipes;
		m_ZenExtraCraftingRecipes.Load();
	}

	return m_ZenExtraCraftingRecipes;
};