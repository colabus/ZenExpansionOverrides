class LukowPrisonKeys extends HandcuffKeys 
{
	void LukowPrisonKeys()
	{
		SetAllowDamage(false);
	}

	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionUnlockLukowPrison);
	}

	static void LockPrisonDoors()
	{
		// Lock bunker prison door
		array<Object> nearest_objects = new array<Object>;
		GetGame().GetObjectsAtPosition3D("4103.509277 5002.064941 10177.916016", 2, nearest_objects, NULL);

		for (int i = 0; i < nearest_objects.Count(); ++i)
		{
			Building building = Building.Cast(nearest_objects.Get(i));

			if (building != NULL && building.GetType().Contains("Land_Underground_Storage_Prison"))
			{
				for (int x = 0; x < 5; x++)
				{
					building.LockDoor(x, true); // Index 4 = prison cell
				}
			}
		}
	}
}