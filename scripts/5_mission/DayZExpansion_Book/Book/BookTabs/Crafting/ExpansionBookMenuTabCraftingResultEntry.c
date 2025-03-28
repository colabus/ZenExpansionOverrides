modded class ExpansionBookMenuTabCraftingResultEntry: ExpansionScriptView
{
	static ref ExpansionTooltipServerSettingEntry m_Tooltip;

	override void OnResultEntryButtonClick()
	{
		super.OnResultEntryButtonClick();

		if (m_Tooltip)
			m_Tooltip.Destroy();
	};

	override bool OnMouseEnter(Widget w, int x, int y)
	{
		switch (w)
		{
		case result_entry_button:
			UpdateTooltip();
			break;
		}
		
		return super.OnMouseEnter(w, x, y);;
	}
	
	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		switch (w)
		{
		case result_entry_button:
			if (m_Tooltip)
				m_Tooltip.Destroy();
			break;
		}
		
		return super.OnMouseLeave(w, enterW, x, y);
	}

	void UpdateTooltip()
	{
		if (!m_Item)
			return;

		string className = "";
		int i;

		for (i = 0; i < m_Item.ClassNames.Count(); i++)
		{
			string classType = m_Item.ClassNames[i];
			classType.ToLower();

			// Test just regular kit name
			if (classType.Contains("_kit"))
			{
				classType.Replace("_kit", "");
				string cfgPath = "CfgVehicles " + classType;
				if (GetGame().ConfigIsExisting(cfgPath))
				{
					className = classType;
					break;
				}
				else
				{
					cfgPath = "CfgWeapons " + classType;
					if (GetGame().ConfigIsExisting(cfgPath))
					{
						className = classType;
						break;
					}
				}
			}

			// If that didn't work, check for .cpp config
			cfgPath = "CfgVehicles " + m_Item.ClassNames[i] + " kitDisplay";
			if (GetGame().ConfigIsExisting(cfgPath))
			{
				className = GetGame().ConfigGetTextOut(cfgPath);
				break;
			}

			// If that didn't work, just create the object as it is
			cfgPath = "CfgVehicles " + classType;
			if (GetGame().ConfigIsExisting(cfgPath))
			{
				className = classType;
				break;
			}

			cfgPath = "CfgWeapons " + classType;
			if (GetGame().ConfigIsExisting(cfgPath))
			{
				className = classType;
				break;
			}
		}

		ExpansionBookMenuTabCrafting.PREVIEW_ITEM_TYPE = className; // todo: replace this

		if (ExpansionBookMenuTabCrafting.PREVIEW_ITEM_TYPE == "")
			return;

		m_Tooltip = new ExpansionTooltipServerSettingEntry("", "");
		ExpansionTooltipServerSettingEntryController controller = ExpansionTooltipServerSettingEntryController.Cast(m_Tooltip.GetController());

		if (controller)
		{
			string displayName = "";
			string description = "";
			string tooltip = "";
			string storageSlots = "Storage Slots: ";
			string attachmentSlots = "Attachments: ";

			cfgPath = "CfgVehicles " + ExpansionBookMenuTabCrafting.PREVIEW_ITEM_TYPE + " displayName";
			if (!GetGame().ConfigIsExisting(cfgPath))
			{
				cfgPath = "CfgWeapons " + ExpansionBookMenuTabCrafting.PREVIEW_ITEM_TYPE + " displayName";
			}

			if (GetGame().ConfigIsExisting(cfgPath))
			{
				displayName = GetGame().ConfigGetTextOut(cfgPath);
			}
			else
			{
				m_Tooltip.Destroy();
				return;
			}

			cfgPath = "CfgVehicles " + ExpansionBookMenuTabCrafting.PREVIEW_ITEM_TYPE + " descriptionShort";
			if (!GetGame().ConfigIsExisting(cfgPath))
			{
				cfgPath = "CfgWeapons " + ExpansionBookMenuTabCrafting.PREVIEW_ITEM_TYPE + " descriptionShort";
			}

			if (GetGame().ConfigIsExisting(cfgPath))
			{
				description = GetGame().ConfigGetTextOut(cfgPath);
			}

			cfgPath = "CfgVehicles " + ExpansionBookMenuTabCrafting.PREVIEW_ITEM_TYPE + " Cargo itemsCargoSize";
			if (!GetGame().ConfigIsExisting(cfgPath))
			{
				cfgPath = "CfgVehicles " + ExpansionBookMenuTabCrafting.PREVIEW_ITEM_TYPE + " itemsCargoSize";
			}

			if (GetGame().ConfigIsExisting(cfgPath))
			{
				TIntArray cargoArray = new TIntArray;
				GetGame().ConfigGetIntArray(cfgPath, cargoArray);

				if (cargoArray && cargoArray.Count() == 2)
				{
					storageSlots = storageSlots + (cargoArray.Get(0) * cargoArray.Get(1)).ToString();
				}
			}

			cfgPath = "CfgVehicles " + ExpansionBookMenuTabCrafting.PREVIEW_ITEM_TYPE + " attachments";
			if (!GetGame().ConfigIsExisting(cfgPath))
			{
				cfgPath = "CfgWeapons " + ExpansionBookMenuTabCrafting.PREVIEW_ITEM_TYPE + " attachments";
			}

			if (GetGame().ConfigIsExisting(cfgPath))
			{
				TStringArray attachmentArray = new TStringArray;
				GetGame().ConfigGetTextArray(cfgPath, attachmentArray);

				if (attachmentArray && attachmentArray.Count() > 0)
				{
					string appendSlots = "";
					string slotConfigName;
					string slotDisplayName;
					for (i = 0; i < attachmentArray.Count(); i++)
					{
						slotConfigName = attachmentArray.Get(i);
						int slot_id = InventorySlots.GetSlotIdFromString(slotConfigName);
						slotDisplayName = InventorySlots.GetSlotDisplayName(slot_id);

						if (slotDisplayName == "")
							continue;

						appendSlots = appendSlots + slotDisplayName;
						if (i < attachmentArray.Count() - 1)
							appendSlots = appendSlots + ", ";
						else
							appendSlots = appendSlots + ".";
					}

					attachmentSlots = attachmentSlots + appendSlots;
				}
			}

			// Set tooltip text
			if (storageSlots == "Storage Slots: ")
				storageSlots = "Storage Slots: None";

			if (attachmentSlots == "Attachments: ")
				attachmentSlots = "Attachments: None";

			tooltip = description + "\n\n" + storageSlots + " | " + attachmentSlots;

			// Update title label
			m_Tooltip.m_Title = displayName;
			controller.TooltipTitle = displayName;
			controller.NotifyPropertyChanged("TooltipTitle");

			// Update description label
			m_Tooltip.m_Text = tooltip;
			controller.TooltipText = tooltip;
			controller.NotifyPropertyChanged("TooltipText");
		}

		m_Tooltip.TooltipText.Update();
	}
};