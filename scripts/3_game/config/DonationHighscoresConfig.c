class DonationHighscoresConfig
{
	// Config location
	private const static string zenModFolder = "$profile:\\Zenarchist\\Expansion\\";
	private const static string zenConfigName = "DonationsHighscore.json";

	// Config data
	ref array<ref SyberiaDonationRecord> DonationData = new array<ref SyberiaDonationRecord>;

	// Load config file or create default file if config doesn't exsit
	void Load()
	{
		if (FileExist(zenModFolder + zenConfigName))
		{
			// If config exists, load file and sort
			JsonFileLoader<DonationHighscoresConfig>.JsonLoadFile(zenModFolder + zenConfigName, this);
			SortDonations();
			return;
		}

		DonationData.Insert(new SyberiaDonationRecord("Test", 100.69, "2/2/24"));

		// Save config
		Save();
	};

	// Save config
	void Save()
	{
		if (!FileExist(zenModFolder))
		{
			// If config folder doesn't exist, create it.
			MakeDirectory(zenModFolder);
		}

		// Save JSON config
		JsonFileLoader<DonationHighscoresConfig>.JsonSaveFile(zenModFolder + zenConfigName, this);
	}

	void SortDonations()
	{
		int i;
		int j;
		int min_idx;

		for (i = 0; i < DonationData.Count() - 1; i++) 
		{
			min_idx = i;
			for (j = i + 1; j < DonationData.Count(); j++) 
			{
				SyberiaDonationRecord record1 = DonationData.Get(min_idx);
				SyberiaDonationRecord record2 = DonationData.Get(j);

				if (record2.Amount > record1.Amount)
					min_idx = j;
			}

			DonationData.SwapItems(min_idx, i);
		}
	}
}

class SyberiaDonationRecord
{
	string Name;
	float Amount;

	void SyberiaDonationRecord(string n, float a, string d)
	{
		Name = n;
		Amount = a;
	}
};

ref DonationHighscoresConfig m_DonationHighscoresConfig;

static DonationHighscoresConfig GetDonationHighscoresConfig()
{
	if (!m_DonationHighscoresConfig)
	{
		m_DonationHighscoresConfig = new DonationHighscoresConfig;

		// Only load JSON config on the server
		if (GetGame().IsDedicatedServer())
		{
			m_DonationHighscoresConfig.Load();
		}
	}

	return m_DonationHighscoresConfig;
};
