modded class ExpansionClientSettings
{
	override bool Load()
	{
		bool loaded = super.Load();
		ShowNotifications = true;
		return loaded;
	}
}