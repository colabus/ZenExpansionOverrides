modded class ExpansionP2PMarketMenuListHeader
{
	override void OnShow()
	{
		super.OnShow();
		price_icon.LoadImageFile(0, "DayZExpansion/Core/GUI/icons/misc/T_Nails_256x256.edds");
	}
};

modded class ExpansionP2PMarketMenuListing
{
	override void OnShow()
	{
		super.OnShow();
		price_icon.LoadImageFile(0, "DayZExpansion/Core/GUI/icons/misc/T_Nails_256x256.edds");
	}

	override void SetIsOwnedItem()
	{
		super.SetIsOwnedItem();
		price_icon.LoadImageFile(0, "DayZExpansion/Core/GUI/icons/misc/T_Nails_256x256.edds");
	}
	
	override void SetIsSoldItem()
	{
		super.SetIsSoldItem();
		price_icon.LoadImageFile(0, "DayZExpansion/Core/GUI/icons/misc/T_Nails_256x256.edds");
	}
};