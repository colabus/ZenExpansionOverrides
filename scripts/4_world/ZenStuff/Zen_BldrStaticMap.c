class Zen_BldrStaticMap extends BuildingSuper
{
	override bool IsBuilding()
	{
		return false;
	}

	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionOpenStaticZenMap);
	}
}