modded class ExpansionActionOpenQuestMenu
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		Object targetObject;
		if (!Class.CastTo(targetObject, target.GetParentOrObject()))
			return false;

		ExpansionQuestNPCAIBase npcAI = ExpansionQuestNPCAIBase.Cast(targetObject);
		if (npcAI && npcAI.ZenIsHidden())
			return false;

		ExpansionQuestNPCBase npcB = ExpansionQuestNPCBase.Cast(targetObject);
		if (npcB && npcB.ZenIsHidden())
			return false;

		ExpansionQuestStaticObject npcObject = ExpansionQuestStaticObject.Cast(targetObject);
		if (npcObject)
		{
			if (npcObject.ZenIsHiddenStatic())
				return false;

			m_Text = "Read";

			// Talk through bars
			if (npcObject.GetType() == "Quest_Prison_MainCastle_barsdoors")
				m_Text = "#STR_EXPANSION_QUEST_ACTION_TALK" + " " + targetObject.GetDisplayName();
			
			// Skeleton
			if (npcObject.GetType().Contains("Quest_Skeleton"))
				m_Text = "#syb_search_target_inv" + " " + targetObject.GetDisplayName();
			
			return true;
		}

		return super.ActionCondition(player, target, item);
	}
}