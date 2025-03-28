class ExpansionCircuitBoard_Airdrop extends ItemBase
{
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionCallAirdropRadar);
	}
}