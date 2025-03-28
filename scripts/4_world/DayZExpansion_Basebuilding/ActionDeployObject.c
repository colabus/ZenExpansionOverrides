modded class ActionDeployObject
{
	static const ref array<string> ITEM_WHITELIST =
	{
		"ExpansionSatchel",
		"Plastic_Explosive",
		"LandMineTrap",
		"BearTrap",
		"FishNetTrap",
		"SmallFishTrap",
		"TripwireTrap",
		"ZenNote",
		"Paper",
		"CargoDroneKit",
		"SimpleDroneKit",
		"ReconDroneKit",
		"ReconDroneKit_ARCTIC",
		"ReconDroneKit_MULTICAMO",
		"ReconDroneKit_MULTICAMODARK",
		"ClaymoreMine",
		"Fireplace"
	};

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!super.ActionCondition(player, target, item))
		{
			player.PlacingCancelLocal();
			player.PlacingCancelServer();
			return false;
		}

#ifdef SERVER
		vector playerPos = player.GetPosition();
		array<ref array<float>> safeSpots = GetContaminatedSafeZoneConfig().SafePositions;
		vector closest_safe_pos = MiscGameplayFunctions.GetClosestSafePos(player.GetPosition(), safeSpots);
		closest_safe_pos[1] = GetGame().SurfaceY(closest_safe_pos[0], closest_safe_pos[2]);

		if (vector.Distance(playerPos, closest_safe_pos) <= 50)
		{
			ExpansionNotification("CONTAMINATED AREA SAFE ZONE", "You can't build within 50 meters of a dynamic contaminated area zone safe zone.").Error(player.GetIdentity());
			player.PlacingCancelLocal();
			player.PlacingCancelServer();
			return false;
		}
