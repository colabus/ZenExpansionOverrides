modded class ExpansionVodnik
{
	// Vodnik keeps exploding due to coolant issues (or oil?) - just refill it, fuck it. Sick of support tickets.
	override void OnEngineStart()
	{
		super.OnEngineStart();

		#ifdef SERVER
		Fill(CarFluid.COOLANT, 6.0);
		Fill(CarFluid.OIL, 4.0);
		#endif
	}
}