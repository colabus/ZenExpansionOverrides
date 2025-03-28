modded class ActionConstructor
{
	override void RegisterActions(TTypenameArray actions)
	{
		super.RegisterActions(actions);

		actions.Insert(ActionClimbOnBoat);
		actions.Insert(ZenActionPauseGuitar);

		// Quests
		actions.Insert(ActionRepairPolanaRadioTower);
		actions.Insert(ActionRepairSwarogRadioTower);
		actions.Insert(ActionFreeHermit);
		actions.Insert(ActionEnterContamBunker1);
		actions.Insert(ActionExitContamBunker1);
		actions.Insert(ActionEnterContamBunker2);
		actions.Insert(ActionExitContamBunker2);
		actions.Insert(ActionSearchForRadioactiveCase);
		actions.Insert(ActionCallAirdropRadar);
		actions.Insert(ActionEnterLukowBunker);
		actions.Insert(ActionExitLukowBunker);
		actions.Insert(ActionUnlockLukowPrison);
		actions.Insert(ActionBuryZenRunes);
		actions.Insert(ActionSearchLukowSpecimen);

		// Other
		actions.Insert(ActionZenOpenCargoCrate);
		actions.Insert(ActionZenRaidHelicopterLock);
		actions.Insert(ActionZenUnlockCar);
		actions.Insert(ActionOpenStaticZenMap);

		// View weekly quest on raid alarm
		actions.Insert(ActionViewWeeklyQuestsOnRaidAlarm);
	}
}