class Zen_ContaminatedZoneBunkerSkeleton extends BuildingSuper
{
	override bool IsBuilding()
	{
		return true;
	}
	
	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionSearchForRadioactiveCase);
	}
}