class Zen_ContaminatedZoneBunkerEntrance1 extends BuildingSuper
{
	override bool IsBuilding()
	{
		return true;
	}
	
	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionEnterContamBunker1);
	}
}