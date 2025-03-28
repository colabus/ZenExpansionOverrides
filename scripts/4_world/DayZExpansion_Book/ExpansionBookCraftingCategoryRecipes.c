modded class ExpansionBookCraftingCategoryRecipes : ExpansionBookCraftingCategory
{
	override ExpansionBookCraftingRecipe AddRecipe(RecipeBase recipeBase)
	{
		if (recipeBase.m_Name.Contains("Dismantle") || recipeBase.m_Name.Contains("dismantle"))
			return NULL;

		return super.AddRecipe(recipeBase);
	}
};