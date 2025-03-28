modded class ActionFoldBaseBuildingObject
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (item != NULL && item.Type() == ExpansionBarbedWire)
		{
			if (player.IsInTerritory())// && !player.IsInsideOwnTerritory())
			{
				return false;
			}
		}

		return super.ActionCondition(player, target, item);
	}
}