// Spawn parts to make boats always useable on Livonia river
modded class ExpansionZodiacBoat
{
	override void EEInit()
	{
		super.EEInit();
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(ClearParts, 1000, false);
	}

	void ClearParts()
	{
		ItemBase glowPlug = ItemBase.Cast(FindAttachmentBySlotName("GlowPlug"));
		ItemBase truckBattery = ItemBase.Cast(FindAttachmentBySlotName("TruckBattery"));

		if (glowPlug)
		{
			glowPlug.UnlockFromParent();
			glowPlug.DeleteSafe();
		}

		if (truckBattery)
		{
			truckBattery.UnlockFromParent();
			truckBattery.DeleteSafe();
		}

		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(SpawnNewParts, 1000, false);
	}

	void SpawnNewParts()
	{
		ItemBase glowPlug = ItemBase.Cast(GetInventory().CreateInInventory("GlowPlug"));
		ItemBase truckBattery = ItemBase.Cast(GetInventory().CreateInInventory("TruckBattery"));

		if (glowPlug)
			glowPlug.LockToParent();

		if (truckBattery)
			truckBattery.LockToParent();

		Fill(CarFluid.FUEL, 200.0);
	}
}