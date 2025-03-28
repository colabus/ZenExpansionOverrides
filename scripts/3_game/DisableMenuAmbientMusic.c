modded class DynamicMusicPlayerRegistry
{
	override protected void RegisterTracksMenu()
	{
		super.RegisterTracksMenu();

		// Don't allow any menu music, interferes with guitarist
		m_TracksMenu.Clear();
	}
}