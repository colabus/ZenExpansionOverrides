modded class ExpansionCodeLock
{
	override void DeferredInit()
	{
		super.DeferredInit();

		// Don't damage attached code locks when raiding
		if (GetGame().IsDedicatedServer() && GetHierarchyParent() != NULL)
		{
			if (GetHierarchyParent().IsItemBase())
				SetAllowDamage(false);
		}
	}

	override void OnWasDetached(EntityAI parent, int slot_id)
	{
		super.OnWasDetached(parent, slot_id);

		if (GetGame().IsDedicatedServer())
			SetAllowDamage(true);
	}
}