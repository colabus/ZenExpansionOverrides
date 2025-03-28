class Zen_LukowBunkerEntrance extends BuildingSuper
{
	override bool IsBuilding()
	{
		return true;
	}

	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionEnterLukowBunker);
	}
}