modded class ExpansionBookMenuTabPlayerProfile
{
	override void SetStats(ExpansionSyncedPlayerStats stats)
	{
		if (!stats || stats.m_PlainID != string.Empty || !stats.m_HasBaseStats || !stats.m_HasRegisteredStats)
			return;

		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());

		stats.Acquire(player);

		bool hasPerk = false;
		int timestamp = JMDate.Now(false).GetTimestamp();
		if (player.GetPerkBoolValue(SyberiaPerkType.SYBPERK_MEDICINE_EXPBOOKSTATS) && timestamp - player.m_LastThermometerCheck <= 300)
			hasPerk = true;

		//! Profile stats
		if (hasPerk)
		{
			m_PlayerProfileController.ProfileTimePlayed  = ExpansionStatic.GetTimeString(stats.m_Playtime);
			m_PlayerProfileController.ProfileLongestShot = ExpansionStatic.GetDistanceString(stats.m_LongestShot);
			m_PlayerProfileController.ProfilePlayerKills = ExpansionStatic.GetValueString(stats.m_PlayersKilled) + " Kills";
			m_PlayerProfileController.ProfileZombieKills = ExpansionStatic.GetValueString(stats.m_InfectedKilled) + " Kills";
			m_PlayerProfileController.ProfileAnimalKills = ExpansionStatic.GetValueString(stats.m_AnimalsKilled) + " Kills";
		}
		else
		{
			if (!player.GetPerkBoolValue(SyberiaPerkType.SYBPERK_MEDICINE_EXPBOOKSTATS))
				m_PlayerProfileController.ProfileTimePlayed	 = "Medicine Perk Required";
			else 
				m_PlayerProfileController.ProfileTimePlayed	 = "Thermometer Required";

			m_PlayerProfileController.ProfileLongestShot = "???";
			m_PlayerProfileController.ProfilePlayerKills = "???";
			m_PlayerProfileController.ProfileZombieKills = "???";
			m_PlayerProfileController.ProfileAnimalKills = "???";
		}

		#ifdef HEROESANDBANDITSMOD
		if (m_ShowHaBStats)
		{
			m_PlayerProfileController.HaB_Affinity = g_HeroesAndBanditsPlayer.getAffinity().DisplayName;
			m_PlayerProfileController.HaB_Level = g_HeroesAndBanditsPlayer.getLevel().Name;
			if ( GetHeroesAndBanditsSettings().Mode != 1 )
			{
				m_PlayerProfileController.HaB_Humanity = ExpansionStatic.GetValueString(g_HeroesAndBanditsPlayer.getHumanity());
			}
			else
			{
				m_PlayerProfileController.HaB_Humanity = ExpansionStatic.GetValueString(g_HeroesAndBanditsPlayer.getAffinityPoints( g_HeroesAndBanditsPlayer.getAffinityName() ));
			}
			if ( !GetHeroesAndBanditsSettings().HideKillsInGUI )
				m_PlayerProfileController.ProfilePlayerKills = ExpansionStatic.GetValueString(stats.m_PlayersKilled) + " (" + ExpansionStatic.GetValueString( g_HeroesAndBanditsPlayer.getStat("Kill") ) + ") Kills";
			
			m_PlayerProfileController.ProfileZombieKills = ExpansionStatic.GetValueString(stats.m_InfectedKilled) + " (" + ExpansionStatic.GetValueString( g_HeroesAndBanditsPlayer.getStat("ZombieKill") ) + ") Kills";
			m_PlayerProfileController.ProfileAnimalKills = ExpansionStatic.GetValueString(stats.m_AnimalsKilled) + " (" + ExpansionStatic.GetValueString( g_HeroesAndBanditsPlayer.getStat("Hunt") ) + ") Kills";
			m_PlayerProfileController.HaB_Medic = ExpansionStatic.GetValueString( g_HeroesAndBanditsPlayer.getStat("Medic") );
			m_PlayerProfileController.HaB_Raid = ExpansionStatic.GetValueString( g_HeroesAndBanditsPlayer.getStat("Raid") );
			m_PlayerProfileController.HaB_Suicides = ExpansionStatic.GetValueString( g_HeroesAndBanditsPlayer.getStat("Sucide") );

			m_PlayerProfileController.NotifyPropertiesChanged({"HaB_Affinity", "HaB_Level", "HaB_Humanity", "HaB_Medic", "HaB_Raid", "HaB_Suicides"});
		}
		#endif

		if (hasPerk)
		{
			m_PlayerProfileController.ProfileDistanceTraveled = ExpansionStatic.GetDistanceString(stats.m_Distance);
			m_PlayerProfileController.ProfileWeight = ExpansionStatic.GetWeightString(stats.m_Weight);
		}
		else 
		{
			m_PlayerProfileController.ProfileDistanceTraveled = "???";
			m_PlayerProfileController.ProfileWeight = "???";
		}

		array<string> profile_properties = {"ProfileTimePlayed", "ProfileLongestShot", "ProfilePlayerKills", "ProfileZombieKills", "ProfileAnimalKills", "ProfileDistanceTraveled", "ProfileWeight"};
		
		if (player.HasBloodTypeVisible())
		{
			string type;
			bool positive;
			m_PlayerProfileController.PlayerBloodType = BloodTypes.GetBloodTypeName(player.GetBloodType(), type, positive);
			profile_properties.Insert("PlayerBloodType");
		}
		else
		{
			profile_blood_spacer.Show(false);
		}

		m_PlayerProfileController.NotifyPropertiesChanged(profile_properties);

		//! Player preview
		if (!m_PlayerProfileController.PlayerCharacter)
		{
			m_PlayerProfileController.PlayerCharacter = GetGame().GetPlayer();
			m_PlayerProfileController.NotifyPropertyChanged("PlayerCharacter");
		}
		
		//! Player conditions
		if (hasPerk)
		{
			m_PlayerProfileController.PlayerHealth = stats.m_Health;
			m_PlayerProfileController.PlayerHealthValue = stats.m_Health.ToString() + "%";
			m_PlayerProfileController.PlayerBlood = stats.m_Blood;
			m_PlayerProfileController.PlayerBloodValue = stats.m_Blood.ToString() + "%";
			m_PlayerProfileController.PlayerWater = stats.m_Water;
			m_PlayerProfileController.PlayerWaterValue = stats.m_Water.ToString() + "%";
			m_PlayerProfileController.PlayerEnergy = stats.m_Energy;
			m_PlayerProfileController.PlayerEnergyValue = stats.m_Energy.ToString() + "%";
			m_PlayerProfileController.PlayerStamina = stats.m_Stamina;
			m_PlayerProfileController.PlayerStaminaValue = stats.m_Stamina.ToString() + "%";

			array<string> player_properties = {"PlayerHealth", "PlayerHealthValue", "PlayerBlood", "PlayerBloodValue", "PlayerWater", "PlayerWaterValue", "PlayerEnergy", "PlayerEnergyValue", "PlayerStamina", "PlayerStaminaValue"};
			m_PlayerProfileController.NotifyPropertiesChanged(player_properties);
		}

		#ifdef EXPANSIONMODHARDLINE
		if (m_ShowHardlineStats)
		{
			m_PlayerProfileController.Hardline_Reputation = player.Expansion_GetReputation().ToString();
			m_PlayerProfileController.NotifyPropertyChanged("Hardline_Reputation");
		}
		#endif

		#ifdef EXPANSIONMODAI
		if (m_ShowPlayerFaction)
		{
			string factionName = "#STR_EXPANSION_NONE";
			eAIGroup group = player.GetGroup();
			if (group)
			{
				eAIFaction playerFaction = group.GetFaction();
				if (playerFaction)
					factionName = playerFaction.GetDisplayName();
			}
		
			m_PlayerProfileController.ProfilePlayerFaction = factionName;
			m_PlayerProfileController.NotifyPropertyChanged("ProfilePlayerFaction");
		}
		#endif

		UpdateUIElements();
	}
}