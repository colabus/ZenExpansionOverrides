/*modded class ExpansionActionEnterCodeLock
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!GetExpansionSettings().GetBaseBuilding(false).IsLoaded())
			return false;

		m_Target = ItemBase.Cast(target.GetParentOrObject());

		if (m_Target)
		{
			m_IsKnownUser = m_Target.IsKnownUser(player);

			// Don't allow "unlock" of gates/doors - they can just open/close them and remove codelock with ChangePin if they want to.
			if (m_IsKnownUser)
				return false;
		}
		
		return super.ActionCondition(player, target, item);
	}
}*/