class Zen_ContaminatedZoneBunkerExit2 extends BuildingSuper
{
	override bool IsBuilding()
	{
		return true;
	}
	
	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionExitContamBunker2);
	}
}