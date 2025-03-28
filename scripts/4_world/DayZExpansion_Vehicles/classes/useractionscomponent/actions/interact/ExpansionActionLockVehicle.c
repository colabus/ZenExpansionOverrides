// Only allow locking helis
modded class ExpansionActionLockVehicle: ActionInteractBase
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		// Allow keys on PVE
		if (IsServerPVE())
			return super.ActionCondition(player, target, item);

		if (!super.ActionCondition(player, target, item))
			return false;

		ExpansionHelicopterScript helicopter;
		if (!Class.CastTo( helicopter, target.GetParentOrObject()))
			return false;

		return true;
	}
}