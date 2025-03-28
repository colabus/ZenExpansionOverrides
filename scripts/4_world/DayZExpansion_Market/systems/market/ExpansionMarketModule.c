modded class ExpansionMarketModule
{
	override bool CheckCanUseTrader(PlayerBase player, ExpansionTraderObjectBase trader)
	{
		if (!player || !trader)
			return false;

		if (GetGame().IsDedicatedServer() && GetExpansionSettings().GetQuest().EnableQuests)
		{
			int questID = trader.GetTraderMarket().RequiredCompletedQuestID;
			if (questID > -1)
			{
				//! Check if player has completed required quest
				if (!ExpansionQuestModule.GetModuleInstance().HasCompletedQuest(questID, player.GetIdentity().GetId()))
				{
					ExpansionQuestConfig questConig = ExpansionQuestModule.GetModuleInstance().GetQuestConfigByID(questID);
					if (!questConig)
					{
						Error(ToString() + "::OnExecuteServer - Could not get quest config for quest ID: " + questID);
						return true;
					}
		
					string extra = "";
					if (questID == 1 || questID == 3)
						extra = "\n\nSpeak to Sebastian in the Clothing trader shed";
					if (questID == 2)
						extra = "\n\nRequires Secret Agent Man and Welcome to Sanctuary Quest completed. Speak to Scarecrow the Black Market trader to start Secret Agent Man.\n\nTo start Welcome to Sanctuary, speak to Sebastian in the Clothing trader shed";

					ExpansionNotification("STR_EXPANSION_QUEST", new StringLocaliser("STR_EXPANSION_QUEST_REQUIRED_TRADER", questConig.Title + extra), EXPANSION_NOTIFICATION_ICON_ERROR, COLOR_EXPANSION_NOTIFICATION_ERROR, 7, ExpansionNotificationType.TOAST).Create(player.GetIdentity());
					return false;
				}
				else
				if (!Zen_PowerControlPanel.POWER_ON)
				{
					ExpansionNotification("STR_EXPANSION_QUEST", "The power is out again! Speak to Sebastian at Sanctuary or take a Truck Battery to Irena the engineer at the Karlin Power Plant tower to turn the power back on for another week. She'll reward you for the trouble!", EXPANSION_NOTIFICATION_ICON_ERROR, COLOR_EXPANSION_NOTIFICATION_ERROR, 7, ExpansionNotificationType.TOAST).Create(player.GetIdentity());
					return false;
				}
			}

			if (trader.GetTraderEntity().GetType() == "ExpansionTraderSeaChest")
			{
				if (player.StatGet(AnalyticsManagerServer.STAT_PLAYTIME) > GetFreshieSuppliesConfig().MaximumPlayerAge && player.GetIdentity().GetPlainId() != "76561197983963610")
				{
					int maxAge = GetFreshieSuppliesConfig().MaximumPlayerAge / 60 / 60;
					ExpansionNotification("FRESHIE SUPPLIES", "Only fresh survivors can use this supply chest.\n\nYour character must be less than " + maxAge + " hours old!", EXPANSION_NOTIFICATION_ICON_ERROR, COLOR_EXPANSION_NOTIFICATION_ERROR, 7, ExpansionNotificationType.TOAST).Create(player.GetIdentity());
					return false;
				}
			}
		}

		return super.CheckCanUseTrader(player, trader);
	}

	override private void Exec_RequestPurchase(notnull PlayerBase player, string itemClassName, int count, int currentPrice, ExpansionTraderObjectBase trader, bool includeAttachments = true, int skinIndex = -1, TIntArray attachmentIDs = NULL)
	{
		if (trader.GetTraderEntity().GetType() == "ExpansionTraderSeaChest")
		{
			foreach (FreshieMarketItem fmi : GetFreshieSuppliesConfig().FreshieMarketItems)
			{
				foreach (string s : fmi.Classnames)
				{
					if (s == itemClassName)
					{
						int buyCount;
						if (!fmi.PlayerBought.Find(player.GetIdentity().GetPlainId(), buyCount))
						{
							buyCount = 0;
						}

						if (buyCount >= fmi.MaxBuy)
						{
							ExpansionNotification("FRESHIE SUPPLIES", "Don't be greedy! You've taken the maximum allowed amount of " + fmi.ItemType + " for today.", EXPANSION_NOTIFICATION_ICON_ERROR, COLOR_EXPANSION_NOTIFICATION_ERROR, 7, ExpansionNotificationType.TOAST).Create(player.GetIdentity());
							return;
						}

						break;
					}
				}
			}
		}

		super.Exec_RequestPurchase(player, itemClassName, count, currentPrice, trader, includeAttachments, skinIndex, attachmentIDs);

		if (itemClassName.Contains("dogpreview"))
		{
			Dayz_Doggo dog = player.GetMyDog();
			if (dog)
			{
				Callback(itemClassName, 6969, player.GetIdentity());
				return;
			}
		}
	}

	override void Exec_ConfirmPurchase(notnull PlayerBase player, string itemClassName, bool includeAttachments = true, int skinIndex = -1)
	{
		// If we bought a dog but we already have a dog, stop here
		if (itemClassName.Contains("dogpreview"))
		{
			Dayz_Doggo dog = player.GetMyDog();
			if (dog)
				return;
		}

		super.Exec_ConfirmPurchase(player, itemClassName, includeAttachments , skinIndex);

		// Check for freshie supplies bought
		foreach (FreshieMarketItem fmi : GetFreshieSuppliesConfig().FreshieMarketItems)
		{
			foreach (string s : fmi.Classnames)
			{
				if (s == itemClassName)
				{
					int buyCount;
					if (!fmi.PlayerBought.Find(player.GetIdentity().GetPlainId(), buyCount))
					{
						fmi.PlayerBought.Insert(player.GetIdentity().GetPlainId(), 1);
					}
					else 
					{
						fmi.PlayerBought.Set(player.GetIdentity().GetPlainId(), buyCount + 1);
					}

					break;
				}
			}
		}

		// If we just bought a dog, spawn it in and attach it to the player
		if (itemClassName.Contains("dogpreview"))
		{
			itemClassName.Replace("dogpreview", ""); // get ID
			Dayz_Doggo target_dog = Dayz_Doggo.Cast(GetGame().CreateObject("Doggo_Follow" + itemClassName, "5611.102051 180.636572 10580.422852", false, false, true));

			if (target_dog)
			{
				AIGroup grp = GetGame().GetWorld().GetAIWorld().CreateGroup("DZDogGroupBeh");
				target_dog.InitAIAgent(grp);
				target_dog.SetOwnerId(player.GetID());
				player.setMyDog(target_dog);
				target_dog.SetDoggoCmd(DoggoCmd.STAY);
			}
		}
	}

	override Object Spawn(ExpansionMarketTrader trader, ExpansionMarketItem item, PlayerBase player, inout EntityAI parent, vector position, vector orientation, out int remainingAmount, bool includeAttachments = true, int skinIndex = -1, int level = 0, inout bool attachmentNotAttached = false, TStringIntMap spawnedAmounts = null)
	{
		Object obj = super.Spawn(trader, item, player, parent, position, orientation, remainingAmount, includeAttachments, skinIndex, level, attachmentNotAttached, spawnedAmounts);

		CarScript vehicle = CarScript.Cast(obj);
		if (vehicle)
		{
			if (vehicle.GetType().Contains("bastard"))
			{
				// Hate this, but this bike does not spawn properly with Expansion @ our trader. Always with 1 wheel in the ground. This fixes it but fuck sake...
				GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(RespawnBastard, 2000, false, vehicle, player);
			}
			else
			{
				if (player)
					vehicle.SetTraderLocked(player);
			}
		}

		return obj;
	}

	// pass car here and transfer inventory.
	void RespawnBastard(CarScript bike, PlayerBase player)
	{
		if (!bike)
			return;

		CarScript newBike = CarScript.Cast(GetGame().CreateObjectEx(bike.GetType(), bike.GetPosition(), ECE_SETUP|ECE_KEEPHEIGHT|ECE_PLACE_ON_SURFACE));
		if (newBike)
		{
			ZenFunctions.MoveInventory(bike, newBike);
			newBike.SetOrientation(bike.GetOrientation());
			newBike.ZenFillUpCarFluids();
			if (player)
				newBike.SetTraderLocked(player);
		}
	}
}