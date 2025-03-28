#ifdef ENFUSION_AI_PROJECT
modded class UniversalLight
{
	override void EEInit()
	{
		#ifdef SERVER
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.CheckAiHeadtorch, 1000, false);
		#endif
	}

	void CheckAiHeadtorch()
	{
		PlayerBase owner = PlayerBase.Cast(GetHierarchyRootPlayer());

		if (owner && owner.IsAI())
		{
			GetInventory().CreateAttachment("Battery9V");
			
			if (!HasEnergyManager() || !GetCompEM() || !GetCompEM().CanWork())
				return;

			GetCompEM().SwitchOn();
		}
	}
}
#endif