#endif

		// Check build limit for territory flag
		TerritoryFlag theFlag = player.ZenGetExpansionTerritoryModule().GetFlagAtPosition3D(player.GetPosition(), GetExpansionSettings().GetTerritory().TerritorySize);
		if (theFlag && !theFlag.CanBuildMore())
		{
			foreach (string deployable: ITEM_WHITELIST)
			{
				if (item.IsKindOf(deployable))
					return true;
			}

			string objectsText = " " + theFlag.m_CurrentObjectCount + "/" + ZenExtraExpansionConfig.MaxBasebuildingObjects + " total allowed base objects and";
			string cargoText = " " + theFlag.m_CurrentCargoItemCount + "/" + ZenExtraExpansionConfig.MaxCargoItems + " cargo items.";
			string msgTxt = "Cannot build! Territory contains" + objectsText + cargoText + "\n\nThis limit exists to maintain server performance.\n\nDismantle non-essential objects to continue building.";
			ExpansionNotification("LIMIT REACHED", msgTxt).Error(player.GetIdentity());
			player.PlacingCancelLocal();
			player.PlacingCancelServer();
			return false;
		}

		if (item.GetType() == "BBP_Step_Ladder_Kit")
		{
			if (!player.IsInsideOwnTerritory())
			{
				ExpansionNotification(new StringLocaliser("BASE TERRITORY", "BASE TERRITORY"), "You can only deploy step ladders inside your own Territory!").Error(player.GetIdentity());
				player.PlacingCancelLocal();
				player.PlacingCancelServer();
				return false;
			}
		}

		return super.ActionCondition(player, target, item);
	}

	//! LAST UPDATED: 16th August 2024
	/*
	override static bool Expansion_CheckDeploy(PlayerBase player, ActionTarget target, ItemBase item, bool notify = false)
	{
		//if (player.Expansion_IsInSafeZone())
		//	return false;

		if (!GetExpansionSettings().GetBaseBuilding(false).IsLoaded() || !GetExpansionSettings().GetTerritory(false).IsLoaded())
			return false;

		bool isDisallowedOutsideBuildZone;
		bool isDisallowedOutsideTerritory;
		bool isDisallowedInEnemyTerritory;
		bool isDisallowedNearEnemyTerritory;
		string title;
		string text;

		//! @note zones are not sent to client (intentional)
		if (GetGame().IsServer() && GetExpansionSettings().GetBaseBuilding().Zones.Count())
		{
			ExpansionBuildNoBuildZone zone = player.GetBuildNoBuildZone();

			if (zone)
			{
				//! Player is inside zone

				bool isItemAllowed = !zone.IsWhitelist;

				foreach(string item_name : zone.Items)
				{
					if ((item.CanMakeGardenplot() && item_name == "GardenPlot") || item.IsKindOf(item_name))
					{
						isItemAllowed = zone.IsWhitelist;
						break;
					}
				}

				if (!isItemAllowed)
				{
					text = zone.CustomMessage;

					if (GetExpansionSettings().GetBaseBuilding().ZonesAreNoBuildZones)
					{
						title = "STR_EXPANSION_NOBUILD_ZONE_TITLE";
						if (!text)
							text = "STR_EXPANSION_NOBUILD_ZONE_ITEM_DISALLOWED";
					}
					else
					{
						title = "STR_EXPANSION_BUILD_ZONE_TITLE";
						if (!text)
							text = "STR_EXPANSION_BUILD_ZONE_ITEM_DISALLOWED";
					}

					ExpansionNotification(new StringLocaliser(title, zone.Name), new StringLocaliser(text)).Error(player.GetIdentity());

					return false;
				}
			}
			else if (!GetExpansionSettings().GetBaseBuilding().ZonesAreNoBuildZones)
			{
				//! Zones are "build" zones, so if player isn't inside one, disallow placing if not whitelisted
				isDisallowedOutsideBuildZone = true;
			}
		}

		if (GetExpansionSettings().GetTerritory().EnableTerritories)
		{
			if (GetExpansionSettings().GetBaseBuilding().AllowBuildingWithoutATerritory == true && !isDisallowedOutsideBuildZone)
			{
				//! Flag can be placed if outside any territory/perimeter or if inside own territory/perimeter
				//! Other items can be placed if not in enemy territory or if item is whitelisted

				if (player.IsInTerritory())
				{
					isDisallowedInEnemyTerritory = !CanDeployInTerritory(player, item);
				}
				else if (item.IsInherited(TerritoryFlagKit) && player.IsInPerimeter() && !player.IsInsideOwnPerimeter())
				{
					isDisallowedNearEnemyTerritory = true;
				}
			}
			else
			{
				//! Flag can be placed if outside any territory/perimeter and is whitelisted, if inside enemy territory and is whitelisted, or if inside own territory/perimeter
				//! Other items can only be placed if item is whitelisted

				if (player.IsInTerritory())
				{
					isDisallowedInEnemyTerritory = !CanDeployInTerritory(player, item);
				}
				else if (GetGame().IsServer())
				{
					//! @note deployables are not sent to client (intentional)
					isDisallowedOutsideTerritory = !GetExpansionSettings().GetBaseBuilding().AllowBuildingWithoutATerritory;
					foreach(string deployable : GetExpansionSettings().GetBaseBuilding().DeployableOutsideATerritory)
					{
						if ((item.CanMakeGardenplot() && deployable == "GardenPlot") || item.IsKindOf(deployable))
						{
							isDisallowedOutsideBuildZone = false;
							isDisallowedOutsideTerritory = false;
							if (item.IsInherited(TerritoryFlagKit) && player.IsInPerimeter() && !player.IsInsideOwnPerimeter())
							{
								isDisallowedNearEnemyTerritory = true;
							}
							break;
						}
					}
				}
			}
		}

		if (isDisallowedOutsideTerritory)
		{
			title = "STR_EXPANSION_TERRITORY_TITLE";
			text = "STR_EXPANSION_TERRITORY_TERRITORY_REQUIRED";
		}
		else if (isDisallowedInEnemyTerritory)
		{
			title = "STR_EXPANSION_TERRITORY_TITLE";
			text = "STR_EXPANSION_TERRITORY_ENEMY_TERRITORY";
		}
		else if (isDisallowedNearEnemyTerritory)
		{
			title = "STR_EXPANSION_TERRITORY_TITLE";
			text = "STR_EXPANSION_TERRITORY_ENEMY_TERRITORY_NEAR";
		}
		else if (isDisallowedOutsideBuildZone)
		{
			title = "STR_EXPANSION_BUILD_ZONE_REQUIRED_TITLE";
			text = GetExpansionSettings().GetBaseBuilding().BuildZoneRequiredCustomMessage;
			if (!text)
				text = "STR_EXPANSION_BUILD_ZONE_REQUIRED";
		}
		else
		{
			return true;
		}

		if (notify)
			ExpansionNotification(title, text).Error(player.GetIdentity());

		return false;
	}
	*/
}