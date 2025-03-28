modded class Zen_ArtillerySmokeGrenade : M18SmokeGrenade_Red
{
	override void StartBombs()
	{
		if (vector.Distance(GetPosition(), "5647.100586 180.683914 10611.924805") < 300)
			return;

		super.StartBombs();
	}
}