modded class ExpansionMapMenu
{
	ref ExpansionMapMarkerPlayerArrow m_OurPlayerMarker;

	// Expansion only updates compass state when map is created for some reason, so if player drops compass or picks one up after opening map it doesn't affect their marker
	override void Refresh()
	{
		super.Refresh();

		if (!GetOurPlayerMarker())
			return;

		m_HasCompass = m_PlayerB.HasItemCompass() || m_PlayerB.HasItemPDA() || m_PlayerB.HasItemGPS_Zen();

		if (!m_HasCompass)
			m_OurPlayerMarker.Hide();
		else
			m_OurPlayerMarker.Show();
	}

	private bool GetOurPlayerMarker()
	{
		if (m_OurPlayerMarker)
			return true;

		if (!m_Markers || m_Markers.Count() == 0)
			return false;

		foreach (ExpansionMapWidgetBase marker : m_Markers)
		{
			if (marker.IsInherited(ExpansionMapMarkerPlayerArrow))
			{
				m_OurPlayerMarker = ExpansionMapMarkerPlayerArrow.Cast(marker);
				return true;
			}
		}

		return false;
	}
}