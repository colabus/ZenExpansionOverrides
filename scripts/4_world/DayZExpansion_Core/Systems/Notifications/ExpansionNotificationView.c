#ifdef EXPANSIONMODCORE
modded class ExpansionNotificationView
{
	override void ShowNotification() 
	{
		super.ShowNotification();

		// For mission audio compatibility
		if (!NotificationUI.CheckPlayZenNotificationSoundset(m_Data.GetDetailText()))
		{
			SEffectManager.PlaySoundOnObject("Zen_NotifySoundset", GetGame().GetPlayer(), 0, 0.15, false);
		}
	}

	override bool CheckZenSoundSet()
	{
		return false;
	}
}
#endif