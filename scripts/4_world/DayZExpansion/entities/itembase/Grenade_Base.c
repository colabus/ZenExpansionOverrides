modded class Grenade_Base
{
	protected PlayerBase m_ZenUnpinPlayer = NULL;

	PlayerBase GetZenUnpinPlayer()
	{
		return m_ZenUnpinPlayer;
	}

	// Detect by players unpins
	override void Unpin()
	{
		super.Unpin();

		if (GetGame().IsDedicatedServer() && GetHierarchyRootPlayer() != NULL)
		{
			PlayerBase pb = PlayerBase.Cast(GetHierarchyRootPlayer());
			if (pb)
			{
				if (pb.IsAI())
				{
					// Don't count expansion AI
					m_ZenUnpinPlayer = NULL;
					return;
				}

				m_ZenUnpinPlayer = pb;
			}
		}
		else 
		{
			m_ZenUnpinPlayer = NULL;
		}
	}
}