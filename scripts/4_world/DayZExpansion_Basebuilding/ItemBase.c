// totally fucked solution to Expansion items appearing on roofs when dropped on ground
/*modded class ItemBase
{
	bool m_WasThrown = false;

	override void OnItemLocationChanged(EntityAI old_owner, EntityAI new_owner)
	{
		super.OnItemLocationChanged(old_owner, new_owner);

		if (m_WasThrown)
			return;

		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(CheckExpansionRoof, 1, false, old_owner, new_owner);
	}

	void CheckExpansionRoof(EntityAI old_owner, EntityAI new_owner)
	{
		if (!old_owner)
			return;

		PlayerBase player = PlayerBase.Cast(old_owner);
		if (!player)
			player = PlayerBase.Cast(old_owner.GetHierarchyRootPlayer());

		if (!player)
			return;

		if (new_owner)
			return;

		float itemZ = GetPosition()[1];
		float ourZ = player.GetPosition()[1];
		float diff = Math.AbsFloat(itemZ - ourZ);

		if (diff < 2)
			return;

		// Perform raycast
		bool needsMoving = false;
		vector start = player.GetPosition();
		vector end = player.GetPosition();
		end[1] = end[1] + diff + 0.5;
		float raycastRadius = 0.25;
		RaycastRVParams rayInput = new RaycastRVParams(start, end, player, raycastRadius);
		rayInput.flags = CollisionFlags.ALLOBJECTS;
		array<ref RaycastRVResult> results = new array<ref RaycastRVResult>;

		if (DayZPhysics.RaycastRVProxy(rayInput, results))
		{
			if (!results.Count() || results.Count() == 0)
				return;

			for (int i = 0; i < results.Count(); i++)
			{
				if (results.Get(i).obj && results.Get(i).obj.IsInherited(ExpansionBaseBuilding))
				{
					needsMoving = true;
					break;
				}
			}
		}

		if (needsMoving)
		{
			SetPosition(player.GetPosition() + "0 0.25 0");
			SetSynchDirty();
		}
	}
}*/