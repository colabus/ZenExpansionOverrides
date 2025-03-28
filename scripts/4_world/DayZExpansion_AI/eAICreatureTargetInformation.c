modded class eAICreatureTargetInformation
{
	override vector GetAimOffset(eAIBase ai = null)
	{
		vector pos;
		if (m_Creature.IsInherited(Animal_UrsusArctos))
			pos = "0 1.2 0";
		else
		if (m_Creature.IsInherited(Croco_Base))
			pos = "0 0.4 0";
		else
			pos = "0 0.6 0";
		
		#ifdef DIAG
		if (EXTrace.AI && ai)
			ai.Expansion_DebugObject(1234567890, m_Creature.GetPosition() + pos, "ExpansionDebugBox_Orange", m_Creature.GetDirection(), ai.GetPosition() + "0 1.5 0", 3.0, ShapeFlags.NOZBUFFER);
		#endif

		return pos;
	}

	override float CalculateThreat(eAIBase ai = null)
	{
		if (!m_Creature.IsDamageDestroyed() && m_Creature.IsInherited(Croco_Base) && vector.Distance(ai.GetPosition(), m_Creature.GetPosition()) < 100.0)
		{
			return 1000.0;
		}

		return super.CalculateThreat(ai);
	}
}