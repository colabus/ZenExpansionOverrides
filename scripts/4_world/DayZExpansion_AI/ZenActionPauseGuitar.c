class ZenActionPauseGuitar: ActionInteractBase
{
	void ZenActionPauseGuitar()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_ATTACHITEM;
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTCursor;
		m_Text = "Take a break";
	}

	override typename GetInputType()
	{
		return InteractActionInput;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		Object targetObject;
		if (!Class.CastTo(targetObject, target.GetParentOrObject()))
			return false;

		ExpansionQuestNPCAIBase npcAI = ExpansionQuestNPCAIBase.Cast(targetObject);
		if (!npcAI)
			return false;

		if (!npcAI.GetItemInHands() || !npcAI.GetItemInHands().GetType().Contains("Guitar"))
			return false;

		return true;
	}

	override void OnExecuteServer(ActionData action_data)
	{
		if (!action_data.m_Target || !action_data.m_Target.GetObject())
			return;

		// Scan for any invisible music (eg. guitar player) and stop their music
		array<Object> nearbyObjects = new array<Object>;
		GetGame().GetObjectsAtPosition3D(action_data.m_Target.GetObject().GetPosition(), GetZenMusicConfig().StaticBoomboxTurnsOffInvisibleRange, nearbyObjects, NULL);

		foreach (Object obj : nearbyObjects)
		{
			if (obj.IsInherited(Zen_BoomBox_Invisible_Static))
			{
				Zen_BoomBox_Invisible_Static staticInvisBoombox = Zen_BoomBox_Invisible_Static.Cast(obj);
				if (staticInvisBoombox)
				{
					if (!staticInvisBoombox.IsPlayingSong())
					{
						staticInvisBoombox.StartPlayingAgain();
						GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(staticInvisBoombox.StartPlayingAgain);
					}
					else
					{
						staticInvisBoombox.PauseMusicServer();
						GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(staticInvisBoombox.StartPlayingAgain, 300 * 1000.0, false);
					}
					
					break;
				}
			}
		}
	}
}
