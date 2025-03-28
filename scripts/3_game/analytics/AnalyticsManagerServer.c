modded class AnalyticsManagerServer
{
	override void OnPlayerKilled(Man killer, EntityAI target)
	{
		// Don't count ExpansionAI
		if (target && target.GetType().Contains("eAI"))
			return;

		// Delay PVP kill update by 90 secs
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DelayedKillPVP, 90000, false, killer);
	}

	void DelayedKillPVP(Man killer)
	{
		if (killer)
			killer.StatUpdate(STAT_PLAYERS_KILLED, 1);
	}
}
