modded class ExpansionLampLightBase
{
	override protected void OnEnable()
	{
		super.OnEnable();

		if (IsMissionClient())
		{
			if (m_Light)
				m_Light.SetCastShadow(false);
		}
	}
}
