modded class ExpansionP2PMarketTraderNPC
{
	protected EffectSound m_VoiceAudioZen;

	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        super.OnRPC(sender, rpc_type, ctx);

		Param1<bool> client_receive_data;
		if (GetGame().IsClient() && rpc_type == ZENEXPANSIONOVERRIDESRPC.POWEROUTAGE)
		{
			client_receive_data = new Param1<bool>(false);
			if (!ctx.Read(client_receive_data))
				return;

			if (client_receive_data.param1)
			{
				GetZenExpansionAudioAIConfig().DebugMessage("[CLIENT] [" + GetType() + "] Play Power Outage SoundSet");
				PlayPowerOutVoiceZen();
			}
		}
	}

	void ZenExpansionAudio_TriggerPowerOutVoice(PlayerIdentity id)
	{
		Param1<bool> server_send_data = new Param1<bool>(true);
		RPCSingleParam(ZENEXPANSIONOVERRIDESRPC.POWEROUTAGE, server_send_data, true, id);
	}

	override void PlayVoiceAudioZen(ZENTRADERAUDIO type)
	{
		string voiceSoundSet;

		if (type == ZENTRADERAUDIO.QUESTREQ)
			voiceSoundSet = "Zen_" + GetType() + "_QuestRequired_SoundSet";

		if (!GetGame().ConfigIsExisting("CfgSoundSets " + voiceSoundSet))
		{
			GetZenExpansionAudioAIConfig().DebugMessage("[CLIENT] [" + GetType() + "] Soundset " + voiceSoundSet + " not found. Checking for generic soundset: " + GetType() + " @ " + GetPosition());

			// Scan generic NPC config types
			bool useGenericVoice = false;
			string checkType = GetType();
			checkType.ToLower();

			foreach (string s : GetZenExpansionAudioAIConfig().GenericAudioTypes)
			{
				if (checkType.Contains(s))
				{
					useGenericVoice = true;
					break;
				}
			}

			// If type is not found, don't play generic voice hello
			if (!useGenericVoice)
				return;

			if (IsMale())
			{
				if (type == ZENTRADERAUDIO.QUESTREQ)
					voiceSoundSet = "Zen_ExpansionTraderGenericMale_QuestRequired_SoundSet";
			}
			else
			{
				if (type == ZENTRADERAUDIO.QUESTREQ)
					voiceSoundSet = "Zen_ExpansionTraderGenericFemale_QuestRequired_SoundSet";
			}
		}

		GetZenExpansionAudioAIConfig().DebugMessage("[CLIENT] [" + GetType() + "] Playing soundset: " + voiceSoundSet + " @ " + GetPosition());
		m_VoiceAudioZen = SEffectManager.PlaySoundOnObject(voiceSoundSet, this);
		if (m_VoiceAudioZen)
			m_VoiceAudioZen.SetSoundAutodestroy(true);
	}

	void PlayPowerOutVoiceZen()
	{
		string voiceSoundSet = "Zen_PowerOut_" + GetType() + "_SoundSet";

		if (GetGame().ConfigIsExisting("CfgSoundSets " + voiceSoundSet))
		{
			GetZenExpansionAudioAIConfig().DebugMessage("[CLIENT] [" + GetType() + "] Playing soundset: " + voiceSoundSet + " @ " + GetPosition());
			m_VoiceAudioZen = SEffectManager.PlaySoundOnObject(voiceSoundSet, this);
			if (m_VoiceAudioZen)
				m_VoiceAudioZen.SetSoundAutodestroy(true);
		}
	}
}