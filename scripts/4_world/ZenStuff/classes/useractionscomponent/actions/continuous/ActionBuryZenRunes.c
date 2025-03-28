class ActionBuryZenRunes: ActionContinuousBase
{
	void ActionBuryZenRunes()
	{
		m_CallbackClass		= ActionBuryAshesCB;
		m_CommandUID		= DayZPlayerConstants.CMD_ACTIONFB_DIGMANIPULATE;
		m_FullBody			= true;
		m_StanceMask		= DayZPlayerConstants.STANCEMASK_ERECT;
		m_SpecialtyWeight	= UASoftSkillsWeight.ROUGH_LOW;
		m_Text = "#bury";
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionTarget	= new CCTNonRuined(UAMaxDistances.DEFAULT);
		m_ConditionItem		= new CCINonRuined();
	}
	
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (player.IsPlacingLocal())
		{
			return false;
		}

		if (player.GetBrokenLegs() == eBrokenLegs.BROKEN_LEGS)
		{
			return false;
		}

		// Check location is a quest location
		ZenRune_Base runeBase = ZenRune_Base.Cast(target.GetObject());
		if (runeBase)
		{
			bool isInRange = vector.Distance(runeBase.GetPosition(), runeBase.BuryLocation()) < 500;
			if (!isInRange)
			{
				return false;
			}

			int liquidType;
			string surfaceType;
			GetGame().SurfaceUnderObject(runeBase, surfaceType, liquidType);
			if (GetGame().IsSurfaceDigable(surfaceType))
			{
				return true;
			}
		}
		
		return false;
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		//destroy rune
		GetGame().ObjectDelete(action_data.m_Target.GetObject());

		MiscGameplayFunctions.DealAbsoluteDmg(action_data.m_MainItem, 4);
		
		//add soft skill specialty
		action_data.m_Player.GetSoftSkillsManager().AddSpecialty(UASoftSkillsWeight.ROUGH_LOW);
	}
}