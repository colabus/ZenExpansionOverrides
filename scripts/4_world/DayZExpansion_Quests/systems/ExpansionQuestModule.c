modded class ExpansionQuestModule
{
	override void OnInit()
	{
		super.OnInit();

		Expansion_RegisterClientRPC("RPC_RequestOpenQuestMenuBaseRadio");
	}

	override void CreateClientMarker(vector pos, string text, int questID, PlayerIdentity identity, int objectiveIndex, int visibility = -1)
	{
		// Check if this marker is to be hidden or not (eg. quest to track blood trail, don't want map marker for that!)
		foreach (ExpansionHideQuestMarker hideCfg : GetZenQuestHideNpcConfig().HideQuestMarkers)
		{
			if (hideCfg.QuestID == questID && hideCfg.QuestObjectiveHideIndex == objectiveIndex)
				return;
		}

		super.CreateClientMarker(pos, text, questID, identity, objectiveIndex, visibility);
	}

	override protected void CompleteQuest(ExpansionQuest quest, string playerUID, PlayerIdentity identity, bool isAutoComplete = false, ExpansionQuestRewardConfig reward = null, int selectedObjItemIndex = -1)
	{
		super.CompleteQuest(quest, playerUID, identity, isAutoComplete, reward, selectedObjItemIndex);

		PlayerBase player = PlayerBase.Cast(identity.GetPlayer());
		if (!player)
			return;

		ExpansionQuestEXP expReward = GetZenQuestExpConfig().GetQuestReward(quest.GetQuestConfig().GetID());
		if (expReward && expReward.EXP > 0)
		{
			string skillName = expReward.Skill;
			skillName.ToLower();

			switch (skillName)
			{
				case "immunity":
					player.AddExperience(SyberiaSkillType.SYBSKILL_IMMUNITY, expReward.EXP);
					break;
				case "athletics":
					player.AddExperience(SyberiaSkillType.SYBSKILL_ATHLETICS, expReward.EXP);
					break;
				case "strength":
					player.AddExperience(SyberiaSkillType.SYBSKILL_STRENGTH, expReward.EXP);
					break;
				case "medicine":
					player.AddExperience(SyberiaSkillType.SYBSKILL_MEDICINE, expReward.EXP);
					break;
				case "stealth":
					player.AddExperience(SyberiaSkillType.SYBSKILL_STEALTH, expReward.EXP);
					break;
				case "survival":
					player.AddExperience(SyberiaSkillType.SYBSKILL_SURVIVAL, expReward.EXP);
					break;
				case "hunting":
					player.AddExperience(SyberiaSkillType.SYBSKILL_HUNTING, expReward.EXP);
					break;
				case "crafting":
					player.AddExperience(SyberiaSkillType.SYBSKILL_CRAFTING, expReward.EXP);
					break;
				
				default:
					ZenFunctions.SendGlobalMessage("[QUEST] Failed to add EXP to player for quest " + quest.GetQuestConfig().GetID() + " - tell Zenarchist he fucked up!");
					break;
			}
		}

		// Dog collect quest
		if (quest.GetQuestConfig().GetID() == 9)
		{
			Dayz_Doggo dog = player.GetMyDog();
			if (dog)
			{	
				array<EntityAI> children = new array<EntityAI>;
				dog.GetInventory().EnumerateInventory(InventoryTraversalType.LEVELORDER, children);
				foreach (EntityAI child : children)
				{
					if (child)
					{
						child.SetLifetime(14400);
						dog.GetInventory().DropEntity(InventoryMode.SERVER, dog, child);
					}
				}

				dog.DeleteSafe();
				player.resetDog();
			}

			return;
		}

		// !Power turn on quest + repeatable version from quest board
		if (quest.GetQuestConfig().GetID() != 5 && quest.GetQuestConfig().GetID() != 4)
			return;

		// Someone turned the lights on!
		Zen_PowerControlPanel m_PowerPanel = GetPowerPanel();
		if (!m_PowerPanel)
		{
			ZenModLogger.Log("ERROR: Tell Zenarchist he fucked up! Power control panel not found.", "error");
			return;
		}

		// Update battery timestamp
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(m_PowerPanel.DeleteBattery, 1, false);
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.SpawnBattery, 500, false, m_PowerPanel);
	}

	private void SpawnBattery(Zen_PowerControlPanel panel)
	{
		if (panel)
			panel.GetInventory().CreateAttachment("TruckBattery");
	}

	private Zen_PowerControlPanel GetPowerPanel()
	{
		Zen_PowerControlPanel panel;
		array<Object> objectsAtPowerStation = new array<Object>;
		GetGame().GetObjectsAtPosition3D(GetZenLightingConfig().ControlPanelLocation, 1, objectsAtPowerStation, null);

		for (int x = 0; x < objectsAtPowerStation.Count(); x++)
		{
			if (objectsAtPowerStation[x].IsInherited(Zen_PowerControlPanel))
			{
				panel = Zen_PowerControlPanel.Cast(objectsAtPowerStation[x]);

				// We found the control panel - stop here.
				if (panel)
				{
					return panel;
				}
			}
		}

		return NULL; // Power panel not found at location.
	}

	override ExpansionQuestNPCData GetQuestNPCDataByID(int id)
	{
		ExpansionQuestNPCData foundData;
		if (m_QuestsNPCs.Find(id, foundData))
		{
			if (foundData.GetID() == 0) // Zenarchist at camp
			{
				string songTitle = "Unknown Song";

				// Scan for any invisible music (eg. guitar player)
				array<Object> nearbyObjects = new array<Object>;
				GetGame().GetObjectsAtPosition3D(foundData.Position, GetZenMusicConfig().StaticBoomboxTurnsOffInvisibleRange, nearbyObjects, NULL);
				foreach (Object obj : nearbyObjects)
				{
					if (obj.IsInherited(Zen_BoomBox_Invisible_Static))
					{
						Zen_BoomBox_Invisible_Static staticInvisBoombox = Zen_BoomBox_Invisible_Static.Cast(obj);
						if (staticInvisBoombox && staticInvisBoombox.GetCassette())
						{
							songTitle = staticInvisBoombox.GetCassette().ConfigGetString("descriptionShort");
							break;
						}
					}
				}

				songTitle.Replace("-", "by");
				foundData.SetDefaultNPCText("He's the server admin. He's playing the song " + songTitle + ". Did you know: " + ZenLoadingScreenConfig.Tips.GetRandomElement());
			}

			return foundData;
		}

		return NULL;
	}

	override bool QuestDisplayConditions(ExpansionQuestConfig config, PlayerBase player, ExpansionQuestPersistentData playerQuestData = null, int questNPCID = -1, bool displayQuestsWithCooldown = false, bool skipPreQuestCheck = false)
	{
		if (!super.QuestDisplayConditions(config, player, playerQuestData, questNPCID, displayQuestsWithCooldown))
			return false;

		#ifndef SERVER
		// Check post-quest conditions
		foreach (ExpansionHideQuest hideQuestConfig : GetZenQuestHideNpcConfig().HideQuests)
		{
			if (hideQuestConfig.QuestHideID == config.ID)
			{
				// If player has already completed the quest that hides this quest, don't allow player to see the quest in list
				if (ExpansionQuestModule.GetModuleInstance().HasCompletedQuest(hideQuestConfig.QuestCompletedID, player.GetIdentity().GetId()))
					return false;
			}
		}
		#endif

		// If above checks pass then quest was ok all along.
		return true;
	}

	bool Zen_HasStartedQuest(int questID, string playerUID)
	{
		ExpansionQuestPersistentData playerQuestData = GetPlayerQuestData(playerUID);
		if (!playerQuestData)
			return false;

		ExpansionQuestState questState = playerQuestData.GetQuestStateByQuestID(questID);
		if (questState != ExpansionQuestState.STARTED && questState != ExpansionQuestState.CAN_TURNIN && questState != ExpansionQuestState.COMPLETED)
			return false;

		return true;
	}

	// Expansion quest module removes player quest data from cache upon disconnect which fucks up my highscore saving
	// so this is a hacky solution - just update the player's quest points upon disconnect if their highscore record is found.
	// The other highscore stuff is handled in PlayerBase.c OnDisconnect(). Not ideal, but fuck it - I cbf finding a better way right now.
	// this already took way way way longer to implement than I expected, as usual.
	override void OnClientDisconnect(Class sender, CF_EventArgs args)
	{
		//! Save quest points before removing player from cached Expansion list, then call super()
		auto cArgs = CF_EventPlayerDisconnectedArgs.Cast(args);
		SyberiaHighscoreRecord record2 = GetHighscoresConfig().GetHighscoreRecord(cArgs.UID);
		if (cArgs && record2)
		{
			int questPoints = 0;

			// Save Expansion quest points 
			ExpansionQuestPersistentData questPlayerData = GetPlayerQuestDataByUID(cArgs.UID);
			if (questPlayerData)
			{
				for (int i = 0; i < questPlayerData.QuestData.Count(); i++)
				{
					ExpansionQuestPersistentQuestData qd = questPlayerData.QuestData.GetElement(i);
					if (qd != NULL)
					{
						questPoints = questPoints + qd.CompletionCount;
					}
				}
			}

			record2.QuestPoints = questPoints;
		}

		super.OnClientDisconnect(sender, args);
	}

	static bool VIEWING_QUESTS_ON_BASE_RADIO = false;

	override void RPC_RequestOpenQuestMenu(PlayerIdentity identity, Object target, ParamsReadContext ctx)
	{
		VIEWING_QUESTS_ON_BASE_RADIO = false;
		super.RPC_RequestOpenQuestMenu(identity, target, ctx);
	}

	void RPC_RequestOpenQuestMenuBaseRadio(PlayerIdentity identity, Object target, ParamsReadContext ctx)
	{
		RPC_RequestOpenQuestMenu(identity, target, ctx);
		VIEWING_QUESTS_ON_BASE_RADIO = true; // hide completion button on GUI
	}
}