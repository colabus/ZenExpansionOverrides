modded class TrapBase
{
	// This will only be tracked until server restarts.
	protected PlayerBase m_ZenPlayerTrapper = NULL;

	PlayerBase GetZenPlayerTrapper()
	{
		return m_ZenPlayerTrapper;
	}

	override void StartActivate(PlayerBase player)
	{
		super.StartActivate(player);

		if (GetGame().IsDedicatedServer())
		{
			m_ZenPlayerTrapper = player;
		}
	}
}