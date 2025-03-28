class CfgPatches
{
	class ZenExpansionOverrides
	{
		requiredVersion = 0.1;
		units[] = {};
		requiredAddons[] =
		{
			"DZ_Data",
			"DZ_Scripts",
			"DZ_Characters_Tops",
			"DayZExpansion_Core_Scripts",
			"DayZExpansion_Book_Scripts", // For modifying some book stuff (eg. preview item/description)
			"DayZExpansion_Navigation_Scripts", // For disabling K key and other map/compass/gps hud stuff
			"DayZExpansion_Quests_Dta_Core", // For adding extra quest items
			"DayZExpansion_Quests_Scripts", // For disabling O key
			"DayZExpansion_Market_Objects", // For adding trader objects
			"DayZExpansion_P2PMarket_Objects", // For adding p2p trader objects
			"DayZExpansion_Market_Scripts", // For adding stock on restarts
			"DayZExpansion_Weapons_Scripts", // For turning laser beams on when added to AI
			"DayZExpansion_Objects_BaseBuilding_Data", // For overriding BB descriptions
			"DayZExpansion_Objects_BaseBuilding_Items", // For adding HP to ExpansionCodeLocks
			"DayZExpansion_Sounds_UI", // For overriding Expansion notification sound with my own
			"DayZExpansion_Objects_Structures_Props", // For extra flags
			"DayZExpansion_Vehicles_GUI", // For fixing radiator temp color
			"DayZExpansion_Core_Objects_Currencies", // For gold/silver bars
			"DayZExpansion_Vehicles_Ground_UAZ", // For tire rack
			"DayZExpansion_Vehicles_Ground_LandRover", // For tire rack
			"DayZExpansion_Weapons_Sniper_AWM", // To make magazine larger
			"SyberiaScripts", // For PDA gps
			"cabin_mod",
			"MoreDoors", 
			"Dayz_Dog", // For dog on logout screen
			"ZenModPack", // For anti-combat log code + for rune burying quest
			"ZenExpansionAudioAI_Scripts", // For market power outage stuff
		};
	};
};

class CfgMods
{
	class ZenExpansionOverrides
	{
		dir = "ZenExpansionOverrides";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "ZenExpansionOverrides";
		credits = "";
		author = "Zenarchist";
		authorID = "0";
		version = "1.0";
		extra = 0;
		type = "mod";
		dependencies[] = { "Game","World","Mission" };
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = { "ZenExpansionOverrides/scripts/3_game" };
			};
			class worldScriptModule
			{
				value = "";
				files[] = { "ZenExpansionOverrides/scripts/4_World" };
			};
			class missionScriptModule
			{
				value = "";
				files[] = { "ZenExpansionOverrides/scripts/5_mission" };
			};
		};
	};
};

class CfgVehicles
{
	class HouseNoDestruct;
	class Inventory_Base;
	class MoreDoorKitBase;
	class ExpansionKitLarge;
	class ExpansionBaseBuilding;
	class Flag_Base;
    class Armband_ColorBase;
	class CarWheel;
	class Truck_01_WheelDouble;
	class Armband_DoubleColorBase;

	class Zen_BldrStaticMap : HouseNoDestruct
	{
		scope = 1;
		model = "ZenModPack\data\models\woodreserves\zen_woodreserve.p3d";
	};
	class Zen_BldrStaticMap_Debug : Zen_BldrStaticMap
	{
		scope = 1;
		model = "ZenModPack\data\models\woodreserves\zen_woodreserve_debug.p3d";
	};

	// Used for calling airdrops
	class Zen_AirdropRadar_Static : HouseNoDestruct
	{
		scope = 1;
		model = "ZenModPack\data\models\RaidDish\radar.p3d";
		hiddenSelections[] = { "texture" };
		hiddenSelectionsTextures[] = { "ZenModPack\data\textures\raiddish\radar_co.paa" };
	};

	class ExpansionCircuitBoardBase;
	class ExpansionCircuitBoard_Airdrop : ExpansionCircuitBoardBase
	{
		scope = 2;
		displayName = "Circuit Board - MK3";
		descriptionShort = "I think I can use this to repair the radar dishes usually found at the top of radio towers and call in an airdrop.";
		model = "DayZExpansion\Core\Objects\CircuitBoard\CircuitBoard.p3d";
		hiddenSelections[] =
		{
			"camo"
		};
		hiddenSelectionsTextures[] =
		{
			"ZenExpansionOverrides\data\textures\circuit_board_airdrop_co.paa"
		};
		hiddenSelectionsMaterials[] =
		{
			"DayZExpansion\Core\Objects\CircuitBoard\data\circuit_board.rvmat"
		};
	};

	class Expansion_Landrover_Wheel: CarWheel
	{
		inventorySlot[] += 
		{  
			"ZenTireRack1",
			"ZenTireRack2",
			"ZenTireRack3",
			"ZenTireRack4",
			"ZenTireRack5",
			"ZenTireRack6",
			"ZenTireRack7",
			"ZenTireRack8"
		};
	};
	class ExpansionUAZWheel: CarWheel
	{
		inventorySlot[] += 
		{  
			"ZenTireRack1",
			"ZenTireRack2",
			"ZenTireRack3",
			"ZenTireRack4",
			"ZenTireRack5",
			"ZenTireRack6",
			"ZenTireRack7",
			"ZenTireRack8"
		};
	};

	class ExpansionMoneyBar_Base;
	class ExpansionSilverBar: ExpansionMoneyBar_Base
	{
		scope=2;
		weight=1000;
		canBeSplit=0;
		varQuantityInit=1;
		varQuantityMin=0;
		varQuantityMax=1;
		varQuantityDestroyOnMin=1;
		varStackMax=1;
		descriptionShort="An ancient form of storing wealth. Even in the apocalypse, this thing is valuable - to the tune of about 1,000 nails.";
	
	};
	class ExpansionGoldBar: ExpansionMoneyBar_Base
	{
		scope=2;
		weight=1000;
		canBeSplit=0;
		varQuantityInit=1;
		varQuantityMin=0;
		varQuantityMax=1;
		varQuantityDestroyOnMin=1;
		varStackMax=1;
		descriptionShort="An ancient form of storing wealth. Even in the apocalypse, this thing is valuable - to the tune of about 5,000 nails.";
	};

