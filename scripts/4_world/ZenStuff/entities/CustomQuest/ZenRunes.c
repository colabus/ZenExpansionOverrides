modded class FieldShovel
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionBuryZenRunes);
	}
};

modded class Shovel
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionBuryZenRunes);
	}
};

modded class Pickaxe
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionBuryZenRunes);
	}
};

modded class FarmingHoe
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionBuryZenRunes);
	}
};

modded class Iceaxe
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionBuryZenRunes);
	}
};

modded class ZenRune_Base
{
	vector BuryLocation()
	{
		return "-1000 -1000 -1000";
	}
};

modded class ZenRune_Air
{
	// NE
	override vector BuryLocation()
	{
		return "12207.799805 254.336899 12330.500000";
	}
};

modded class ZenRune_Earth
{
	// SW
	override vector BuryLocation()
	{
		return "785.658752 524.754333 483.930267";
	}
};

modded class ZenRune_Fire
{
	// SE
	override vector BuryLocation()
	{
		return "12353.700195 297.548431 390.208008";
	}
};

modded class ZenRune_Water
{
	// NW
	override vector BuryLocation()
	{
		return "401.726990 406.962006 12325.200195";
	}
};