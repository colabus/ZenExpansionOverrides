modded class Zen_RaidAlarmStation
{
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionViewWeeklyQuestsOnRaidAlarm);
	}
}

modded class BaseRadio
{
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionViewWeeklyQuestsOnRaidAlarm);
	}
}