	// EXPANSION FLAGS -> Add 'color' config. Armband recipe spawns item as: "Armband_" + color.
	class Flag_ZenYellowKing: Flag_Base
	{
		scope=2;
		hiddenSelectionsTextures[]=
		{
			"\ZenExpansionOverrides\data\textures\flag_yellowking_co.paa"
		};
		color = "ZenYellowKing";
	};
	/*class Armband_ZenYellowKing: Armband_ColorBase
	{
        scope = 2;
		descriptionShort = "An armband worn by a member of the Yellow King's bandit group. Probably worth some money at the Black Market trader...";
        hiddenSelectionsTextures[] =
        {
            "\ZenExpansionOverrides\data\textures\flag_yellowking_co.paa",
            "\ZenExpansionOverrides\data\textures\flag_yellowking_co.paa",
            "\ZenExpansionOverrides\data\textures\flag_yellowking_co.paa",
            "\ZenExpansionOverrides\data\textures\flag_yellowking_co.paa",
            "\ZenExpansionOverrides\data\textures\flag_yellowking_co.paa",
            "\ZenExpansionOverrides\data\textures\flag_yellowking_co.paa",
            "\ZenExpansionOverrides\data\textures\flag_yellowking_co.paa",
            "\ZenExpansionOverrides\data\textures\flag_yellowking_co.paa",
            "\ZenExpansionOverrides\data\textures\flag_yellowking_co.paa"
        };
	};*/

	class Armband_DoubleZenYellowKing: Armband_DoubleColorBase
	{
		scope=2;
		descriptionShort = "An armband worn by a member of the Yellow King's bandit group. Probably worth some money at the Black Market trader...";
        hiddenSelectionsTextures[]=
		{
			"\ZenExpansionOverrides\data\textures\flag_yellowking_co.paa",
            "\ZenExpansionOverrides\data\textures\flag_yellowking_co.paa",
            "\ZenExpansionOverrides\data\textures\flag_yellowking_co.paa",
            "\ZenExpansionOverrides\data\textures\flag_yellowking_co.paa",
            "\ZenExpansionOverrides\data\textures\flag_yellowking_co.paa",
            "\ZenExpansionOverrides\data\textures\flag_yellowking_co.paa",
            "\ZenExpansionOverrides\data\textures\flag_yellowking_co.paa",
            "\ZenExpansionOverrides\data\textures\flag_yellowking_co.paa",
            "\ZenExpansionOverrides\data\textures\flag_yellowking_co.paa"
		};
	};

	class M65Jacket_ColorBase;
	class M65Jacket_ZenYellowKing: M65Jacket_ColorBase
	{
		scope=2;
		hiddenSelectionsTextures[]=
		{
			"\ZenExpansionOverrides\data\textures\M65_Jacket_yk_co.paa",
			"\ZenExpansionOverrides\data\textures\M65_Jacket_yk_co.paa",
			"\ZenExpansionOverrides\data\textures\M65_Jacket_yk_co.paa"
		};
	};
	class RidersJacket_ColorBase;
	class RidersJacket_ZenYellowKing: RidersJacket_ColorBase
	{
		scope=2;
		visibilityModifier=0.85000002;
		hiddenSelectionsTextures[]=
		{
			"\ZenExpansionOverrides\data\textures\Riders_Jacket_yk_co.paa",
			"\ZenExpansionOverrides\data\textures\Riders_Jacket_yk_co.paa",
			"\ZenExpansionOverrides\data\textures\Riders_Jacket_yk_co.paa"
		};
	};
	class BomberJacket_ColorBase;
	class BomberJacket_ZenYellowKing: BomberJacket_ColorBase
	{
		scope=2;
		hiddenSelectionsTextures[]=
		{
			"\ZenExpansionOverrides\data\textures\BomberJacket_yk_co.paa",
			"\ZenExpansionOverrides\data\textures\BomberJacket_yk_co.paa",
			"\ZenExpansionOverrides\data\textures\BomberJacket_yk_co.paa"
		};
	};


	class Flag_ZenLoneWolf: Flag_Base
	{
		scope=2;
		hiddenSelectionsTextures[]=
		{
			"\ZenExpansionOverrides\data\textures\flag_lonewolf_co.paa"
		};
		color = "ZenLoneWolf";
	};
	class Armband_ZenLoneWolf: Armband_ColorBase
	{
        scope = 2;
		descriptionShort = "An armband worn by a Lone Wolf survivor.";
        visibilityModifier = 0.5;
        hiddenSelectionsTextures[] =
        {
            "\ZenExpansionOverrides\data\textures\flag_lonewolf_co.paa",
            "\ZenExpansionOverrides\data\textures\flag_lonewolf_co.paa",
            "\ZenExpansionOverrides\data\textures\flag_lonewolf_co.paa",
            "\ZenExpansionOverrides\data\textures\flag_lonewolf_co.paa",
            "\ZenExpansionOverrides\data\textures\flag_lonewolf_co.paa",
            "\ZenExpansionOverrides\data\textures\flag_lonewolf_co.paa",
            "\ZenExpansionOverrides\data\textures\flag_lonewolf_co.paa",
            "\ZenExpansionOverrides\data\textures\flag_lonewolf_co.paa",
            "\ZenExpansionOverrides\data\textures\flag_lonewolf_co.paa"
        };
		kitDisplay="Armband_ZenLoneWolf";
	};
	class Flag_ZenLoneWolfBlack: Flag_Base
	{
		scope=2;
		hiddenSelectionsTextures[]=
		{
			"\ZenExpansionOverrides\data\textures\flag_lonewolf_black_co.paa"
		};
		color = "ZenLoneWolfBlack";
	};
	class Armband_ZenLoneWolfBlack: Armband_ColorBase
	{
        scope = 2;
		descriptionShort = "An armband worn by a Lone Wolf survivor.";
        visibilityModifier = 0.5;
        hiddenSelectionsTextures[] =
        {
            "\ZenExpansionOverrides\data\textures\flag_lonewolf_black_co.paa",
            "\ZenExpansionOverrides\data\textures\flag_lonewolf_black_co.paa",
            "\ZenExpansionOverrides\data\textures\flag_lonewolf_black_co.paa",
            "\ZenExpansionOverrides\data\textures\flag_lonewolf_black_co.paa",
            "\ZenExpansionOverrides\data\textures\flag_lonewolf_black_co.paa",
            "\ZenExpansionOverrides\data\textures\flag_lonewolf_black_co.paa",
            "\ZenExpansionOverrides\data\textures\flag_lonewolf_black_co.paa",
            "\ZenExpansionOverrides\data\textures\flag_lonewolf_black_co.paa",
            "\ZenExpansionOverrides\data\textures\flag_lonewolf_black_co.paa"
        };
		kitDisplay="Armband_ZenLoneWolfBlack";
	};

