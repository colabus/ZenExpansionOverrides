/*modded class WeaponStartAction extends WeaponStateBase
{
	override void OnEntry(WeaponEventBase e)
	{
		return;
	}
};*/

/*modded class DayZPlayerImplement
{
	
}*/

/*modded class Weapon_Base
{
	override void EEItemLocationChanged (notnull InventoryLocation oldLoc, notnull InventoryLocation newLoc)
	{
		super.EEItemLocationChanged(oldLoc, newLoc);

		if (newLoc.GetType() == InventoryLocationType.HANDS)
		{
			PlayerBase player;
			if (newLoc.GetParent() && PlayerBase.CastTo(player, newLoc.GetParent()))
			{ 
				ZenFunctions.DebugMessage("Put weapon in hands=" + GetType() + " - take back to inventory");
				player.ServerDropEntity(this);

				// todo: only do this if gun is loaded

				// Get human inventory
				HumanInventory inventory = player.GetHumanInventory();
				if (!inventory)
					return;

				// Get weapon reserved location in inventory (dst)
				InventoryLocation loc_dst = new InventoryLocation;
				int reservedIndex = inventory.FindUserReservedLocationIndex(this);
				inventory.GetUserReservedLocation(reservedIndex, loc_dst);

				// Get current weapon inventory location (src)
				InventoryLocation loc_src = new InventoryLocation;
				this.GetInventory().GetCurrentInventoryLocation(loc_src);

				// If player has moved an item into the matchbox reserve slot, or ServerTakeToDst fails, just take matchbox to anywhere in inventory.
				if (reservedIndex == -1 || !player.ServerTakeToDst(loc_src, loc_dst))
				{
					// If we can't take the matchbox to inventory for whatever reason, do nothing, leave it in player's hands and spawn match on ground
					if (!player.ServerTakeEntityToInventory(FindInventoryLocationType.ANY_CARGO, this))
					{
						// drop gun on ground
						player.ServerDropEntity(this);
					}
				}

				ZenFunctions.DebugMessage("You cannot draw your loaded guns inside Sanctuary!");
			}
		}
	}
}*/