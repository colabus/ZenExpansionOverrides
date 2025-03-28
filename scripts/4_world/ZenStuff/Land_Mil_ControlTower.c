modded class Land_Mil_ControlTower
{
	void Land_Mil_ControlTower()
	{
		if (GetGame().IsDedicatedServer())
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(SpawnMapProxy, 5000.0, false);
	}

	void SpawnMapProxy()
	{
		vector objPosOffset = "0.7 3.2 0";
		vector worldPos = ModelToWorld(objPosOffset);

		Object mapObj = GetGame().CreateObjectEx("Zen_BldrStaticMap", GetPosition(), ECE_KEEPHEIGHT);
		mapObj.SetOrientation(GetOrientation() + "90 0 0");
		mapObj.SetPosition(worldPos);
		mapObj.SetScale(0.5);
	}
}