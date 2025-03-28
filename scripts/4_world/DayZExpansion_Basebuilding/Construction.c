modded class Construction
{
	override void DismantlePartServer( notnull Man player, string part_name, int action_id )
	{
		super.DismantlePartServer(player, part_name, action_id);

		string playerDesc = Expansion_GetPlayerDesc(PlayerBase.Cast(player));
		GetExpansionSettings().GetLog().PrintLog("[BaseRaiding] " + part_name + " dismantled by " + playerDesc);
	}

	string Expansion_GetPlayerDesc(PlayerBase player)
	{
		string playerId;
		string playerName;
		string playerDesc;

		if ( player )
		{
			playerId = player.GetIdentityUID();
			playerName = player.GetIdentityName();
			playerDesc = "player \"" + playerName + "\" (ID = \"" + playerId + "\" at " + player.GetPosition() + ")";

			ItemBase itemInHands = player.GetItemInHands();
			if (itemInHands)
				playerDesc = playerDesc + " (Using item in hands=" + itemInHands.GetType() + ")";
			else
				playerDesc = playerDesc + " (Using no item in hands?)";
		}

		return playerDesc;
	}
}