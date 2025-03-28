modded class ExpansionActionCoverVehicle
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!super.ActionCondition(player, target, item))
			return false;

		// Don't allow covering vehicles at Sanctuary
		return vector.Distance(player.GetPosition(), "5640.437500 180.431915 10606.750000") > 100;
	}
}