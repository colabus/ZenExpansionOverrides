modded class Zen_CraftableMap
{
	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionOpenStaticZenMap);
	}
}

class bldr_mil_enoch_map extends BuildingSuper
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