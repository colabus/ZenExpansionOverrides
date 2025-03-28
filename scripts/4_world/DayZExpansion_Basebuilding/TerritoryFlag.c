modded class TerritoryFlag
{
	ref Timer m_UpdateObjectCountTimer;
	int m_CurrentObjectCount = 0;
	int m_CurrentCargoItemCount = 0;
	bool m_LoggedItemCount = false;

	void TerritoryFlag()
	{
		RegisterNetSyncVariableInt("m_CurrentObjectCount");
		RegisterNetSyncVariableInt("m_CurrentCargoItemCount");
	}

	override void EEInit()
	{
		super.EEInit();

		if (GetGame().IsDedicatedServer())
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.ScanObjectsLog, 5000, false);

			if (!m_UpdateObjectCountTimer)
				m_UpdateObjectCountTimer = new Timer();

			// Randomize timer slightly so we don't have all the flags scanning a shitload of base objects all at once
			m_UpdateObjectCountTimer.Run(3600 + Math.RandomIntInclusive(-600, 600), this, "ScanObjectsLog", NULL, false);
		}
	}

	bool CanBuildMore()
	{
		return m_CurrentObjectCount < ZenExtraExpansionConfig.MaxBasebuildingObjects && m_CurrentCargoItemCount < ZenExtraExpansionConfig.MaxCargoItems;
	}

	override string GetDisplayName()
	{
		if (m_RefresherActive)
		{
			return m_CurrentObjectCount.ToString() + "/" + ZenExtraExpansionConfig.MaxBasebuildingObjects.ToString() + " Objects | " + m_CurrentCargoItemCount.ToString() + "/" + ZenExtraExpansionConfig.MaxCargoItems.ToString() + " Cargo";
		}

		return super.GetDisplayName();
	}

	/*override bool DescriptionOverride(out string output)
	{
		if (!m_RefresherActive)
			return false;


		output = "";

		return true;
	}*/

	private void ScanObjectsLog()
	{
		array<Object> objectsNearFlag = new array<Object>;
		GetGame().GetObjectsAtPosition3D(GetPosition(), GetExpansionSettings().GetTerritory().TerritorySize + 1, objectsNearFlag, NULL);

		int i;
		Object obj;
		m_CurrentObjectCount = 0;
		m_CurrentCargoItemCount = 0;
		EntityAI entity;

		for (i = 0; i < objectsNearFlag.Count(); i++)
		{
			obj = objectsNearFlag.Get(i);

			if (obj == this || obj.IsInherited(TerritoryFlag))
				continue;

			entity = EntityAI.Cast(obj);
			if (entity && entity.IsRefresherSignalingViable())
			{
				m_CurrentObjectCount++;

				CargoBase cargo = entity.GetInventory().GetCargo();
				if (cargo)
				{
					m_CurrentCargoItemCount += cargo.GetItemCount();
				}
			}
		}

		SetSynchDirty();

		if (!m_LoggedItemCount)
		{
			ZenModLogger.Log("TERRITORY @ <" + GetPosition()[0] + " " + GetPosition()[2] + "> CONTAINS " + m_CurrentObjectCount + "/" + ZenExtraExpansionConfig.MaxBasebuildingObjects + " OBJECTS AND " + m_CurrentCargoItemCount + "/" + ZenExtraExpansionConfig.MaxCargoItems + " CARGO ITEMS - CANBUILD=" + CanBuildMore(), "basebuild");
			m_LoggedItemCount = true;
		}
	}

	override bool CanReleaseAttachment(EntityAI attachment)
	{
		if (GetGame().IsClient())
		{
			PlayerBase pb = PlayerBase.Cast(GetGame().GetPlayer());
			if (!pb)
				return false;

			if (attachment.IsInherited(Flag_Base))
			{
				return !pb.IsInTerritory() || pb.IsInsideOwnTerritory();
			}
		}

		return super.CanReleaseAttachment(attachment);
	}
}