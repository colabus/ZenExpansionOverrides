/*class Armband_ZenYellowKing extends Armband_ColorBase
{
	void Armband_ZenYellowKing()
	{
		if (GetGame().IsDedicatedServer())
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(CheckIfWornOnAI, 500.0, false);
	}

	void CheckIfWornOnAI()
	{
		if (GetHierarchyRootPlayer())
		{
			PlayerBase pb = PlayerBase.Cast(GetHierarchyRootPlayer());
			if (pb && pb.IsAI())
				SetAllowDamage(false);
		}
	}
}*/

class Armband_DoubleZenYellowKing extends Armband_ColorBase 
{
	void Armband_ZenYellowKing()
	{
		if (GetGame().IsDedicatedServer())
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(CheckIfWornOnAI, 500.0, false);
	}

	void CheckIfWornOnAI()
	{
		if (GetHierarchyRootPlayer())
		{
			PlayerBase pb = PlayerBase.Cast(GetHierarchyRootPlayer());
			if (pb && pb.IsAI())
				SetAllowDamage(false);
		}
	}
};

modded class DarkMotoHelmet_YellowScarred
{
	void DarkMotoHelmet_YellowScarred()
	{
		if (GetGame().IsDedicatedServer())
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(CheckIfWornOnAI, 500.0, false);
	}

	void CheckIfWornOnAI()
	{
		if (GetHierarchyRootPlayer())
		{
			PlayerBase pb = PlayerBase.Cast(GetHierarchyRootPlayer());
			if (pb && pb.IsAI())
				SetAllowDamage(false);
		}
	}
}

class RidersJacket_ZenYellowKing extends RidersJacket_ColorBase {};
class M65Jacket_ZenYellowKing extends M65Jacket_ColorBase {};
class BomberJacket_ZenYellowKing extends BomberJacket_ColorBase {};