	class ShelterKit: Inventory_Base
	{
		kitDisplay="ShelterStick";
	};
	class Cabin_Kit: Inventory_Base
	{
		kitDisplay="Prefab_Cabin";
	};
	class Zen_CamoShelterKit : Inventory_Base
	{
		kitDisplay="Zen_ImprovisedShelter";
	};

	class MoreDoorSmallKit: MoreDoorKitBase
    {
		kitDisplay="MoreDoorSmall";
	};
	class MoreDoorBarricadeKit: MoreDoorKitBase
    {
		kitDisplay="MoreDoorBarricade";
	};

	class FenceKit: Inventory_Base
	{
		kitDisplay="Fence";
	};
	class WatchtowerKit: Inventory_Base
	{
		kitDisplay="Watchtower";
	};

	class TerritoryFlagKit: Inventory_Base
	{
		kitDisplay="TerritoryFlag";
	};

	class ExpansionWallKit: ExpansionKitLarge
	{
		kitDisplay="ExpansionWall6x3";
	};
	class ExpansionWallBase: ExpansionBaseBuilding
	{
		descriptionShort="Used to craft doors, walls, gates & windows. Foundation: 2x 3M Lumber | Frame: 5 Wooden Planks + 15 Nails | Wall/Door/Gate: 5 Wooden Planks + 15 Nails | Window: 10 Wooden Planks, 2x 3M Lumber, 30 Nails";
	};
	class ExpansionFloorKit: ExpansionKitLarge
	{
		kitDisplay="ExpansionFloor3x6";
	};
	class ExpansionFloorBase: ExpansionBaseBuilding
	{
		descriptionShort="Used to craft floors and roofs. Foundation: 4x 3M Lumber | Frame: 5 Wooden Planks + 15 Nails | Wall/Door: 5 Wooden Planks + 15 Nails";
	}
	class ExpansionStairKit: ExpansionKitLarge
	{
		kitDisplay="ExpansionStairS1_5x3x3";
	};
	class ExpansionStairBase: ExpansionKitLarge
	{
		descriptionShort="Used to craft stairs. Foundation: 4x 3M Lumber | Frame: 15 Wooden Planks + 45 Nails";
	};
	class ExpansionRampKit: ExpansionKitLarge
	{
		kitDisplay="ExpansionRamp3x1_5x6";
	};
	class ExpansionRampBase: ExpansionKitLarge
	{
		descriptionShort="Used to craft ramps. Foundation: 2x 3M Lumber | Frame: 5 Wooden Planks + 15 Nails | Ramp: 5 Wooden Planks + 15 Nails";
	};
	class ExpansionBarbedWireKit: ExpansionKitLarge
	{
		kitDisplay="ExpansionBarbedWire";
	};
	class ExpansionBarbedWire: ExpansionKitLarge
	{
		descriptionShort="This is used to keep the rabbits out";
	};

	// Quest stuff 
	class Zen_LukowQuestTrashPile : HouseNoDestruct
	{
		scope = 1;
		model = "ZenModPack\data\models\chickencoops\zen_coop.p3d";
	};

	// Hermit
	class ZenNote;
	class Zen_HermitQuestNote : ZenNote
	{
		scope = 2;
		displayName = "Blood-stained Note";
		descriptionShort = "It's a blood-stained note left by the hermit...";
	};
	class Zen_HermitQuestDoor: HouseNoDestruct
	{
		scope=1;
		model="\DZ\structures\specific\prison\proxy\prison_maincastle_celldoors.p3d";
	};
	class Zen_HermitQuestTent: HouseNoDestruct
	{
		scope=1;
		hiddenSelections[]=
		{
			"bags",
			"camo",
			"xlights_glass_r",
			"xlights_glass_g",
			"xlights_glass_b",
			"xlights_glass_y"
		};
		hiddenSelectionsTextures[]=
		{
			"#(argb,8,8,3)color(0.470588,0.470588,0.470588,1.0,co)",
			"dz\gear\camping\data\tent_pristine_co.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"dz\gear\camping\data\tent_medium_packed.rvmat",
			"dz\gear\camping\data\tent_medium_pitched.rvmat"
		};
		model="\DZ\gear\camping\MediumTent.p3d";
	};

	// Underground bunker 
	class Zen_ContaminatedZoneBunkerEntrance1 : HouseNoDestruct
	{
		scope = 1;
		model = "ZenModPack\data\models\chickencoops\zen_coop2.p3d";
	};
	class Zen_ContaminatedZoneBunkerEntrance2 : HouseNoDestruct
	{
		scope = 1;
		model = "ZenModPack\data\models\chickencoops\zen_coop2.p3d";
	};

	class Zen_ContaminatedZoneBunkerExit1 : HouseNoDestruct
	{
		scope = 1;
		model = "DZ\structures\Industrial\Mines\Mine_Tunnel.p3d";
	};
	class Zen_ContaminatedZoneBunkerExit2 : HouseNoDestruct
	{
		scope = 1;
		model = "DZ\structures\Industrial\Mines\Mine_Tunnel.p3d";
	};

	class Zen_ContaminatedZoneBunkerSkeleton : HouseNoDestruct
	{
		scope = 2;
		displayName = "Skeleton";
		hiddenSelections[] =
		{
			"camo"
		};
		hiddenSelectionsTextures[] =
		{
			"AP_hnd_structure\data\skeletons\tex\base_gnaw.paa"
		};
		model = "AP_hnd_structure\data\skeletons\skeleton_sit1.p3d";
	};

	// Lukow airfield bunker 
	class Zen_LukowBunkerEntrance : HouseNoDestruct
	{
		scope = 1;
		model = "\DZ\structures_bliss\Underground\Stairs\Underground_Stairs_Block_Terminator.p3d";
	};
	class Zen_LukowBunkerExit : HouseNoDestruct
	{
		scope = 1;
		model = "\DZ\structures_bliss\Underground\Stairs\Underground_Stairs_Block_Terminator.p3d";
	};

