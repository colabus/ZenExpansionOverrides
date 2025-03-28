modded class CharacterCreationMenu
{
	void CharacterCreationMenu()
	{
		if (m_Scene.Expansion_IsCustomScene())
		{
			if (m_Scene.Expansion_CanUseCustomSceneInCharacterCreation())
				m_Scene.Expansion_SetupCharacter(true);
			else 
			if (!m_Scene.Expansion_LoadRandomScene("cfgExpansionCharacterScenes_Zen " + g_Game.GetWorldName(), true))
				m_Scene.Expansion_LoadRandomSceneVanilla();
		}
	}
}

modded class DayZIntroScenePC
{
	static EffectSound m_GuitarSong;

	EffectSound m_FireplaceSound;
	Dayz_Doggo doggo;
	ref array<Object> m_LoadingScreenObjects;
	Object m_Tarp;
	ItemBase m_BeerCan;

	int year, month, day;

	static const ref array<string> TRADER_SONGS =
	{
		"Zen_Cassette_Trader1",
		"Zen_Cassette_Trader2",
		"Zen_Cassette_Trader3",
		"Zen_Cassette_Trader4",
		"Zen_Cassette_Trader5",
		"Zen_Cassette_Trader6",
		"Zen_Cassette_Trader7",
		"Zen_Cassette_Trader8",
		"Zen_Cassette_Trader9",
		"Zen_Cassette_Trader10",
		"Zen_Cassette_Trader11",
		"Zen_Cassette_Trader12",
		"Zen_Cassette_Trader13",
		"Zen_Cassette_Trader14",
		"Zen_Cassette_Trader15",
		"Zen_Cassette_Trader16",
		"Zen_Cassette_Trader17",
		"Zen_Cassette_Trader18",
		"Zen_Cassette_Trader19",
		"Zen_Cassette_Trader20",
		"Zen_Cassette_Trader21",
		"Zen_Cassette_Trader22",
		"Zen_Cassette_Trader23",
		"Zen_Cassette_Trader24",
		"Zen_Cassette_Trader25",
		"Zen_Cassette_Trader26",
		"Zen_Cassette_Trader27",
		"Zen_Cassette_Trader28"
	};

	static const ref array<string> SLEEPING_BAGS = 
	{ 
		"SleepingBagDeployedBlack",
		"SleepingBagDeployedBlue",
		"SleepingBagDeployedGrey",
		"SleepingBagDeployedRed",
		"SleepingBagDeployedGreen"
	};

	static const ref array<string> BEER_CANS = 
	{ 
		"BeerCan_Corona",
		"BeerCan_VB",
		"BeerCan_XXXX",
		"Kvass"
	};

	static const ref array<string> BEER_BOTTLES = 
	{ 
		"Fraochan",
		"BlackGroat",
		"AuldBroon",
		"Laboureuse",
		"Boilermaker",
		"PilgrimsPale",
		"Handfasted",
		"CreuseWit",
		"Forgeronne",
		"Caoranach",
		"Vodka",
		"ZenJameson"
	};

	void ~DayZIntroScenePC()
	{
		if (!GetGame())
			return;

		GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).Remove(PlaySong);

		if (m_FireplaceSound)
			m_FireplaceSound.Stop();

		if (m_GuitarSong)
			m_GuitarSong.Stop();

		DeleteLoadingScreenObjects();

		if (doggo)
			GetGame().ObjectDelete(doggo);
	}

	void DeleteLoadingScreenObjects()
	{
		if (!m_LoadingScreenObjects)
			return;

		// Clear objects
		for (int i = m_LoadingScreenObjects.Count(); i >= 0; i--)
		{
			GetGame().ObjectDelete(m_LoadingScreenObjects.Get(i));
			m_LoadingScreenObjects.Remove(i);
		}
	}

	override bool Expansion_LoadRandomScene(string root_path, bool characterCreation = false)
	{
		super.Expansion_LoadRandomScene(root_path, characterCreation);

		// Override to my own CFG class so I have full control over the scenes that load
		root_path = "cfgExpansionCharacterScenes_Zen " + g_Game.GetWorldName();

		int count = g_Game.ConfigGetChildrenCount(root_path);
		if (count == 0)
			return false;

		string childName;

		if (characterCreation)
		{
			TStringArray ccScenes = {};

			for (int i = 0; i < count; i++)
			{
				GetGame().ConfigGetChildName(root_path, i, childName);

				if (GetGame().ConfigGetInt(root_path + " " + childName + " CanUseInCharacterCreation"))
					ccScenes.Insert(childName);
			}

			if (ccScenes.Count() == 0)
				return false;

			childName = ccScenes.GetRandomElement();
		}
		else
		{
			int index = Math.RandomInt(0, count);
			g_Game.ConfigGetChildName(root_path, index, childName);
		}

		Expansion_LoadScene(root_path, childName, characterCreation);

		return true;
	}

	override void Expansion_HandleCustomScene(string childName)
	{
		super.Expansion_HandleCustomScene(childName);

		DeleteLoadingScreenObjects();

		PlayerBase sceneCharacter = m_Character.GetCharacterObj();

		//if (childName == "enoch_swarog") // cbf making a .map file
		//{
		//	ZenMenuSpawnObject("Land_Tower_TC4_Base", "5177.049805 538.900024 2248.000000", "179.999939 0.000000 0.000000");
		//	ZenMenuSpawnObject("Land_Tower_TC4_Mid", "5176.910156 582.377991 2248.110107", "179.999939 0.000000 0.000000");
		//	ZenMenuSpawnObject("Land_Tower_TC4_Top", "5177.049805 622.890015 2248.000000", "179.999939 0.000000 0.000000");
		//}
		//else
		if (childName == "enoch_sanctuary_guitar_night")
		{
			//SetRandomWeather();
			m_FireplaceSound = SEffectManager.PlaySoundOnObject("Zen_Fireplace_SoundSet", m_Character.GetCharacterObj(), 0.0, 0.0, true);
			if (m_FireplaceSound)
			{
				m_FireplaceSound.SetSoundAutodestroy(true);
				m_FireplaceSound.SetSoundVolume(0.15);
			}

			if (Math.RandomFloat01() <= 0.25) // 25% chance of In The House, In A Heartbeat
			{
				GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( PlaySong, 3000, false, "Zen_Cassette_Trader10");
			} else
			{
				GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( PlaySong, 3000, false, TRADER_SONGS.GetRandomElement());
			}
		}
	}

	private void SetRandomWeather()
	{
		bool raining = true; //Math.RandomFloat01() <= 0.2;

		if (raining)
		{
			m_Weather = g_Game.GetWeather();
			m_Weather.GetOvercast().SetLimits(1.0, 1.0);
			m_Weather.GetOvercast().Set(1.0, 1.0, 0);
			m_Weather.GetRain().SetLimits(0.1, 0.1);
			m_Weather.GetRain().Set(0.1, 0.1, 0);
		}

		bool isSunset = Math.RandomFloat01() <= 0.33;

		if (isSunset)
		{
			World world = g_Game.GetWorld();
			if (world)
			{
				world.SetDate(1990, 6, 7, Math.RandomIntInclusive(19, 23), Math.RandomIntInclusive(0, 59));
			}
		}

		/*float overcast, rain, windspeed, fog;
		overcast = g_Game.ConfigGetFloat(scene_path + " overcast");
		rain = g_Game.ConfigGetFloat(scene_path + " rain");
		fog = g_Game.ConfigGetFloat(scene_path + " fog");
		windspeed = g_Game.ConfigGetFloat(scene_path + " windspeed");
		m_Weather = g_Game.GetWeather();
		m_Weather.GetOvercast().SetLimits(overcast, overcast);
		m_Weather.GetRain().SetLimits(rain, rain);
		m_Weather.GetFog().SetLimits(fog, fog );
		m_Weather.GetOvercast().Set(overcast, overcast, 0);
		m_Weather.GetRain().Set(rain, rain, 0);
		m_Weather.GetFog().Set(fog, fog, 0);

		if ( windspeed != -1 )
		{
			m_Weather.SetWindSpeed(windspeed);
			m_Weather.SetWindMaximumSpeed(windspeed);
			m_Weather.SetWindFunctionParams(windspeed,windspeed,0);
		}*/
	}

	bool IsChristmas()
	{
		return month == 12 && day >= 12;
	}

	bool IsAustraliaDay()
	{
		return month == 1 && day >= 25 && day <= 27;
	}

	ZombieBase santaZombie;
	AnimalBase reindeer;

	void SpawnHolidayStuff()
	{
		// Christmas
		if (IsChristmas())
		{
			Object tree = ZenMenuSpawnObject("Zen_ChristmasTree_Green", "5635.877930 181.020950 10587.395508", "65.000000 0.000000 0.000000");
			if (tree)
				tree.SetScale(0.28);
			ZenMenuSpawnObject("ClutterCutter6x6", "5635.266602 183.216141 10587.012695", "0.000000 -0.000000 -0.000000");
			ZenMenuSpawnObject("bldr_prop_GiftBox_Large_2", "5636.300781 180.229691 10588.332031", "35.999989 -0.000000 -0.000000");
			ZenMenuSpawnObject("bldr_prop_GiftBox_Small_4", "5635.034668 180.237152 10587.333008", "-27.000000 0.000000 0.000000");
			ZenMenuSpawnObject("bldr_prop_GiftBox_Large_4", "5636.666504 180.186279 10586.630859", "-53.999985 0.000000 0.000000");
			ZenMenuSpawnObject("bldr_prop_GiftBox_Small_3", "5637.009277 180.188904 10587.086914", "0.000000 -0.000000 -0.000000");
			ZenMenuSpawnObject("bldr_prop_GiftBox_Large_3", "5635.139160 180.232498 10588.027344", "-62.999973 0.000000 0.000000");

			int santaLocation = Math.RandomIntInclusive(1, 10);

			if (santaZombie)
				santaZombie.DeleteSafe();

			if (reindeer)
				reindeer.DeleteSafe();
			
			if (santaLocation == 1)
				santaZombie = ZombieBase.Cast(ZenMenuSpawnObject("ZmbM_Santa", "5636.150391 180.246918 10589.803711", "-152.999908 0.000000 -0.000000"));
			else if (santaLocation == 2)
				santaZombie = ZombieBase.Cast(ZenMenuSpawnObject("ZmbM_Santa", "5635.870117 180.179764 10585.506836", "-109.503967 0.000000 0.000000"));
			else if (santaLocation == 3)
				santaZombie = ZombieBase.Cast(ZenMenuSpawnObject("ZmbM_Santa", "5633.209961 180.345993 10593.099609", "-179.503983 0.000000 0.000000"));

			if (Math.RandomFloat01() < 0.2)
				reindeer = AnimalBase.Cast(ZenMenuSpawnObject("Animal_RangiferTarandus_Xmas", "5634.399902 180.360992 10591.299805", "180.0 0.000000 0.000000"));

			if (santaZombie)
				santaZombie.GetInventory().CreateAttachment("SantasHat");

			return;
		}

		// Halloween

		// Easter

		// Australia Day
		if (IsAustraliaDay())
		{
			//if (Math.RandomFloat01() < 0.5)
				ZenMenuSpawnObject("ExpansionPropFlagAustralivonia", "5634.877930 175.5 10587.395508", "40.000000 0.000000 0.000000");
			//else
			//	ZenMenuSpawnObject("ExpansionPropFlagAboriginal", "5634.877930 175.5 10587.395508", "40.000000 0.000000 0.000000");
			return;
		}
	}

	override void Expansion_SetupCharacter(bool characterCreation = false)
	{
		if (!m_Character || !m_Character.GetCharacterObj())
			super.Expansion_SetupCharacter(characterCreation);

		auto trace = EXTrace.StartStack(EXTrace.MISC, this, "characterCreation " + characterCreation);

		m_Character.Expansion_SetPosition(g_Game.ConfigGetVector(m_Expansion_CustomScene + " PlayerPosition"));
		m_Character.Expansion_SetOrientation(g_Game.ConfigGetVector(m_Expansion_CustomScene + " PlayerOrientation"));

		if (characterCreation)
		{
			//! Fugly: I couldn't find a way to reset pose when entering CC menu, so the whole character is re-created - lava76
			m_Character.CreateNewCharacterById(m_Character.GetCharacterID());
			return;
		}
		else
		{
			string item = "Expansion_Guitar_old";
			//if (Math.RandomFloat01() <= 0.1)
			//	item = "Expansion_Guitar";

			if (m_Character.GetCharacterObj().GetItemInHands())
			{
				HandleHandItem(m_Character.GetCharacterObj(), m_Character.GetCharacterObj().GetItemInHands(), item);
			}
			else
			{
				m_Character.GetCharacterObj().GetHumanInventory().CreateInHands(item);
			}

			int customPose = g_Game.ConfigGetInt(m_Expansion_CustomScene + " CustomPose");
			if (customPose != -1)
				m_Character.GetCharacterObj().StartCommand_Action(customPose, ActionBaseCB, DayZPlayerConstants.STANCEMASK_ALL);
		}

		GetYearMonthDay(year, month, day);
		//GetHourMinuteSecond(hour, minute, second);

		SpawnHolidayStuff();

		// Spawn winter stuff
		if (IsWinterOrSpring())
		{
			ZenMenuSpawnObject("bl_anatolian_carpet_2_Static", "5633.949219 180.262619 10587.861328", "-0.000038 0.733228 1.099898");
		}

		/*
		"Head",
		"Shoulder",
		"Melee",
		"Headgear",
		"Mask",
		"Eyewear",
		"Hands",
		"LeftHand",
		"Gloves",
		"Armband",
		"Vest",
		"Body",
		"Back",
		"Hips",
		"Legs",
		"Feet",
		"Splint_RigZenExpansionAudioAI_SoundSetsht"
		*/


			
		ItemBase newItem;

		ItemBase itemCheck = ItemBase.Cast(m_Character.GetCharacterObj().FindAttachmentBySlotName("Headgear"));
		if (itemCheck && itemCheck.IsInherited(HelmetBase))
		{
			newItem = ItemBase.Cast(ZenMenuSpawnObject(itemCheck.GetType(), "5633.675293 181.219437 10588.418945", "53.999985 -0.000000 -0.000000"));
			if (newItem)
				newItem.SetHealth(itemCheck.GetHealth());

			GetGame().ObjectDelete(itemCheck);
		}

		itemCheck = ItemBase.Cast(m_Character.GetCharacterObj().FindAttachmentBySlotName("Feet"));
		if (itemCheck)
		{
			newItem = ItemBase.Cast(ZenMenuSpawnObject(itemCheck.GetType(), "5633.272461 180.286087 10588.293945", "80.999954 -0.000000 -0.000000"));
			if (newItem)
				newItem.SetHealth(itemCheck.GetHealth());

			GetGame().ObjectDelete(itemCheck);
		}

		itemCheck = ItemBase.Cast(m_Character.GetCharacterObj().FindAttachmentBySlotName("Eyewear"));
		if (itemCheck && !itemCheck.GetType().Contains("EyeMask")) // allow eyemasks
		{
			GetGame().ObjectDelete(itemCheck);
		}

		itemCheck = ItemBase.Cast(m_Character.GetCharacterObj().FindAttachmentBySlotName("Gloves"));
		if (itemCheck)
		{
			GetGame().ObjectDelete(itemCheck);
		}

		itemCheck = ItemBase.Cast(m_Character.GetCharacterObj().FindAttachmentBySlotName("Vest"));
		if (itemCheck)
		{
			GetGame().ObjectDelete(itemCheck);
		}

		itemCheck = ItemBase.Cast(m_Character.GetCharacterObj().FindAttachmentBySlotName("Hips"));
		if (itemCheck)
		{
			GetGame().ObjectDelete(itemCheck);
		}

		itemCheck = ItemBase.Cast(m_Character.GetCharacterObj().FindAttachmentBySlotName("Back"));
		if (itemCheck)
		{
			newItem = ItemBase.Cast(ZenMenuSpawnObject(itemCheck.GetType(), "5633.152832 180.248535 10588.756836", "86.399994 -19.999983 0.000000"));
			if (newItem)
			{
				ZenFunctions.MoveInventory(itemCheck, newItem);
				newItem.SetHealth(itemCheck.GetHealth());
			}

			GetGame().ObjectDelete(itemCheck);
		}

		itemCheck = ItemBase.Cast(m_Character.GetCharacterObj().FindAttachmentBySlotName("Mask"));
		if (itemCheck && !itemCheck.GetType().Contains("_Scarf_")) // allow shemagh
		{
			GetGame().ObjectDelete(itemCheck);
		}

		itemCheck = ItemBase.Cast(m_Character.GetCharacterObj().FindAttachmentBySlotName("Shoulder"));
		if (itemCheck)
		{
			HandleShoulderItem(itemCheck);
		}

		itemCheck = ItemBase.Cast(m_Character.GetCharacterObj().FindAttachmentBySlotName("Melee"));
		if (itemCheck)
		{
			HandleMeleeItem(itemCheck);
		}

		itemCheck = ItemBase.Cast(m_Character.GetCharacterObj().FindAttachmentBySlotName("Armband"));
		if (itemCheck && itemCheck.GetType() == "ItemPDA")
		{
			GetGame().ObjectDelete(itemCheck);
		}

		if (IsChristmas() && !santaZombie)
		{
			m_Character.GetCharacterObj().GetInventory().CreateAttachment("SantasHat");
		}

		ZenMenuSpawnObject(SLEEPING_BAGS.GetRandomElement(), "5632.294434 180.297668 10588.098633", "-95.197784 1.028189 -0.726999");

		if (m_BeerCan)
			GetGame().ObjectDelete(m_BeerCan);

		if (IsAustraliaDay())
		{
			if (Math.RandomFloat01() < 0.5)
				m_BeerCan = ItemBase.Cast(ZenMenuSpawnObject("BeerCan_XXXX", "5633.479980 180.328262 10587.90039", "25.999998 0.000000 0.000000"));
			else
				m_BeerCan = ItemBase.Cast(ZenMenuSpawnObject("BeerCan_VB", "5633.479980 180.328262 10587.90039", "25.999998 0.000000 0.000000"));
		}
		else
		{
			int randType = Math.RandomIntInclusive(1, 2);
			if (randType == 1)
			{
				m_BeerCan = ItemBase.Cast(ZenMenuSpawnObject(BEER_CANS.GetRandomElement(), "5633.479980 180.328262 10587.90039", "25.999998 0.000000 0.000000"));
			}
			else
			{
				m_BeerCan = ItemBase.Cast(ZenMenuSpawnObject(BEER_BOTTLES.GetRandomElement(), "5633.478516 180.407639 10587.897461", "34.999996 0.000000 0.000000"));
			}
		}

		// HANDLE DOG:
		if (PlayerBase.DOG_TYPE != "")
		{
			vector dogPos = "5635.354004 180.186249 10585.725586";

			// This crashes game?
			/*array<Object> nearest_objects = new array<Object>;
			GetGame().GetObjectsAtPosition3D(dogPos, 5, nearest_objects, NULL);

			foreach(Object nearobj : nearest_objects)
			{
				if (nearobj.IsInherited(Dayz_Doggo))
				{
					Dayz_Doggo nearbyDoggo = Dayz_Doggo.Cast(nearobj);
					if (nearbyDoggo)
						nearbyDoggo.DeleteSafe();
				}
			}*/

			string dogType = PlayerBase.DOG_TYPE;
			dogType.Replace("DogPreview", "");
			dogType = "Doggo_Follow" + dogType;

			if (doggo)
				GetGame().ObjectDelete(doggo);

			doggo = Dayz_Doggo.Cast(GetGame().CreateObjectEx(dogType, dogPos, false, true));

			if (doggo)
			{
				m_LoadingScreenObjects.Insert(doggo);

				doggo.SetOrientation("-60.0 0.000000 0.000000");

				ZenMenuSpawnObject("dog_bone_toy", "5632.308594 180.214697 10585.949219", "0.0 0.0 0.0");

				randType = Math.RandomIntInclusive(1, 3);
				doggo.SetAmbient(randType);

				if (randType == 3) // eat
				{
					ZenMenuSpawnObject("dog_bowl", "5634.429688 180.229248 10586.243164", "0.0 0.0 0.0");
					ZenMenuSpawnObject("DogFoodCan_Opened", "5634.532715 180.270264 10587.273438", "-16.0 0.0 0.0");
				}
			}
		}
		else
		{
			if (doggo)
				doggo.DeleteSafe();
		}

		// SPAWN HUNTING RIFLE ON RACK
		if (Math.RandomIntInclusive(1, 3) == 1)
		{
			itemCheck = ItemBase.Cast(ZenMenuSpawnObject("Winchester70", "5632.950195 180.709000 10589.500000", "-179.999985 0.000000 71.700005"));
			if (itemCheck)
			{
				itemCheck.GetInventory().CreateAttachment("HuntingOptic");
			}
		}
	}

	private void HandleHandItem(notnull PlayerBase pb, notnull ItemBase itemCheck, string handItem)
	{
		if (itemCheck.IsInherited(Weapon_Base))
		{
			ItemBase moveItem = ItemBase.Cast(ZenMenuSpawnObject(itemCheck.GetType(), "5631.500000 180.350006 10587.400391", "99.999992 -85.015320 0.000005"));
			if (moveItem)
			{
				ZenFunctions.MoveInventory(itemCheck, moveItem);
				moveItem.SetHealth(itemCheck.GetHealth());
				SpawnTarp();
			}
		}
		else
		if (itemCheck.IsInherited(WoodAxe))
		{
			ZenMenuSpawnObject(itemCheck.GetType(), "5631.649902 180.302643 10586.500000", "-45.000000 0.000000 90.000000");
		}
		else
		if (itemCheck.IsInherited(Pickaxe))
		{
			ZenMenuSpawnObject(itemCheck.GetType(), "5633.505859 180.536118 10589.197266", "-95.000000 0.000000 -15.499998");
		}

		GetGame().ObjectDelete(itemCheck);
		pb.GetHumanInventory().CreateInHands(handItem);
	}

	private void HandleShoulderItem(notnull ItemBase itemCheck)
	{
		if (itemCheck.IsInherited(Weapon_Base))
		{
			ItemBase moveItem = ItemBase.Cast(ZenMenuSpawnObject(itemCheck.GetType(), "5631.479980 180.345001 10587.900391", "-84.999985 -84.999626 0.000000"));
			if (moveItem)
			{
				ZenFunctions.MoveInventory(itemCheck, moveItem);
				moveItem.SetHealth(itemCheck.GetHealth());
				SpawnTarp();
			}
		}
		else
		if (itemCheck.IsInherited(WoodAxe))
		{
			ZenMenuSpawnObject(itemCheck.GetType(), "5631.649902 180.302643 10586.500000", "-45.000000 0.000000 90.000000");
		}
		else
		if (itemCheck.IsInherited(Pickaxe))
		{
			ZenMenuSpawnObject(itemCheck.GetType(), "5633.505859 180.536118 10589.197266", "-95.000000 0.000000 -15.499998");
		}

		GetGame().ObjectDelete(itemCheck);
	}

	private void HandleMeleeItem(notnull ItemBase itemCheck)
	{
		if (itemCheck.IsInherited(Weapon_Base))
		{
			ItemBase moveItem = ItemBase.Cast(ZenMenuSpawnObject(itemCheck.GetType(), "5631.069824 180.399994 10587.299805", "-90.000000 -74.991592 179.999969"));
			if (moveItem)
			{
				ZenFunctions.MoveInventory(itemCheck, moveItem);
				moveItem.SetHealth(itemCheck.GetHealth());
				SpawnTarp();
			}
		}
		else
		if (itemCheck.IsInherited(WoodAxe))
		{
			ZenMenuSpawnObject(itemCheck.GetType(), "5631.649902 180.302643 10586.500000", "-45.000000 0.000000 90.000000");
		}
		else
		if (itemCheck.IsInherited(Pickaxe))
		{
			ZenMenuSpawnObject(itemCheck.GetType(), "5633.505859 180.536118 10589.197266", "-95.000000 0.000000 -15.499998");
		}

		GetGame().ObjectDelete(itemCheck);
	}

	private void SpawnTarp()
	{
		m_Tarp = ZenMenuSpawnObject("ExpansionPropTarp", "5631.170410 180.475128 10588.195313", "-30.999996 0.000244 -0.202904");

		if (!m_Tarp)
			return;

		m_Tarp.SetScale(0.3);
		ZenMenuSpawnObject("ClutterCutterFireplace", "5631.170410 180.475128 10588.195313", "-30.999996 0.000244 -0.202904");
	}
	
	private Object ZenMenuSpawnObject(string type, vector position, vector orientation)
	{
		Object obj = GetGame().CreateObjectEx(type, position, ECE_LOCAL|ECE_NOLIFETIME);
		if (!obj) 
			return NULL;

		obj.SetOrientation(orientation);
		obj.SetOrientation(obj.GetOrientation());

		if (!m_LoadingScreenObjects)
			m_LoadingScreenObjects = new array<Object>;

		m_LoadingScreenObjects.Insert(obj);

		return obj;
	}

	private void PlaySong(string tapeType)
	{
		if (!m_Character || !m_Character.GetCharacterObj() || GetHardcoreDayZClientConfig().MusicMuted)
			return;

		if (GetZenModPackClientConfig().CassetteMusicSetting != 1)
			return;

		string soundSet = Zen_Cassette_Base.GetSongSoundSet(tapeType);
		if (soundSet == "")
			return;

		m_GuitarSong = SEffectManager.PlaySoundOnObject(soundSet, m_Character.GetCharacterObj());
		if (m_GuitarSong)
		{
			m_GuitarSong.SetSoundAutodestroy(true);
			m_GuitarSong.SetSoundFadeOut(3.0);
			m_GuitarSong.SetSoundVolume(0.25);
		}
	}
}