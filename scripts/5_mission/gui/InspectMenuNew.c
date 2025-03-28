modded class InspectMenuNew extends UIScriptedMenu
{
	//! Unfortunately because these are static functions that can't call super() this complicated workaround is the only way to not break future vanilla changes
	static void ZenMilkUpdateItemInfo(Widget root_widget, EntityAI item)
	{
		if (!root_widget || !item) return;

		UpdateItemInfo(root_widget, item);
		WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "MILK", Colors.COLOR_LIQUID);
	}
}