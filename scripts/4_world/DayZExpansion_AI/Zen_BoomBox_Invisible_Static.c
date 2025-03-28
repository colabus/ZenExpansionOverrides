modded class Zen_BoomBox_Invisible_Static
{
	void StartPlayingAgain()
	{
		// Scan for static boombox and see if it's playing first
		array<Object> nearbyObjects = new array<Object>;
		GetGame().GetObjectsAtPosition3D(GetPosition(), GetZenMusicConfig().StaticBoomboxTurnsOffInvisibleRange, nearbyObjects, NULL);

		foreach (Object obj : nearbyObjects)
		{
			if (obj.IsInherited(Zen_BoomBox_Static))
			{
				Zen_BoomBox_Static staticInvisBoombox = Zen_BoomBox_Static.Cast(obj);
				if (staticInvisBoombox && !staticInvisBoombox.DisableVicinityIcon())
				{
					if (staticInvisBoombox.IsPlayingSong())
					{
						return;
					}
				}
			}
		}

		PrepareForNewMusic(true);
	}
}