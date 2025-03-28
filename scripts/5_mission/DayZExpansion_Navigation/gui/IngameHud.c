modded class IngameHud
{
	override void UpdateCompass()
	{
		if (!m_Player)
			return;

		if (GetCompassState())
		{
			#ifdef NAMALSK_SURVIVAL
			Zen_NavHelmet helm = Zen_NavHelmet.Cast(m_Player.FindAttachmentBySlotName("Eyewear")); // requires ZenWinterLivonia mod
			if (!helm || helm.IsRuined() || !helm.GetCompEM() || !helm.GetCompEM().IsWorking())
			{
				CompassHide();
				m_HasCompassItem = false;
				return;
			}
			#endif

			if (!m_Player.IsInVehicle() || !m_Player.HasItemCompass())
            {
				CompassHide();
				m_HasCompassItem = false;
				return;
            }
		}
		else
		{
			if (m_Player.IsInVehicle())
            {
				if (m_Player.HasItemCompass())
				{
					CompassShow();
					return;
				}
            }

			#ifdef NAMALSK_SURVIVAL
			Zen_NavHelmet helm = Zen_NavHelmet.Cast(m_Player.FindAttachmentBySlotName("Eyewear"));
			if (helm && !helm.IsRuined() && helm.GetCompEM() && helm.GetCompEM().IsWorking())
			{
				CompassShow();
				return;
			}
			#endif
		}
	}

	override void UpdateGPS()
	{
		//! If GPS is visable and player has no GPS item then close the GPS overlay when setting is enabled
		if (GetExpansionSettings().GetMap().NeedGPSItemForKeyBinding && GetGPSState())
		{
			if (!m_Player)
				return;

			if (!m_Player.HasItemPDA() && m_HasGPSItem)
			{
				m_HasGPSItem = false;
				ToggleHUDGPS();
			}
		}
	}
};