	class Lockpick;
	class LukowPrisonKeys : Lockpick
	{
		scope = 2;
		displayName = "Prison Keys";
		descriptionShort = "These keys probably open the prison cells in the Lukow Airfield bunker.";
		model = "\dz\gear\tools\Handcuff_Keys.p3d";
		debug_ItemCategory = 2;
		animClass = "Knife";
		rotationFlags = 17;
		RestrainUnlockType = 0;
		weight = 4;
		itemSize[] = { 1,1 };
		fragility = 0.0099999998;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] =
					{

						{
							1,

							{
								"DZ\gear\tools\data\Handcuff_Key.rvmat"
							}
						},

						{
							0.69999999,

							{
								"DZ\gear\tools\data\Handcuff_Key.rvmat"
							}
						},

						{
							0.5,

							{
								"DZ\gear\tools\data\Handcuff_Key_damage.rvmat"
							}
						},

						{
							0.30000001,

							{
								"DZ\gear\tools\data\Handcuff_Key_damage.rvmat"
							}
						},

						{
							0,

							{
								"DZ\gear\tools\data\Handcuff_Key_destruct.rvmat"
							}
						}
					};
				};
			};
		};
		soundImpactType = "metal";
	}

	class ExpansionQuestItemBase;
	class ExpansionQuestItem_Medicine: ExpansionQuestItemBase
	{
		scope=2;
		displayName="Anti-Radiation Medicine";
		descriptionShort="A container filled with anti-radiation medicine. Hans needs me to deliver it to Dr Eva at Dolnik Hospital ASAP!";
		model="SyberiaScripts\data\medical\large_first_aid_kit.p3d";
		rotationFlags=17;
		weight=1000;
		isMeleeWeapon=1;
		itemSize[]={5,5};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpItem_Light
				{
					soundSet="pickUpCourierBag_Light_SoundSet";
					id=796;
				};
				class pickUpItem
				{
					soundSet="pickUpCourierBag_SoundSet";
					id=797;
				};
			};
		};
	};
	class ExpansionCircuitBoard_Quest1: ExpansionQuestItemBase
	{
		scope=2;
		displayName="Circuit Board - MK1";
		descriptionShort="Used to modify various electronic devices, like radio tower control panels. Hans wants me to use this to fix the Polana Radio Tower.";
		model="DayZExpansion\Core\Objects\CircuitBoard\CircuitBoard.p3d";
		itemSize[]={2,1};
		hiddenSelections[]=
		{
			"camo"
		};
		hiddenSelectionsTextures[]=
		{
			"DayZExpansion\Core\Objects\CircuitBoard\data\circuit_board_co.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"DayZExpansion\Core\Objects\CircuitBoard\data\circuit_board.rvmat"
		};
	};
	class ExpansionCircuitBoard_Quest2: ExpansionQuestItemBase
	{
		scope=2;
		displayName="Circuit Board - MK2";
		descriptionShort="Used to modify various electronic devices, like radio tower control panels. Irena wants me to use this to fix the Swarog Radio Tower.";
		model="DayZExpansion\Core\Objects\CircuitBoard\CircuitBoard.p3d";
		itemSize[]={2,1};
		hiddenSelections[]=
		{
			"camo"
		};
		hiddenSelectionsTextures[]=
		{
			"DayZExpansion\Core\Objects\CircuitBoard\data\circuit_board_mk2_co.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"DayZExpansion\Core\Objects\CircuitBoard\data\circuit_board.rvmat"
		};
	};
	class ExpansionQuestItem_Satchel: ExpansionQuestItemBase
	{
		scope=2;
		displayName="Radiated Satchel Charge";
		descriptionShort="I should return this to Sebastian...";
		model="\DayZExpansion\Objects\Weapons\Explosives\satchel.p3d";
		weight=1000;
		itemSize[]={3,4};
		rotationFlags=17;
		stackedUnit="l";
	};
	class ExpansionQuestItem_EncryptedRadio : ExpansionQuestItemBase
	{
		scope=2;
		displayName="Encrypted Radio";
		descriptionShort="A radio that can send signals over encrypted channels - perfect for Black Market operations! Scarecrow the Black Market trader wants me to deliver it to Sebastian at Sanctuary. I'd better not lose this!";
		model="\dz\gear\radio\WalkieTalkie.p3d";
		weight=250;
		absorbency=0.5;
		itemSize[]={1,3};
		rotationFlags=1;
		isMeleeWeapon=1;
		class MeleeModes
		{
			class Default
			{
				ammo="MeleeLightBlunt";
				range=1;
			};
			class Heavy
			{
				ammo="MeleeLightBlunt_Heavy";
				range=1;
			};
			class Sprint
			{
				ammo="MeleeLightBlunt_Heavy";
				range=2.8;
			};
		};
	};
	class ExpansionQuestItem_SanctuaryPackage: ExpansionQuestItemBase
	{
		scope=2;
		displayName="Mysterious Package";
		descriptionShort="A mysterious package. When I shake it, I hear rattling inside. Sebastian from Sanctuary wants me to deliver it to the Black Market trader at Swarog Military Base. Apparently he hangs out inside a radio tower station there. I'd better not lose this!";
		model="\DayZExpansion\Quests\Dta\Core\Package\package.p3d";
		isMeleeWeapon=1;
		weight=250;
		absorbency=1;
		itemSize[]={2,2};
		rotationFlags=16;
		inventorySlot[]={};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpItem
				{
					soundSet="pickUpPaper_SoundSet";
					id=797;
				};
			};
		};
	};
	class ExpansionQuestItem_PowerPlantBattery: ExpansionQuestItemBase
	{
		scope=2;
		displayName="Power Plant Battery";
		descriptionShort="A truck battery from Sanctuary. They want me to deliver it to the engineer at Karlin Power Plant. I'd better not lose this!";
		model="\dz\vehicles\parts\battery_truck.p3d";
		isMeleeWeapon=1;
		weight=18000;
		absorbency=1;
		itemSize[]={5,3};
		rotationFlags=16;
		inventorySlot[]={};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpItem
				{
					soundSet="carbattery_drop_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="carbattery_drop_SoundSet";
					id=898;
				};
			};
		};
	};
	class ExpansionQuestItem_ElectronicRepairKit: ExpansionQuestItemBase
	{
		scope=2;
		displayName="$STR_CfgVehicles_ElectronicRepairKit0";
		descriptionShort="An Electrical Repair Kit from Sanctuary. They want me to deliver it to the engineer at Karlin Power Plant. I'd better not lose this!";
		model="\dz\gear\tools\electronicCase.p3d";
		animClass="Knife";
		weight=1000;
		itemSize[]={2,3};
		inventorySlot[]={};
		soundImpactType="textile";
		class AnimEvents
		{
			class SoundWeapon
			{
				class Stitch
				{
					soundSet="StitchUpSelf_SoundSet";
					id=201;
				};
				class pickup
				{
					soundSet="sewingkit_pickup_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="sewingkit_drop_SoundSet";
					id=898;
				};
			};
		};
	};
	class ExpansionQuestItem_Briefcase: ExpansionQuestItemBase
	{
		scope=2;
		weight=3000;
		itemSize[]={5,3};
		rotationFlags=17;
		isMeleeWeapon=1;
		randomQuantity=2;
		model="\DayZExpansion\Core\Objects\Briefcase\briefcase.p3d";
		displayName="Briefcase";
		descriptionShort="A briefcase containing god knows what. Sebastian wants me to deliver it to Scarecrow at Swarog Military Base radio tower.";
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=750;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								""
							}
						},
						
						{
							0.69999999,
							
							{
								""
							}
						},
						
						{
							0.5,
							
							{
								""
							}
						},
						
						{
							0.30000001,
							
							{
								""
							}
						},
						
						{
							0,
							
							{
								""
							}
						}
					};
				};
			};
			class GlobalArmor
			{
				class FragGrenade
				{
					class Health
					{
						damage=8;
					};
					class Blood
					{
						damage=8;
					};
					class Shock
					{
						damage=8;
					};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpItem
				{
					soundSet="smallprotectorcase_pickup_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="smallprotectorcase_drop_SoundSet";
					id=898;
				};
			};
		};
	};
	class ExpansionQuestItem_HermitMap: ExpansionQuestItemBase 
	{
		scope=2;
		displayName="Hermit's Map";
		descriptionShort="This map has the location of a medical cache marked on it - I better give this to Sebastian.";
		model="\ZenMiscAssets\data\misc\zen_map.p3d";
		//rotationFlags=17;
		itemSize[]={2,2};
		weight=40;
		selectionPaper="paper";
		absorbency=1;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=50;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\gear\navigation\data\Map_chernarus.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\gear\navigation\data\Map_chernarus.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\gear\navigation\data\Map_chernarus_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\gear\navigation\data\Map_chernarus_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\gear\navigation\data\Map_chernarus_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class ExpansionQuestItem_NBCCase : ExpansionQuestItemBase
	{
		scope = 2;
		displayName = "Radioactive Material";
		descriptionShort = "I'd better not open this... maybe I should just take it back to Sanctuary.";
		model = "\dz\gear\containers\Protector_Case.p3d";
		rotationFlags = 17;
		weight = 5000;
		itemSize[] = { 3,4 };
		itemsCargoSize[] = { 0,0 };
		isMeleeWeapon = 1;
		hiddenSelections[] =
		{
			"zbytek"
		};
		hiddenSelectionsTextures[] =
		{
			"\ZenExpansionOverrides\data\textures\radioactive_nbc_case.paa",
			"\ZenExpansionOverrides\data\textures\radioactive_nbc_case.paa",
			"\ZenExpansionOverrides\data\textures\radioactive_nbc_case.paa"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 1000;
				};
			};
		};
	};
	class ExpansionQuestItem_LukowPetridish : Inventory_Base
	{
		scope = 2;
		displayName = "$STR_ZEN_VIRUS_CURE_PETRIDISH";
		descriptionShort = "This contains some strange looking specimen. I'd better bring it back to Sanctuary for them to study.";
		model = "\dz\structures\furniture\school_equipment\lab_petri_dish.p3d";
		weight = 0;
		interactionWeight = 1;
		itemSize[] = { 2,1 };
		hiddenSelections[] = { "component1" };
		hiddenSelectionsTextures[] = { "\DZ\structures\furniture\school_equipment\data\lab_set_ca.paa","\DZ\structures\furniture\school_equipment\data\lab_set_ca.paa","\DZ\structures\furniture\school_equipment\data\lab_set_ca.paa" };
		hiddenSelectionsMaterials[] = { "\DZ\data\data\penetration\glass.rvmat","\DZ\data\data\penetration\glass.rvmat","\DZ\data\data\penetration\glass.rvmat" };
	};

	// AI objects
	class Quest_Prison_MainCastle_barsdoors: HouseNoDestruct
	{
		scope=1;
		model="\DZ\structures\specific\prison\proxy\prison_maincastle_barsdoors.p3d";
	};
	class Quest_Skeleton_Sit2_Old: HouseNoDestruct
	{
		scope=1;
		displayName="Skeleton";
		hiddenSelections[]=
		{
			"camo"
		};
		hiddenSelectionsTextures[]=
		{
			"AP_hnd_structure\data\skeletons\tex\base_old.paa"
		};
		model="AP_hnd_structure\data\skeletons\skeleton_sit2.p3d";
	}
	class Quest_HermitNote: HouseNoDestruct
	{
		scope=1;
		displayName="Blood-stained Note";
		model="\dz\gear\consumables\Paper.p3d";
	}

	class ExpansionTraderStaticBase;
	class ExpansionTraderCashier: ExpansionTraderStaticBase
    {
        scope = 1;
        displayName="";
        model="\DZ\structures\furniture\generalstore\cashier.p3d";
		rotationFlags=12;
    };
	class ExpansionTraderSeaChest: ExpansionTraderStaticBase
	{
		scope=1;
		displayName="";
		model="\DZ\gear\camping\sea_chest.p3d";
		rotationFlags=2;
		hiddenSelections[]=
		{
			"camoGround"
		};
		hiddenSelectionsTextures[]=
		{
			"\ZenExpansionOverrides\data\textures\sea_chest_freshie_co.paa"
		};
	};

	class ExpansionP2PMarketTraderStatic;
	class ExpansionTraderP2PCashier: ExpansionP2PMarketTraderStatic
    {
        scope = 1;
        displayName="";
        model="\DZ\structures\furniture\generalstore\cashier.p3d";
    };

	class Zen_TraderObjectP2P : ExpansionP2PMarketTraderStatic
	{
		scope = 1;
		model = "ZenExpansionOverrides\data\zen_traderobject.p3d";
	};

	class NailBox;
	class NailBox_250: NailBox
	{
		scope = 2;
		displayName = "A box of 250 Nails";
		descriptionShort = "A box of 250 Nails";
		class Resources
		{
			class Nail
			{
				value=250;
				variable="quantity";
			};
		};
	};

	class NailBox_1K: Inventory_Base
	{
		scope = 2;
		displayName = "A box of 1,000 Nails";
		descriptionShort = "A box of 1,000 Nails";
		model="\dz\gear\containers\300RoundBox.p3d";
		weight=1000;
		itemSize[]={2,2};
		class Cargo
		{
			itemsCargoSize[] = { 2,2 };
			openable = 1;
			allowOwnedCargoManipulation = 1;
		};
	};
	class NailBox_2K: Inventory_Base
	{
		scope = 2;
		displayName = "A box of 2,500 Nails";
		descriptionShort = "A box of 2,500 Nails";
		model="\dz\gear\containers\300RoundBox.p3d";
		weight=2500;
		itemSize[]={5,2};
		class Cargo
		{
			itemsCargoSize[] = { 5,2 };
			openable = 1;
			allowOwnedCargoManipulation = 1;
		};
	};
	class NailBox_5K: Inventory_Base
	{
		scope = 2;
		displayName = "A box of 5,000 Nails";
		descriptionShort = "A box of 5,000 Nails";
		model="\dz\gear\containers\300RoundBox.p3d";
		weight=5000;
		itemSize[]={5,4};
		class Cargo
		{
			itemsCargoSize[] = { 5,4 };
			openable = 1;
			allowOwnedCargoManipulation = 1;
		};
	};

	// Mystery cargo box
	class Zen_ExpansionMilitaryCargo: Inventory_Base
	{
		scope=2;
		weight=99999;
		displayName = "Military Cargo";
		descriptionShort = "It seems to be a military container. It's locked with a military-grade steel padlock. I reckon I can use Bolt Cutters or a Propane Torch to open it and see what's inside...";
		itemSize[]={10,10};
		physLayer="item_large";
		class Cargo
		{
			itemsCargoSize[] = { 10,50 };
			openable = 1;
			allowOwnedCargoManipulation = 1;
		};
		model="\DayZExpansion\Objects\airdrop\container.p3d";
		hiddenSelections[]=
		{
			"body"
		};
		hiddenSelectionsTextures[]=
		{
			"DayZExpansion\Objects\Airdrop\data\Airdrop_co.paa"
		};
		class AnimationSources
		{
			class Parachute
			{
				source="user";
				animPeriod=0.99998999;
				initPhase=1;
			};
		};
	};
	class Zen_ExpansionMilitaryCargo_Contam: Zen_ExpansionMilitaryCargo
	{
		scope=2;
	}

	// This is necessary because the cargo box hasn't got proper P3D CE config so it spawns anywhere a tiny item can. Needs to be sheet-metal sized spawns.
	class Zen_DummyExpansionMilitaryCargo: Inventory_Base
	{
		scope=2;
		displayName="DUMMY ITEM";
		descriptionShort="If you're reading this tell Zenarchist he fucked up! You shouldn't be able to see this.";
		model="\dz\gear\consumables\Single_Metal_Sheet.p3d";
		rotationFlags=34;
		weight=1200;
		itemSize[]={10,10};
	};
	class Zen_DummyExpansionMilitaryCargo_Contam: Inventory_Base
	{
		scope=2;
		displayName="DUMMY ITEM";
		descriptionShort="If you're reading this tell Zenarchist he fucked up! You shouldn't be able to see this.";
		model="\dz\gear\consumables\Single_Metal_Sheet.p3d";
		rotationFlags=34;
		weight=1200;
		itemSize[]={10,10};
	};

	// Flag 
	class ExpansionPropFlagBase;
	class ExpansionPropFlagAustralivonia: ExpansionPropFlagBase
	{
		scope=1;
		displayName="$STR_EXPANSION_FLAG_POLE_AUS";
		hiddenSelectionsTextures[]=
		{
			"\ZenExpansionOverrides\data\textures\flag_australivonia_co.paa"
		};
	};
	class ExpansionPropFlagAboriginal : ExpansionPropFlagBase
	{
		scope = 1;
		displayName = "$STR_EXPANSION_FLAG_POLE_AUS";
		hiddenSelectionsTextures[] =
		{
			"\ZenExpansionOverrides\data\textures\flag_aboriginal_co.paa"
		};
	};
};

