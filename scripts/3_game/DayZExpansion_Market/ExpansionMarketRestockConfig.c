class ExpansionMarketRestockConfig
{
	// Config location
	private const static string zenModFolder = "$profile:\\Zenarchist\\Expansion\\";
	private const static string zenConfigName = "ExpansionMarketRestockConfig.json";

	// Saved to json
	bool DebugOn = false;
	int RestockTimer = 3000;
	float RestockChance = 0.5; // 50%
	float RestockQuantity = 0.1; // 10 %
	autoptr array<string> IGNORE_ITEMS;
	autoptr array<ref ExpansionRestockSpecific> SPECIFIC_ITEMS;

	void Load()
	{
		// Don't load JSON on server
		if (!GetGame().IsDedicatedServer())
			return;

		if (FileExist(zenModFolder + zenConfigName))
		{
			JsonFileLoader<ExpansionMarketRestockConfig>.JsonLoadFile(zenModFolder + zenConfigName, this);
			return;
		}

		IGNORE_ITEMS = new array<string>;
		IGNORE_ITEMS.Insert("expansionsatchel");
		IGNORE_ITEMS.Insert("plastic_explosive");
		IGNORE_ITEMS.Insert("improvisedexplosive");
		IGNORE_ITEMS.Insert("dogpreview");

		SPECIFIC_ITEMS = new array<ref ExpansionRestockSpecific>;
		SPECIFIC_ITEMS.Insert(new ExpansionRestockSpecific("SparkPlug", 0.9, 0.2));

		Save();
	};

	void Save()
	{
		if (!FileExist(zenModFolder))
		{
			MakeDirectory(zenModFolder);
		}

		JsonFileLoader<ExpansionMarketRestockConfig>.JsonSaveFile(zenModFolder + zenConfigName, this);
	}

	void AddStockToZone(ExpansionMarketTraderZone zone)
	{
		bool skipThis;
		int newStockQuantity;
		int originalStockQuantity;
		ExpansionMarketItem marketItem;

		if (DebugOn)
			ZMPrint("[ZENEX] [" + zone.m_DisplayName + "] StockCount=" + zone.Stock.Count());

		for (int i = 0; i < zone.Stock.Count(); i++)
		{
			originalStockQuantity = zone.Stock.GetElement(i);
			skipThis = false;

			// Check ignore list
			string itemType = zone.Stock.GetKey(i);
			itemType.ToLower();
			foreach (string ignoreType : IGNORE_ITEMS)
			{
				ignoreType.ToLower();
				if (itemType.Contains(ignoreType))
					skipThis = true;
			}

			// Check static stock and validate item
			if (!skipThis)
			{
				marketItem = ExpansionMarketCategory.GetGlobalItem(itemType, false);
				if (marketItem == NULL || marketItem.IsStaticStock() || originalStockQuantity >= marketItem.MaxStockThreshold)
				{
					skipThis = true;
				}
			}

			if (skipThis)
			{
				//bool isNull = marketItem == NULL;
				//if (DebugOn)
				//	ZMPrint("[ZENEX] Skip item: " + itemType + " / stock=" + zone.Stock.GetElement(i) + " - " + isNull);
				continue;
			}

			// Check specific qty config
			foreach (ExpansionRestockSpecific specific : SPECIFIC_ITEMS)
			{
				string cname = specific.ClassName;
				cname.ToLower();
				if (itemType.Contains(cname))
				{
					if (Math.RandomFloat01() <= specific.RestockChance)
					{
						newStockQuantity = Math.Round(marketItem.MaxStockThreshold * specific.RestockQuantity);
						if (newStockQuantity <= 0)
							newStockQuantity = 1;

						zone.AddStock(itemType, newStockQuantity);
						skipThis = true;
					}
				}
			}

			// General config
			if (!skipThis && Math.RandomFloat01() <= RestockChance)
			{
				newStockQuantity = Math.Round(marketItem.MaxStockThreshold * RestockQuantity);

				// 1% chance to restock everything entirely
				if (Math.RandomFloat01() < 0.01)
					newStockQuantity = marketItem.MaxStockThreshold;

				if (newStockQuantity <= 0)
					newStockQuantity = 1;

				zone.AddStock(itemType, newStockQuantity);

				if (DebugOn)
					ZMPrint("[ZENEX] [" + zone.m_DisplayName + "] Restock: " + itemType + " +" + newStockQuantity + " (was " + originalStockQuantity + ", now " + zone.Stock.GetElement(i) + ", max " + marketItem.MaxStockThreshold + ")");
			}

			zone.Update();
			zone.Save();
		}
	}
}

class ExpansionRestockSpecific
{
	string ClassName;
	float RestockChance = 0.5;
	float RestockQuantity = 0.1;

	void ExpansionRestockSpecific(string p_name, float p_chance, float p_qty)
	{
		ClassName = p_name;
		RestockChance = p_chance;
		RestockQuantity = p_qty;
	}
}

ref ExpansionMarketRestockConfig m_ExpansionMarketRestockConfig;

static ExpansionMarketRestockConfig GetExpansionMarketRestockConfig()
{
	if (!m_ExpansionMarketRestockConfig)
	{
		m_ExpansionMarketRestockConfig = new ExpansionMarketRestockConfig;
		m_ExpansionMarketRestockConfig.Load();
	}

	return m_ExpansionMarketRestockConfig;
};