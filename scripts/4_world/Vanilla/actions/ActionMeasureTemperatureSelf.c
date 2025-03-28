modded class ActionMeasureTemperatureSelf
{
	override void OnFinishProgressClient( ActionData action_data )
	{	
		super.OnFinishProgressClient(action_data);

		Thermometer thermometer = Thermometer.Cast(action_data.m_MainItem);
		if (thermometer)
		{
			action_data.m_Player.m_LastThermometerCheck = JMDate.Now(false).GetTimestamp();
		}
	}
}