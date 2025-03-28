class Zen_ContaminatedZoneBunkerExit1 extends BuildingSuper
{
	override bool IsBuilding()
	{
		return true;
	}
	
	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionExitContamBunker1);
	}
}