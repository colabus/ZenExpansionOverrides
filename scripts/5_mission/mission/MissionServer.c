modded class MissionServer
{
	override void OnInit()
	{
		super.OnInit();

		// Load config
		GetZenQuestExpConfig();
		GetZenQuestHideNpcConfig();
		GetZenCargoCrateConfig();
		GetZenExtraExpansionConfig();
		GetAngryGuardsConfig();

		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(CheckMilitaryLootCrates, 10000, false);
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(CheckContaminatedLootCrates, 11000, false);
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(LockLukowAirfieldBunkerPrison, 12000, false);

		// Spawn angry guards trigger
		ZenAngryGuardTrigger trigger = ZenAngryGuardTrigger.Cast(GetGame().CreateObjectEx("ZenAngryGuardTrigger", "5647.100586 180.683914 10611.924805", ECE_CREATEPHYSICS));
		if (trigger)
		{
			trigger.SetupZenAngryGuardTrigger(250);
		}
	}

	void LockLukowAirfieldBunkerPrison()
	{
		LukowPrisonKeys.LockPrisonDoors();
	}

	void CheckMilitaryLootCrates()
	{
		array<Object> nearestObjects;
		ZenCargoCrate milCrate;
		int i;

		if (Zen_ExpansionMilitaryCargo.MILITARY_COUNT < GetZenCargoCrateConfig().MaxMilitaryCrates)
		{
			milCrate = GetZenCargoCrateConfig().MilitaryCrateLocations.GetRandomElement();
			vector location = milCrate.Locations.GetRandomElement();

			nearestObjects = new array<Object>;
			GetGame().GetObjectsAtPosition3D(location, 1.0, nearestObjects, null);
			foreach (Object obj1 : nearestObjects)
			{
				if (obj1.IsInherited(Zen_ExpansionMilitaryCargo))
				{
					Print("[ZenCrates] NORMAL - ALREADY A CRATE HERE");
					continue; // There's already a crate here, just stop.
				}
			}

			Zen_ExpansionMilitaryCargo milCrateObj = Zen_ExpansionMilitaryCargo.Cast(GetGame().CreateObjectEx(milCrate.Type, location, ECE_PLACE_ON_SURFACE));
			if (!milCrateObj)
			{
				Print("[ZenCrates] ERROR: Could not spawn crate - " + milCrate.Type + " @ " + location);
				return;
			}

			milCrateObj.SetLifetime(GetZenCargoCrateConfig().CrateLifetime);
			milCrateObj.SpawnLoot();
			milCrateObj.SetPosition(location);

			Print("[ZenCrates] SPAWNED REGULAR MILITARY CRATE - Count=" + Zen_ExpansionMilitaryCargo.MILITARY_COUNT);
		}
		else
		{
			Print("[ZenCrates] Max count reached for Military Cargo: " + Zen_ExpansionMilitaryCargo.MILITARY_COUNT);
		}
	}

	void CheckContaminatedLootCrates()
	{
		array<Object> nearestObjects;
		ZenCargoCrate milCrate;
		int i;

		if (Zen_ExpansionMilitaryCargo.CONTAMINATED_COUNT < GetZenCargoCrateConfig().MaxContaminationCrates)
		{
			milCrate = GetZenCargoCrateConfig().ContaminationCrateLocations.GetRandomElement();
			vector location = milCrate.Locations.GetRandomElement();

			nearestObjects = new array<Object>;
			GetGame().GetObjectsAtPosition3D(location, 1.0, nearestObjects, null);
			foreach (Object obj2 : nearestObjects)
			{
				if (obj2.IsInherited(Zen_ExpansionMilitaryCargo_Contam))
				{
					Print("[ZenCrates] CONTAM - ALREADY A CRATE HERE");
					continue; // There's already a crate here, just stop.
				}
			}

			Zen_ExpansionMilitaryCargo_Contam milCrateContamObj = Zen_ExpansionMilitaryCargo_Contam.Cast(GetGame().CreateObjectEx(milCrate.Type, location, ECE_PLACE_ON_SURFACE));
			if (!milCrateContamObj)
			{
				Print("[ZenCrates] ERROR: Could not spawn crate - " + milCrate.Type + " @ " + location);
				return;
			}

			milCrateContamObj.SetLifetime(GetZenCargoCrateConfig().CrateLifetime);
			milCrateContamObj.SpawnLoot();
			milCrateContamObj.SetPosition(location);

			Print("[ZenCrates] SPAWNED CONTAMINATED MILITARY CRATE - Count=" + Zen_ExpansionMilitaryCargo.CONTAMINATED_COUNT);
		}
		else
		{
			Print("[ZenCrates] Max count reached for Contaminated Cargo: " + Zen_ExpansionMilitaryCargo.CONTAMINATED_COUNT);
		}
	}

	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity) 
	{
		super.InvokeOnConnect(player, identity);
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(SendZenExpansionHideQuestConfig, 1, false, player);
	}

	void SendZenExpansionHideQuestConfig(PlayerBase player)
	{
		if (!player || !player.GetIdentity())
			return;

		// Send client config
		Param1<ref ZenQuestHideNpcConfig> configParams = new Param1<ref ZenQuestHideNpcConfig>(GetZenQuestHideNpcConfig());
		GetRPCManager().SendRPC("RPC_ZXQST", "RPC_ReceiveZenQuestHideNpcConfig", configParams, true, player.GetIdentity());

		GetRPCManager().SendRPC("RPC_ZXPO", "RPC_ReceiveDonationsData", new Param1<ref array<ref SyberiaDonationRecord>>(GetDonationHighscoresConfig().DonationData), true, player.GetIdentity());
	
#ifdef SERVER
		array<Man> players = new array<Man>;
		g_Game.GetWorld().GetPlayerList(players);
		GetRPCManager().SendRPC("RPC_ZXPO", "RPC_ReceiveExpansionBookPlayerCountResponse", new Param3<int, int, int>(players.Count(), GetSyberiaCharacters().GetTotalPlayerCount(), GetSyberiaCharacters().GetActivePlayerCount()), true, player.GetIdentity());
#endif
	}
}