modded class eAIBase
{
	static const int HEAL_SECS = 60; // Heal every 1 min
	float m_HealthCheckTicks = 0;

	override void DeferredInit()
	{
		super.DeferredInit();

		if (Expansion_IsQuestVIP())
		{
			// Lukow bunker teleport
			if (GetPosition()[1] >= 5000 && vector.Distance(GetPosition(), "4117.829590 5002.012207 10224.315430") < 100)
			{
				SetPosition("4117.060059 238.261215 10234.051758");
			}
		}
	}

	override void CommandHandler(float pDt, int pCurrentCommandID, bool pCurrentCommandFinished)
	{
		super.CommandHandler(pDt, pCurrentCommandID, pCurrentCommandFinished);

		m_HealthCheckTicks += pDt;

		if (m_HealthCheckTicks < HEAL_SECS)
			return;

		m_HealthCheckTicks = 0;

		// Add 5 hp
		if (GetHealth() != GetMaxHealth("GlobalHealth","Health"))
			AddHealth("GlobalHealth", "Health", 5);

		GetStatEnergy().Set(GetStatEnergy().GetMax());
		GetStatWater().Set(GetStatWater().GetMax());
	}

	bool m_VehicleHitSuspended = false;

	// Resets the flag to allow vehicle hits on zombies to count
	void ResetVehicleHit()
	{
		m_VehicleHitSuspended = false;
	}

	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

		if (source && ammo == "TransportHit" && !m_VehicleHitSuspended)
		{
			m_VehicleHitSuspended = true;
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(ResetVehicleHit, 1000, false);

			CarScript theCar = CarScript.Cast(source);
			if (theCar)
			{
				EntityAI objectToDamage = EntityAI.Cast(source.FindAttachmentBySlotName("SparkPlug"));
				if (!objectToDamage)
					objectToDamage = EntityAI.Cast(source.FindAttachmentBySlotName("GlowPlug"));
				if (!objectToDamage)
					objectToDamage = EntityAI.Cast(source.FindAttachmentBySlotName("CarBattery"));
				if (!objectToDamage)
					objectToDamage = EntityAI.Cast(source.FindAttachmentBySlotName("TruckBattery"));

				if (objectToDamage)
					objectToDamage.DecreaseHealth(objectToDamage.GetMaxHealth() + 1, false);
			}
		}
	}
}