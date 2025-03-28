modded class MissionBase
{
    int m_PlayerCountDB = 0;
    int m_PlayerCountActiveDB = 0;

    void MissionBase()
    {
        #ifdef SERVER
        GetRPCManager().AddRPC("RPC_ZXPO", "RPC_ReceiveExpansionBookPlayerCountRequest", this, SingeplayerExecutionType.Server);
        #else
        GetRPCManager().AddRPC("RPC_ZXPO", "RPC_ReceiveExpansionBookPlayerCountResponse", this, SingeplayerExecutionType.Client);
        GetRPCManager().AddRPC("RPC_ZXPO", "RPC_ReceiveDonationsData", this, SingeplayerExecutionType.Client);
        
        #endif
    }

    #ifdef SERVER
    void RPC_ReceiveExpansionBookPlayerCountRequest(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Server)
			return;

        Param1<bool> data;
        if (!ctx.Read(data))
            return;

		array<Man> players = new array<Man>;
		g_Game.GetWorld().GetPlayerList(players);
		GetRPCManager().SendRPC("RPC_ZXPO", "RPC_ReceiveExpansionBookPlayerCountResponse", new Param3<int, int, int>(players.Count(), GetSyberiaCharacters().GetTotalPlayerCount(), GetSyberiaCharacters().GetActivePlayerCount()), true, sender);
    }
    #endif

	void RPC_ReceiveExpansionBookPlayerCountResponse(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Client)
			return;

        Param3<int, int, int> data;
        if (!ctx.Read(data))
            return;

		ExpansionBookMenuTabServerInfo.CLIENTSIDE_PLAYER_COUNT = data.param1;
        ExpansionBookMenuTabServerInfo.CLIENTSIDE_PLAYER_COUNT_DB = data.param2;
        ExpansionBookMenuTabServerInfo.CLIENTSIDE_PLAYER_COUNT_ACTIVE_DB = data.param3;
    }

    void RPC_ReceiveDonationsData(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Client)
            return;

        Param1<ref array<ref SyberiaDonationRecord>> data;
        if (!ctx.Read(data))
            return;

        ExpansionBookMenu.DONATE_PLAYERS = "";
        
        float totalDonations = 0;
        for (int i = 0; i < data.param1.Count(); i++)
        {
            if (data.param1.Get(i).Name == "")
                continue;

            ExpansionBookMenu.DONATE_PLAYERS = ExpansionBookMenu.DONATE_PLAYERS + data.param1.Get(i).Name + " - $" + data.param1.Get(i).Amount;

            if (i != data.param1.Count() - 1)
                ExpansionBookMenu.DONATE_PLAYERS = ExpansionBookMenu.DONATE_PLAYERS + ", ";

            totalDonations += data.param1.Get(i).Amount;
        }

        ExpansionBookMenu.DONATE_DOLLARS = totalDonations;
    }
}