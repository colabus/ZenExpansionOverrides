class FreshieSuppliesConfig
{
	// Config location
	private const static string zenModFolder = "$profile:\\Zenarchist\\Expansion\\";
	private const static string zenConfigName = "FreshieSuppliesConfig.json";
	private const static string CURRENT_VERSION = "1";

	// Saved to json
	string CONFIG_VERSION = "";

	int MaximumPlayerAge = 14400;

	ref array<ref FreshieMarketItem> FreshieMarketItems = new array<ref FreshieMarketItem>;

	void Load()
	{
		// Don't load JSON on server
		if (!GetGame().IsDedicatedServer())
			return;

		if (FileExist(zenModFolder + zenConfigName))
		{
			JsonFileLoader<FreshieSuppliesConfig>.JsonLoadFile(zenModFolder + zenConfigName, this);

			if (CONFIG_VERSION != CURRENT_VERSION)
			{
				// Mismatch, back up old version
				JsonFileLoader<FreshieSuppliesConfig>.JsonSaveFile(zenModFolder + zenConfigName + "_old", this);
			}
			else
			{
				// Loaded fine, stop here
				return;
			}
		}

		CONFIG_VERSION = CURRENT_VERSION;

		FreshieMarketItem itemExample = new FreshieMarketItem;
		itemExample.ItemType = "Edibles";
		itemExample.MaxBuy = 5;
		itemExample.Classnames.Insert("zagorky");
		itemExample.Classnames.Insert("zagorkychocolate");
		itemExample.Classnames.Insert("zagorkypeanuts");
		itemExample.Classnames.Insert("powderedmilk");
		itemExample.Classnames.Insert("boxcerealcrunchin");
		itemExample.Classnames.Insert("rice");
		itemExample.Classnames.Insert("marmalade");
		itemExample.Classnames.Insert("honey");
		itemExample.Classnames.Insert("saltysticks");
		itemExample.Classnames.Insert("crackers");
		itemExample.Classnames.Insert("chips");
		itemExample.Classnames.Insert("pajka");
		itemExample.Classnames.Insert("pate");
		itemExample.Classnames.Insert("brisketspread");
		itemExample.Classnames.Insert("sardinescan");
		itemExample.Classnames.Insert("tunacan");
		itemExample.Classnames.Insert("dogfoodcan");
		itemExample.Classnames.Insert("catfoodcan");
		itemExample.Classnames.Insert("porkcan");
		itemExample.Classnames.Insert("lunchmeat");
		itemExample.Classnames.Insert("peachescan");
		itemExample.Classnames.Insert("spaghettican");
		itemExample.Classnames.Insert("bakedbeanscan");
		itemExample.Classnames.Insert("tacticalbaconcan");
		itemExample.Classnames.Insert("expansionbread1");
		itemExample.Classnames.Insert("expansionbread2");
		itemExample.Classnames.Insert("expansionbread3");
		itemExample.Classnames.Insert("expansioncheese1");
		itemExample.Classnames.Insert("expansioncheese2");
		itemExample.Classnames.Insert("expansioncheese3");
		itemExample.Classnames.Insert("expansioncheese4");
		FreshieMarketItems.Insert(itemExample);

		Save();
	};

	void Save()
	{
		if (!FileExist(zenModFolder))
		{
			MakeDirectory(zenModFolder);
		}

		JsonFileLoader<FreshieSuppliesConfig>.JsonSaveFile(zenModFolder + zenConfigName, this);
	}
}

class FreshieMarketItem
{
	string ItemType;
	int MaxBuy;
	ref array<string> Classnames = new array<string>;
	ref map<string, int> PlayerBought = new map<string, int>;
}

ref FreshieSuppliesConfig m_FreshieSuppliesConfig;

static FreshieSuppliesConfig GetFreshieSuppliesConfig()
{
	if (!m_FreshieSuppliesConfig)
	{
		m_FreshieSuppliesConfig = new FreshieSuppliesConfig;
		m_FreshieSuppliesConfig.Load();
	}

	return m_FreshieSuppliesConfig;
};