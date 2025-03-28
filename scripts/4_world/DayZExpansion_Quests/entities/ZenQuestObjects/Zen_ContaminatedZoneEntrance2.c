class Zen_ContaminatedZoneBunkerEntrance2 extends BuildingSuper
{
	override bool IsBuilding()
	{
		return true;
	}
	
	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionEnterContamBunker2);
	}
}