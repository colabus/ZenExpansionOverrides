modded class ExpansionBookMenuTabCraftingIngredient: ExpansionScriptView
{
	// Fix for ingredients that don't have a 3D object (eg. Barrel_ColorBase)
	override void SetView()
	{
		super.SetView();

		// Check if preview object was created ok
		if (m_Object)
			return;

		// If it wasn't created, check for .cpp config
		int i;
		for (i = 0; i < m_Item.ClassNames.Count(); i++)
		{
			// Try generic "red" type first
			string testObject = m_Item.ClassNames[i];
			testObject.ToLower();
			testObject.Replace("_colorbase", "_red");
			m_Object = EntityAI.Cast(GetGame().CreateObjectEx(testObject, vector.Zero, ECE_LOCAL|ECE_NOLIFETIME));
			if (m_Object)
				break;

			// Still no object found - check .cpp config
			string cfgPath = "CfgVehicles " + m_Item.ClassNames[i] + " kitDisplay";
			if (GetGame().ConfigIsExisting(cfgPath))
			{
				m_Object = EntityAI.Cast(GetGame().CreateObjectEx(GetGame().ConfigGetTextOut(cfgPath), vector.Zero, ECE_LOCAL|ECE_NOLIFETIME));
				if (m_Object)
					break;
			}
		}

		if (!m_Object && m_Item.ClassNames[i] != "")
		{
			ZenFunctions.ZenClientError("FAILED TO DISPLAY 3D CRAFTING INGREDIENT: " + m_Item.ClassNames[i] + " - tell Zenarchist he fucked up!");
			return;
		}
				
		m_IngredientController.ItemPreview = m_Object;
		m_IngredientController.NotifyPropertyChanged("ItemPreview");
	}
};