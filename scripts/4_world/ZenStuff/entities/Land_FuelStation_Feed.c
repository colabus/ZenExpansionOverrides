modded class Land_FuelStation_Feed extends FuelStation
{
	override void DeferredInit()
	{
		super.DeferredInit();

		// Don't allow Sanctuary fuel pumps to explode
		if (GetGame().IsDedicatedServer() && vector.Distance(GetPosition(), "5638.12060546875 185.103515625 10607.1396484375") < 100)
			SetAllowDamage(false);

		// TEMPORARY FIX: WHEN EXPANSION OBJECTS ARE HIT BY FUEL PUMP EXPLOSION THE SERVER CRASHES, SO MAKE THEM INVINCIBLE FOR NOW 
		//SetAllowDamage(false);
	}
}