modded class BaseBuildingBase
{
	// Stop kit from spawn in weird places when building Expansion stuff
	override void OnPartBuiltServer(notnull Man player, string part_name, int action_id)
	{
		if (!IsInherited(ExpansionBaseBuilding))
		{
			super.OnPartBuiltServer(player, part_name, action_id);
			return;
		}

		ConstructionPart construtionPart = GetConstruction().GetConstructionPart(part_name);
		
		//check base state
		if (construtionPart.IsBase())
		{
			SetBaseState(true);

			//spawn kit
			ItemBase kit = CreateConstructionKit();
			if (kit)
			{
				kit.SetPosition(player.GetPosition() + "0 0.25 0");
			}
		}
			
		//register constructed parts for synchronization
		RegisterPartForSync(construtionPart.GetId());
		
		//register action that was performed on part
		RegisterActionForSync(construtionPart.GetId(), action_id);
		
		//synchronize
		SynchronizeBaseState();

		SetPartFromSyncData(construtionPart); // server part of sync, client will be synced from SetPartsFromSyncData
		
		UpdateNavmesh();
		
		//update visuals
		UpdateVisuals();
		
		//reset action sync data
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(ResetActionSyncData, 100, false, this);
	}

	override ItemBase FoldBaseBuildingObject()
	{
		if (!IsInherited(ExpansionBaseBuilding))
		{
			return super.FoldBaseBuildingObject();
		}

		ItemBase item = CreateConstructionKit();
		DestroyConstruction();

		// Raise item slightly for Expansion stuff
		if (item)
			item.SetPosition(item.GetPosition() + "0 0.25 0");

		return item;
	}
}