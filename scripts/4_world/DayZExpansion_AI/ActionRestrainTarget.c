modded class ActionRestrainTarget
{	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		PlayerBase other_player = PlayerBase.Cast(target.GetObject());
		if (!other_player)
			return false;

		if (other_player.IsAI())
		{
			if (other_player.GetGroup().GetFaction().IsGuard())
				return false;
		}

		return super.ActionCondition(player, target, item);
	}
}