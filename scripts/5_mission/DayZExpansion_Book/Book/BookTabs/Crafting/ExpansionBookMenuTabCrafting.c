modded class ExpansionBookMenuTabCrafting
{
	override void LoadCraftingCategories()
	{
		super.LoadCraftingCategories();


	}

	// For previewing different item to kit
	static string PREVIEW_ITEM_TYPE = "";

	override void SetResultsView(ExpansionBookCraftingItem item, ExpansionBookCraftingRecipe recipe)
	{
		if (item.Amount > 1)
			m_CraftingTabController.ItemName = item.Amount.ToString() + "x " + item.DisplayName;
		else
			m_CraftingTabController.ItemName = item.DisplayName;
		m_CraftingTabController.NotifyPropertyChanged("ItemName");
	
		m_SelectedRecipe = recipe;

		for (int i = 0; i < item.ClassNames.Count(); i++)
		{
			string classType = item.ClassNames[i];
			classType.ToLower();

			// Test just regular kit name
			if (classType.Contains("_kit"))
			{
				if (m_Object)
					GetGame().ObjectDelete(m_Object);

				classType.Replace("_kit", "");
				m_Object = EntityAI.Cast(GetGame().CreateObjectEx(classType, vector.Zero, ECE_LOCAL|ECE_NOLIFETIME));
				if (m_Object)
					break;
			}

			// If that didn't work, check for .cpp config
			string cfgPath = "CfgVehicles " + item.ClassNames[i] + " kitDisplay";
			if (GetGame().ConfigIsExisting(cfgPath))
			{
				if (m_Object)
					GetGame().ObjectDelete(m_Object);

				m_Object = EntityAI.Cast(GetGame().CreateObjectEx(GetGame().ConfigGetTextOut(cfgPath), vector.Zero, ECE_LOCAL|ECE_NOLIFETIME));
				if (m_Object)
					break;
			}

			if (m_Object)
				GetGame().ObjectDelete(m_Object);

			// If that didn't work, just create the object as it is
			m_Object = EntityAI.Cast(GetGame().CreateObjectEx(item.ClassNames[i], vector.Zero, ECE_LOCAL|ECE_NOLIFETIME));

			if (m_Object)
				break;
		}

		// Build any basebuilding objects
		BaseBuildingBase baseObject = BaseBuildingBase.Cast(m_Object);
		if (baseObject)
			baseObject.FullyBuild();
		
		//if (m_Object)
		//	PREVIEW_ITEM_TYPE = m_Object.GetType();

		m_CraftingTabController.ItemPreview = m_Object;
		m_CraftingTabController.NotifyPropertyChanged("ItemPreview");
		
		book_menu_content_left.Show(true);
		
		if (m_IngredientElementOne)
		{
			if (m_IngredientElementOne.IsSelected())
				m_IngredientElementOne.SetUnselected();
			
			m_IngredientElementOne = NULL;
		}
		
		if (m_IngredientOne)
			m_IngredientOne = NULL;
		
		if (m_IngredientElementTwo)
		{
			if (m_IngredientElementTwo.IsSelected())
				m_IngredientElementTwo.SetUnselected();
			
			m_IngredientElementTwo = NULL;
		}
		
		if (m_IngredientTwo)
			m_IngredientTwo = NULL;
	}
};