class CfgSoundShaders
{
	class Zen_Mission_SoundShader_Base;
	class Zen_AirdropAway_SoundShader : Zen_Mission_SoundShader_Base 
	{
		samples[] = 
		{ 
			{ "ZenExpansionOverrides\data\audio\airdrop_away", 1 } 
		};
	};
	class Zen_AirdropNW_SoundShader : Zen_Mission_SoundShader_Base 
	{
		samples[] = 
		{ 
			{ "ZenExpansionOverrides\data\audio\airdrop_nw", 1 } 
		};
	};
	class Zen_AirdropNE_SoundShader : Zen_Mission_SoundShader_Base 
	{
		samples[] = 
		{ 
			{ "ZenExpansionOverrides\data\audio\airdrop_ne", 1 } 
		};
	};
	class Zen_AirdropSW_SoundShader : Zen_Mission_SoundShader_Base 
	{
		samples[] = 
		{ 
			{ "ZenExpansionOverrides\data\audio\airdrop_sw", 1 } 
		};
	};
	class Zen_AirdropSE_SoundShader : Zen_Mission_SoundShader_Base 
	{
		samples[] = 
		{ 
			{ "ZenExpansionOverrides\data\audio\airdrop_se", 1 } 
		};
	};

	class Expansion_UI_SoundShader;
	class Expansion_Hint_SoundShader: Expansion_UI_SoundShader
	{
		samples[]=
		{
			
			{ "ZenServerGUI\data\sounds\notify", 1 }
		};
		volume=0.0;
	};
	class Zen_Hint_SoundShader: Expansion_UI_SoundShader
	{
		samples[]=
		{
			
			{ "ZenServerGUI\data\sounds\notify", 1 }
		};
		volume=0.15;
	};

