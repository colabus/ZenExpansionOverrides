#ifdef ENFUSION_AI_PROJECT
modded class ExpansionQuestNPCAIBase
{
	void ExpansionQuestNPCAIBase()
	{
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(StartPlayingGuitar, 5000, false);
	}

	void StartPlayingGuitar()
	{
		// If AI has guitar in hands then they're guitarist at Sanctuary
		if (GetItemInHands() && GetItemInHands().GetType().Contains("Expansion_Guitar"))
		{
			StartCommand_Action(1051, ActionBaseCB, DayZPlayerConstants.STANCEMASK_ALL);
			GetGame().CreateObjectEx("ClutterCutterFireplace", GetPosition(), ECE_PLACE_ON_SURFACE);

			// Face him properly!
			SetPosition("5634.168945 180.268402 10587.649414");
			SetOrientation("-135.962784 0.000000 -0.000000");
		}
	}
}
#endif