modded class MissionMainMenu
{
	override void PlayMusic()
	{
		StopMusic();
		return; // Don't play vanilla music
	}
}