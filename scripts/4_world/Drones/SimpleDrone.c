modded class ActionConnectToDrone extends ActionContinuousBase
{
	// Don't allow connecting to zone inside sanctuary
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
        if (!super.ActionCondition(player, target, item))
			return false;

		return player && !player.InSanctuary();
    }
}

modded class SimpleDrone extends EVG_DroneBase
{
	#ifdef SERVER
	override void SpecialActionButton()
	{
		vector pos = GetPosition();
		pos[1] = 0;

		float sancDist = vector.Distance(pos, "5648.420410 0 10609.200195");
		if (sancDist <= 300)
			return;

		super.SpecialActionButton();
	}
	#endif
}