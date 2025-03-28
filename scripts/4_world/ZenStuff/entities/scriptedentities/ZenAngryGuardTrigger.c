class ZenAngryGuardTrigger extends Trigger
{
	protected int m_Radius;

	void SetupZenAngryGuardTrigger(int radius)
	{
		ZenModLogger.Log("SetupZenAngryGuardTrigger @ " + GetPosition(), "triggers");

		m_Radius = radius;
		SetCollisionSphere(m_Radius);
	}

	override void OnEnter(Object obj)
	{
		if (!obj.IsMan() || !GetGame().IsDedicatedServer())
			return;

		PlayerBase player = PlayerBase.Cast(obj);
		if (!player || !player.GetIdentity() || player.IsAI())
			return;

		NaughtyPlayer np = GetAngryGuardsConfig().GetNaughtyPlayer(player.GetIdentity().GetPlainId());
		if (!np)
			return;

		int timestamp = JMDate.Now(false).GetTimestamp();
		if (timestamp >= np.BanishmentExpiry)
		{
			player.SetBanished(false);
			return;
		}

		// Config exists - trigger player's aggro timer
		player.Zen_TriggerGuardAggro(m_Radius + 50, 3600);
		player.SetBanished(true);
		string banishMsg = player.InformPlayerOfBanishment(np);

		ZenModLogger.Log("Banished player " + player.GetIdentity().GetPlainId() + " - " + banishMsg, "sanctuary");
	};
};