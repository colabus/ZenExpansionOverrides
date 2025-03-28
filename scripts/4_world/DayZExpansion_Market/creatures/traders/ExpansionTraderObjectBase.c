modded class ExpansionTraderObjectBase
{
	static ref array<string> UNIQUE_MARKET_ZONES = new array<string>;
	ref Timer m_MarketUpdateTimer;

	override void LoadTraderHost(string fileName)
	{
		super.LoadTraderHost(fileName);

		if (m_TraderZone != NULL)
		{
			if (UNIQUE_MARKET_ZONES.Find(m_TraderZone.m_DisplayName) == -1)
			{
				//ZMPrint("[ZENEX] Found trader zone - " + m_TraderZone.m_DisplayName);
				
				UNIQUE_MARKET_ZONES.Insert(m_TraderZone.m_DisplayName);

				if (!m_MarketUpdateTimer)
				{
					ZenRestock();

					m_MarketUpdateTimer = new Timer();
					m_MarketUpdateTimer.Run(GetExpansionMarketRestockConfig().RestockTimer, this, "ZenRestock", NULL, true);
				}
			}
		}
	}

	protected void ZenRestock()
	{
		//ZMPrint("[ZENEX] ZenRestock()");
		GetExpansionMarketRestockConfig().AddStockToZone(m_TraderZone);
	}
};