	class ZenPowerNPC_SoundShaderBase
    {
        samples[] = {};
        frequency = 1;
        range = 100;
        volume = 1;
    };

	class Zen_Fireplace_SoundShader : ZenPowerNPC_SoundShaderBase
	{
		samples[] =
		{
			{ "ZenExpansionOverrides\data\audio\cracklingfireplace", 1 }
		};
	};

	class Zen_Trader_SoundShader : ZenPowerNPC_SoundShaderBase
	{
		samples[] =
		{
			{ "ZenExpansionOverrides\data\audio\nails1", 1 },
			{ "ZenExpansionOverrides\data\audio\nails2", 1 },
			{ "ZenExpansionOverrides\data\audio\nails3", 1 },
			{ "ZenExpansionOverrides\data\audio\nails4", 1 },
			{ "ZenExpansionOverrides\data\audio\nails5", 1 },
			{ "ZenExpansionOverrides\data\audio\nails6", 1 },
		};
	};

	// Power outage sound files
	class Zen_PowerOut_ExpansionTraderCyril_SoundShader : ZenPowerNPC_SoundShaderBase 
	{ 
		samples[] = 
		{ 
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderCyril_1", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderCyril_2", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderCyril_3", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderCyril_4", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderCyril_5", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderCyril_6", 1 }
		}; 
	};
	class Zen_PowerOut_ExpansionTraderBoris_SoundShader : ZenPowerNPC_SoundShaderBase 
	{ 
		samples[] = 
		{ 
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderBoris_1", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderBoris_2", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderBoris_3", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderBoris_4", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderBoris_5", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderBoris_6", 1 }
		}; 
	};
	class Zen_PowerOut_ExpansionTraderLinda_SoundShader : ZenPowerNPC_SoundShaderBase 
	{ 
		samples[] = 
		{ 
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderLinda_1", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderLinda_2", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderLinda_3", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderLinda_4", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderLinda_5", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderLinda_6", 1 }
		}; 
	};
	class Zen_PowerOut_ExpansionTraderDenis_SoundShader : ZenPowerNPC_SoundShaderBase 
	{ 
		samples[] = 
		{ 
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderDenis_1", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderDenis_2", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderDenis_3", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderDenis_4", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderDenis_5", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderDenis_6", 1 }
		}; 
	};
	class Zen_PowerOut_ExpansionTraderNaomi_SoundShader : ZenPowerNPC_SoundShaderBase 
	{ 
		samples[] = 
		{ 
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderNaomi_1", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderNaomi_2", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderNaomi_3", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderNaomi_4", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderNaomi_5", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderNaomi_6", 1 }
		}; 
	};
	class Zen_PowerOut_ExpansionTraderOliver_SoundShader : ZenPowerNPC_SoundShaderBase 
	{ 
		samples[] = 
		{ 
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderOliver_1", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderOliver_2", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderOliver_3", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderOliver_4", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderOliver_5", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderOliver_6", 1 }
		}; 
	};
	class Zen_PowerOut_ExpansionP2PTraderHelga_SoundShader : ZenPowerNPC_SoundShaderBase 
	{ 
		samples[] = 
		{ 
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionP2PTraderHelga_1", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionP2PTraderHelga_2", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionP2PTraderHelga_3", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionP2PTraderHelga_4", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionP2PTraderHelga_5", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionP2PTraderHelga_6", 1 }
		}; 
	};
	class Zen_PowerOut_ExpansionTraderElias_SoundShader : ZenPowerNPC_SoundShaderBase 
	{ 
		samples[] = 
		{ 
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderElias_1", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderElias_2", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderElias_3", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderElias_4", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderElias_5", 1 },
			{ "ZenExpansionOverrides\data\audio\poweroutage\ExpansionTraderElias_6", 1 }
		}; 
	};

	// Quest actions
	class Zen_QuestHermit1_SoundShader : ZenPowerNPC_SoundShaderBase 
	{ 
		samples[] = 
		{ 
			{ "ZenExpansionOverrides\data\audio\quests\hermit1", 1 }
		}; 
	};
	class Zen_QuestHermit2_SoundShader : ZenPowerNPC_SoundShaderBase 
	{ 
		samples[] = 
		{ 
			{ "ZenExpansionOverrides\data\audio\quests\cave\hermit2", 1 }
		}; 
	};

	// Creepy cave sounds
	class Zen_QuestCaveDoor_SoundShader : ZenPowerNPC_SoundShaderBase
	{
		samples[] =
		{
			{ "DZ\sounds\environment\buildings\doors\metalcontainer\doormetalcontainerclose_1", 1 },
			{ "DZ\sounds\environment\buildings\doors\metalcontainer\doormetalcontainerclose_2", 1 },
			{ "DZ\sounds\environment\buildings\doors\metalcontainer\doormetalcontainerclose_3", 1 }
		};
	};
	class Zen_QuestCaveLaughs_SoundShader : ZenPowerNPC_SoundShaderBase
	{
		samples[] =
		{
			{ "ZenExpansionOverrides\data\audio\quests\cave\laugh1", 1 },
			{ "ZenExpansionOverrides\data\audio\quests\cave\laugh2", 1 },
			{ "ZenExpansionOverrides\data\audio\quests\cave\laugh3", 1 },
			{ "ZenExpansionOverrides\data\audio\quests\cave\laugh4", 1 },
			{ "ZenExpansionOverrides\data\audio\quests\cave\laugh5", 1 },
			{ "ZenExpansionOverrides\data\audio\quests\cave\laugh6", 1 },
			{ "ZenExpansionOverrides\data\audio\quests\cave\laugh7", 1 },
			{ "ZenExpansionOverrides\data\audio\quests\cave\laugh8", 1 },
			{ "ZenExpansionOverrides\data\audio\quests\cave\laugh9", 1 },
			{ "ZenExpansionOverrides\data\audio\quests\cave\laugh10", 1 },
			{ "ZenExpansionOverrides\data\audio\quests\cave\laugh11", 1 },
			{ "ZenExpansionOverrides\data\audio\quests\cave\laugh12", 1 },
			{ "ZenExpansionOverrides\data\audio\quests\cave\laugh13", 1 },
			{ "ZenExpansionOverrides\data\audio\quests\cave\cry1", 1 },
			{ "ZenExpansionOverrides\data\audio\quests\cave\cry2", 1 },
			{ "ZenExpansionOverrides\data\audio\quests\cave\cry3", 1 },
			{ "ZenExpansionOverrides\data\audio\quests\cave\cry4", 1 },
			{ "ZenExpansionOverrides\data\audio\quests\cave\cry5", 1 },
			{ "ZenExpansionOverrides\data\audio\quests\cave\cry6", 1 },
			{ "ZenExpansionOverrides\data\audio\quests\cave\cry7", 1 },
			{ "ZenExpansionOverrides\data\audio\quests\cave\cry8", 1 },
			{ "ZenExpansionOverrides\data\audio\quests\cave\cry9", 1 },
			{ "ZenExpansionOverrides\data\audio\quests\cave\cry10", 1 },
			{ "ZenExpansionOverrides\data\audio\quests\cave\cry11", 1 }
		};
		volume = 0.5;
	};
}

