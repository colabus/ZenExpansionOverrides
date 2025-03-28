class Zen_LukowBunkerExit extends BuildingSuper
{
	override bool IsBuilding()
	{
		return true;
	}

	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionExitLukowBunker);
	}
}