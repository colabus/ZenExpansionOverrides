modded class ExpansionTraderNPCBase
{
	protected EffectSound m_VoicePowerOutZen;

	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        super.OnRPC(sender, rpc_type, ctx);

		if (GetGame().IsClient() && rpc_type == ZENEXPANSIONOVERRIDESRPC.POWEROUTAGE)
		{
			Param1<bool> client_receive_data = new Param1<bool>(false);
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

	void PlayPowerOutVoiceZen()
	{
		string voiceSoundSet = "Zen_PowerOut_" + GetType() + "_SoundSet";

		if (GetGame().ConfigIsExisting("CfgSoundSets " + voiceSoundSet))
		{
			GetZenExpansionAudioAIConfig().DebugMessage("[CLIENT] [" + GetType() + "] Playing soundset: " + voiceSoundSet + " @ " + GetPosition());
			m_VoicePowerOutZen = SEffectManager.PlaySoundOnObject(voiceSoundSet, this);
			if (m_VoicePowerOutZen)
			{
				m_VoicePowerOutZen.SetSoundAutodestroy(true);
				SetNpcTalkingClient(m_VoicePowerOutZen.ZenExpAI_GetAbstractWave().GetLength()); // from ZenExpansionAudioAI_Scripts
			}
		}
	}
}