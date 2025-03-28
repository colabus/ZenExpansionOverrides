class Zen_HermitQuestDoor extends BuildingSuper
{
	override bool IsBuilding()
	{
		return true;
	}
	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionFreeHermit);
	}
}