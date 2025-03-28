modded class PlayerBase
{
	bool m_HasCompletedLightsOnQuest = false;

	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        super.OnRPC(sender, rpc_type, ctx);

		// Client receives data from server to tell it if the required quest is completed
		if (rpc_type == ZENEXPANSIONOVERRIDESRPC.OPEN_P2P_TRADER)
		{
			Param1<bool> client_receive_data = new Param1<bool>(false);
			if (!ctx.Read(client_receive_data))
				return;

			GetDayZGame().GetExpansionGame().GetExpansionUIManager().CreateSVMenu("ExpansionP2PMarketMenu");
		}
	}
}