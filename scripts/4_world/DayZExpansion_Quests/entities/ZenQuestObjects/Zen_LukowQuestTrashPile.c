class Zen_LukowQuestTrashPile extends BuildingSuper
{
	override bool IsBuilding()
	{
		return true;
	}

	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionSearchLukowSpecimen);
	}
}