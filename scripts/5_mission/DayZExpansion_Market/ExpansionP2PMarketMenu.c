modded class ExpansionP2PMarketMenu: ExpansionScriptViewMenu
{
	override protected void PlayObjectSound()
	{
		super.PlayObjectSound();

		#ifndef SERVER
		EffectSound sound;
		sound = SEffectManager.PlaySoundOnObject("Zen_Trader_SoundSet", GetGame().GetPlayer());
		if (sound)
			sound.SetSoundAutodestroy(true);
		#endif
	}
}