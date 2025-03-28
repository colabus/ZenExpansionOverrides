class Zen_HermitQuestNote extends ZenNote
{
	void Zen_HermitQuestNote()
	{
		if (GetGame().IsDedicatedServer())
		{
			SetAllowDamage(false);
		}
	}

	override ZenNoteData GetNoteData()
	{
		m_ZenNoteData = new ZenNoteData;
		m_ZenNoteData.m_FontIndex = 5;
		m_ZenNoteData.m_DateText = "Blood-stained Note";
		m_ZenNoteData.m_NoteText = "Last night a group of strange armed men found my camp and shared it with me. They seemed cold and hungry like the rest of us, but I have a really bad feeling about these guys. If you find this note, then I'm either dead or kidnapped. I'm hoping for the latter. [There's a blood-stained trail leading into the woods... I should track it.]";
		m_ZenNoteData.m_ARGBColour = ARGB(255, 0, 0, 0);
		return m_ZenNoteData;
	}

	override bool CanPutInCargo(EntityAI parent)
	{
		return false;
	}

	override bool CanPutIntoHands(EntityAI parent)
	{
		return false;
	}
}