class CfgSoundSets
{
	class Zen_BaseMissionRadio_SoundSet; // From ZenMissionAudio
	class Zen_AirdropAway_SoundSet : Zen_BaseMissionRadio_SoundSet
	{ 
		missionKeywords = "Airdrop away at grid coordinates";
		soundShaders[] = { "Zen_AirdropAway_SoundShader" };
	};
	class Zen_AirdropNW_SoundSet : Zen_BaseMissionRadio_SoundSet
	{ 
		missionKeywords = "We've got a cargo plane in-bound to the NORTH-WEST";
		soundShaders[] = { "Zen_AirdropNW_SoundShader" };
	};
	class Zen_AirdropNE_SoundSet : Zen_BaseMissionRadio_SoundSet
	{ 
		missionKeywords = "We've got a cargo plane in-bound to the NORTH-EAST";
		soundShaders[] = { "Zen_AirdropNE_SoundShader" };
	};
	class Zen_AirdropSW_SoundSet : Zen_BaseMissionRadio_SoundSet
	{ 
		missionKeywords = "We've got a cargo plane in-bound to the SOUTH-WEST";
		soundShaders[] = { "Zen_AirdropSW_SoundShader" };
	};
	class Zen_AirdropSE_SoundSet : Zen_BaseMissionRadio_SoundSet
	{ 
		missionKeywords = "We've got a cargo plane in-bound to the SOUTH-EAST";
		soundShaders[] = { "Zen_AirdropSE_SoundShader" };
	};

