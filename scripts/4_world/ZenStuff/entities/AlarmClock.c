modded class AlarmClock_ColorBase
{
	override void DropGrenade()
	{
		if (vector.Distance(GetPosition(), "5647.100586 180.683914 10611.924805") < 300)
			return;

		super.DropGrenade();
	}
}