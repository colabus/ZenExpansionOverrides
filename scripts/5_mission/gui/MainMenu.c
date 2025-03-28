modded class MainMenu
{
	protected Widget m_Mute;
	protected ImageWidget m_MuteImg;

	// TODO: Find a better way.
	override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets("ZenExpansionOverrides/data/gui/layouts/main_menu.layout");

		// Custom:
		m_Mute = layoutRoot.FindAnyWidget("mute_button");

		m_MuteImg = ImageWidget.Cast(layoutRoot.FindAnyWidget("mute_button_image"));

		if (GetHardcoreDayZClientConfig().MusicMuted)
			m_MuteImg.LoadImageFile(0, "ZenExpansionOverrides/data/gui/unmute.edds");
		else
			m_MuteImg.LoadImageFile(0, "ZenExpansionOverrides/data/gui/mute.edds");

		// Vanilla:
		
		m_Play						= layoutRoot.FindAnyWidget("play");
		m_ChooseServer				= layoutRoot.FindAnyWidget("choose_server");
		m_CustomizeCharacter		= layoutRoot.FindAnyWidget("customize_character");
		m_PlayVideo					= layoutRoot.FindAnyWidget("play_video");
		m_Tutorials					= layoutRoot.FindAnyWidget("tutorials");
		m_TutorialButton			= layoutRoot.FindAnyWidget("tutorial_button");
		m_MessageButton				= layoutRoot.FindAnyWidget("message_button");
		m_SettingsButton			= layoutRoot.FindAnyWidget("settings_button");
		m_Exit						= layoutRoot.FindAnyWidget("exit_button");
		m_PrevCharacter				= layoutRoot.FindAnyWidget("prev_character");
		m_NextCharacter				= layoutRoot.FindAnyWidget("next_character");

		m_DlcFrame 					= layoutRoot.FindAnyWidget("dlc_Frame");
		m_Version					= TextWidget.Cast(layoutRoot.FindAnyWidget("version"));
		m_ModdedWarning				= TextWidget.Cast(layoutRoot.FindAnyWidget("ModdedWarning"));
		m_CharacterRotationFrame	= layoutRoot.FindAnyWidget("character_rotation_frame");
		
		m_LastPlayedTooltip			= layoutRoot.FindAnyWidget("last_server_info");
		m_LastPlayedTooltip.Show(false);
		m_LastPlayedTooltipLabel	= m_LastPlayedTooltip.FindAnyWidget("last_server_info_label");
		m_LastPlayedTooltipName 	= TextWidget.Cast(m_LastPlayedTooltip.FindAnyWidget("last_server_info_name"));
		m_LastPlayedTooltipIP		= TextWidget.Cast(m_LastPlayedTooltip.FindAnyWidget("last_server_info_ip"));
		m_LastPlayedTooltipPort		= TextWidget.Cast(m_LastPlayedTooltip.FindAnyWidget("last_server_info_port"));
		
		m_LastPlayedTooltipTimer	= new WidgetFadeTimer();
		
		m_Stats						= new MainMenuStats(layoutRoot.FindAnyWidget("character_stats_root"));
		
		m_Mission					= MissionMainMenu.Cast(GetGame().GetMission());
		
		m_LastFocusedButton 		= m_Play;

		m_ScenePC					= m_Mission.GetIntroScenePC();
		
		if (m_ScenePC)
		{
			m_ScenePC.ResetIntroCamera();
		}
		
		m_PlayVideo.Show(false);
		
		m_PlayerName				= TextWidget.Cast(layoutRoot.FindAnyWidget("character_name_text"));
		
		// Set Version
		string version;
		GetGame().GetVersion(version);
		m_Version.SetText("#main_menu_version" + " " + version);
		
		GetGame().GetUIManager().ScreenFadeOut(0);

		SetFocus(null);
		
		Refresh();
		
		LoadMods();
		PopulateDlcFrame();
		
		GetDayZGame().GetBacklit().MainMenu_OnShow();
		GetGame().GetMission().GetOnModMenuVisibilityChanged().Insert(ShowDlcFrame);
	
		g_Game.SetLoadState(DayZLoadState.MAIN_MENU_CONTROLLER_SELECT);
		
		return layoutRoot;
	}

	override bool OnClick(Widget w, int x, int y, int button)
	{
		if (w == m_Mute)
		{
			if (GetHardcoreDayZClientConfig().MusicMuted)
			{
				m_MuteImg.LoadImageFile(0, "ZenExpansionOverrides/data/gui/mute.edds");
				GetHardcoreDayZClientConfig().MusicMuted = false;
			}
			else
			{
				m_MuteImg.LoadImageFile(0, "ZenExpansionOverrides/data/gui/unmute.edds");
				GetHardcoreDayZClientConfig().MusicMuted = true;
				MuteMusic();
			}

			GetHardcoreDayZClientConfig().Save();
			return true;
		}

		return super.OnClick(w, x, y, button);
	}

	void MuteMusic()
	{
		if (DayZIntroScenePC.m_GuitarSong)
		{
			DayZIntroScenePC.m_GuitarSong.Stop();
		}
	}
}