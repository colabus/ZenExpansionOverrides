modded class PluginRecipesManagerBase extends PluginBase
{	
	override void RegisterRecipies()
	{
		super.RegisterRecipies();
		RegisterRecipe(new CraftArmband_ZenLoneWolf);
		RegisterRecipe(new CraftArmband_ZenLoneWolfBlack);
	}
}