	class Zen_Fireplace_SoundSet { soundShaders[] = { "Zen_Fireplace_SoundShader" }; };
	class Zen_Trader_SoundSet { soundShaders[] = { "Zen_Trader_SoundShader" }; };

	// Power outage voices
	class Zen_PowerOut_ExpansionTraderCyril_SoundSet	{ soundShaders[] = { "Zen_PowerOut_ExpansionTraderCyril_SoundShader" }; };
	class Zen_PowerOut_ExpansionTraderBoris_SoundSet	{ soundShaders[] = { "Zen_PowerOut_ExpansionTraderBoris_SoundShader" }; };
	class Zen_PowerOut_ExpansionTraderLinda_SoundSet	{ soundShaders[] = { "Zen_PowerOut_ExpansionTraderLinda_SoundShader" }; };
	class Zen_PowerOut_ExpansionTraderDenis_SoundSet	{ soundShaders[] = { "Zen_PowerOut_ExpansionTraderDenis_SoundShader" }; };
	class Zen_PowerOut_ExpansionTraderNaomi_SoundSet	{ soundShaders[] = { "Zen_PowerOut_ExpansionTraderNaomi_SoundShader" }; };
	class Zen_PowerOut_ExpansionTraderOliver_SoundSet	{ soundShaders[] = { "Zen_PowerOut_ExpansionTraderOliver_SoundShader" }; };
	class Zen_PowerOut_ExpansionTraderElias_SoundSet	{ soundShaders[] = { "Zen_PowerOut_ExpansionTraderElias_SoundShader" }; };
	class Zen_PowerOut_ExpansionP2PTraderHelga_SoundSet	{ soundShaders[] = { "Zen_PowerOut_ExpansionP2PTraderHelga_SoundShader" }; };

	// Quest actions 
	class Zen_QuestHermit1_SoundSet	{ soundShaders[] = { "Zen_QuestHermit1_SoundShader" }; };
	class Zen_QuestHermit2_SoundSet	{ soundShaders[] = { "Zen_QuestHermit2_SoundShader" }; };
	class Zen_QuestCaveDoor_SoundSet { soundShaders[] = { "Zen_QuestCaveDoor_SoundShader" }; };
	class Zen_QuestCaveLaughs_SoundSet { soundShaders[] = { "Zen_QuestCaveLaughs_SoundShader" }; };
}

// For balancing expansion/vanilla C4 satchel raiding
class CfgAmmo
{
	class DefaultAmmo;
	class Plastic_Explosive_Ammo: DefaultAmmo
	{
		class DamageApplied
		{
			type="FragGrenade";
			class Health
			{
				damage=410; // was 350, makes this 10k base damage
			};
			class Blood
			{
				damage=0;
			};
			class Shock
			{
				damage=100;
			};
		};
	};
	class ExpansionRocket_Ammo: DefaultAmmo
	{
		class DamageApplied
		{
			type="FragGrenade";
			bleedThreshold=0.40000001;
			class Health
			{
				damage=40;
			};
			class Blood
			{
				damage=0;
			};
			class Shock
			{
				damage=0;
			};
		};
	};
}

class CfgMagazines
{
	class Magazine_Base;
	class Ammo_Flare;
	class Ammo_FlareRed;
	class Ammo_FlareGreen;
	class Ammo_FlareBlue;
	class Expansion_Ammo_FlareSupplyBase: Ammo_Flare
	{
		count=1;
		displayName="$STR_EXPANSION_SUPPLY_GRENADE";
		descriptionShort="A flare used for calling in an Aidrop supply crate, all I need is a flare gun...";
		ammo="Bullet_Expansion_FlareSupply";
	};
	class Expansion_Ammo_FlareSupplyRed: Ammo_FlareRed
	{
		count=1;
		displayName="$STR_EXPANSION_SUPPLY_GRENADE";
		descriptionShort="A flare used for calling in an Aidrop supply crate, all I need is a flare gun...";
		ammo="Bullet_Expansion_FlareSupplyRed";
	};
	class Expansion_Ammo_FlareSupplyGreen: Ammo_FlareGreen
	{
		count=1;
		displayName="$STR_EXPANSION_SUPPLY_GRENADE";
		descriptionShort="A flare used for calling in an Aidrop supply crate, all I need is a flare gun...";
		ammo="Bullet_Expansion_FlareSupplyGreen";
	};
	class Expansion_Ammo_FlareSupplyBlue: Ammo_FlareBlue
	{
		count=1;
		displayName="$STR_EXPANSION_SUPPLY_GRENADE";
		descriptionShort="A flare used for calling in an Aidrop supply crate, all I need is a flare gun...";
		ammo="Bullet_Expansion_FlareSupplyBlue";
	};

	class Mag_Expansion_AWM_5rnd : Magazine_Base
	{
		itemSize[] = { 2,2 };
	};
}

class CfgExpansionCharacterScenes_Zen
{
	class Enoch
	{
		class enoch_sanctuary_guitar_night
		{
			CameraPosition[]={5631.045410, 181.286163, 10585.022461};
			CameraOrientation[]={52.223400, 0.000000, -0.000000};
			PlayerPosition[]={5634.067383, 180.270401, 10587.653320};
			PlayerOrientation[]={-138.364563,0.0,0.0};
			fov=1;
			date[]={2011,8,10,23,30};
			overcast=0;
			rain=0;
			fog=0;
			windspeed=0;
			MappingFiles[]=
			{
				"ZenExpansionOverrides\data\loginscenes\sanctuary_fire"
			};
			CustomPose=1051;
			HandItem="Expansion_Guitar_old";
			CanRotate=0;
			CanUseInCharacterCreation=1;
		};
	};
};

class CfgNonAIVehicles
{
	// Static object proxy example
	class StaticObject;
	class Zen_StaticObject : StaticObject
	{
		scope = 0;
	};

	// Vanilla classname for static object (hover mouse over obj in DayZ Editor to see its classname)
	// Defining it here as a "scripted object" allows it to be interacted with using ActionBase code.
	// Most of these static objects have no script attached to them. This method simply "attaches" a
	// script to the static object which spawns an interactable object on top of it.
	class Static_trailmap_enoch : Zen_StaticObject
	{
		scope = 1;
		model = "DZ\structures_bliss\signs\tourist\trailmap_enoch.p3d";
	};
};