modded class ActionPackTent
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		Object targetObject = target.GetObject();
		Object targetParent = target.GetParent();
		
		TentBase inventory_tent = TentBase.Cast(targetObject);
		if (inventory_tent && inventory_tent.GetHierarchyRootPlayer())
		{
			return false; //tent is somewhere in player's inventory
		}
		
		if (player && targetObject && targetParent)
		{
			TentBase tent = TentBase.Cast(targetParent);
			if (tent.CanBePacked())
			{
				// Check territory
				if (player.IsInTerritory() && !player.IsInsideOwnTerritory())
					return super.ActionCondition(player, target, item);

				return true;
			}
		}

		return super.ActionCondition(player, target, item);
	}
};