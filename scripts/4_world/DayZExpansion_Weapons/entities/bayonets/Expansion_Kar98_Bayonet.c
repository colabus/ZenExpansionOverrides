modded class Expansion_Kar98_Bayonet: Inventory_Base
{
	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionBurnSewTarget);
		AddAction(ActionUnrestrainTarget);
		AddAction(ActionSkinning);
		AddAction(ActionMineBush);
		AddAction(ActionMineTreeBark);
		AddAction(ActionBurnSewSelf);
		AddAction(ActionDigWorms);
		AddAction(ActionShaveTarget);
		AddAction(ActionDisarmMine);
		AddAction(ActionDisarmExplosive);
		AddAction(ActionShave);
		AddAction(ActionCraftBolts);
	}
}