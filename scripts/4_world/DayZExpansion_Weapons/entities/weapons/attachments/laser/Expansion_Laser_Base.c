#ifdef ENFUSION_AI_PROJECT
modded class Expansion_Laser_Base: UniversalLight
{
	#ifdef SERVER
	override void EEInit()
	{
		super.EEInit();
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(CheckForAIParent, 1000, false);
	}

	private void CheckForAIParent()
	{
		if (!HasEnergyManager() || !GetCompEM() || !GetCompEM().CanWork())
			return;

		PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());
		if (!player)
			return;

		// Turn the frickin lazer beams on
		if (player.IsAI())
			GetCompEM().SwitchOn();
	}
	#endif
};
#endif

// Switch off laser when gun is removed from hands
modded class Weapon_Base
{
	#ifdef SERVER
	override void EEItemLocationChanged (notnull InventoryLocation oldLoc, notnull InventoryLocation newLoc)
	{
		super.EEItemLocationChanged(oldLoc, newLoc);

		if (oldLoc.GetType() == InventoryLocationType.HANDS)
		{
			Expansion_Laser_Base laserBase = Expansion_Laser_Base.Cast(GetAttachmentByType(Expansion_Laser_Base));
			if (laserBase)
			{
				laserBase.GetCompEM().SwitchOff();
			}
		}
	}
	#endif
}