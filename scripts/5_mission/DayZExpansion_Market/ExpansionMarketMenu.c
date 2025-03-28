modded class ExpansionMarketMenu
{
	override void PlayMarketSound()
	{
		super.PlayMarketSound();

		#ifndef SERVER
		EffectSound sound;
		sound = SEffectManager.PlaySoundOnObject("Zen_Trader_SoundSet", GetGame().GetPlayer());
		if (sound)
			sound.SetSoundAutodestroy(true);
		#endif
	};

	override void MenuCallback(string itemClassName, ExpansionMarketResult result, int option1 = -1, int option2 = -1, Object object = NULL)
	{
		if (result == 6969)
		{
			ExpansionNotification("Can't buy!", "You already have a dog!", EXPANSION_NOTIFICATION_ICON_ERROR, COLOR_EXPANSION_NOTIFICATION_ERROR, 3, ExpansionNotificationType.MARKET).Create();
			return;
		}

		super.MenuCallback(itemClassName, result, option1, option2, object);
	}
}