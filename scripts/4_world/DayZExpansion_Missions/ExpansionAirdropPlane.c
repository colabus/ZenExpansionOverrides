modded class ExpansionAirdropPlane
{
	protected ExpansionPointLight m_ZenAidropLight;
	protected bool m_ZenHasDroppedLoad = false;

	void ExpansionAirdropPlane()
	{
		RegisterNetSyncVariableBool("m_ZenHasDroppedLoad");

		#ifndef SERVER
		UpdateLight();
		#endif
	}

	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		UpdateLight();
	}

	override ExpansionAirdropContainerBase CreateDrop(string container)
	{
		ExpansionAirdropContainerBase containerSpawn = super.CreateDrop(container);

		if (containerSpawn != NULL)
			ToggleZenAirdropLight();

		return containerSpawn;
	}

	//! SERVER
	void ToggleZenAirdropLight()
	{
		m_ZenHasDroppedLoad = true;
		SetSynchDirty();
	}

	//! CLIENT
	void UpdateLight()
	{
		if (!m_ZenAidropLight)
		{
			m_ZenAidropLight = CreateZenAirdropLight();
			m_ZenAidropLight.SetRadiusTo(10);
			m_ZenAidropLight.SetVisibleDuringDaylight(true);
			m_ZenAidropLight.AttachOnObject(this, "0 -5 0", "0 0 0"); // -5 is good, shows inside plane cargo hold
		}

		if (m_ZenAidropLight)
		{
			if (m_ZenHasDroppedLoad)
			{
				m_ZenAidropLight.SetDiffuseColor(0.1, 1, 0.1);
			}
			else
			{
				m_ZenAidropLight.SetDiffuseColor(1, 0.1, 0.1);
			}

			m_ZenAidropLight.SetBrightnessTo(10);
		}
	}

	ExpansionPointLight CreateZenAirdropLight()
	{
		return ExpansionPointLight.Cast(ScriptedLightBase.CreateLight(ExpansionPointLight));
	}

	//! RADIO NOTIFICATIONS
//	override void SetupPlane(vector dropPosition, string name, float maxRadius, float height, float speed, ExpansionLootContainer container, StringLocaliser warningProximityMsg = NULL, StringLocaliser airdropCreatedMsg = NULL, float containerLifeTime = 0.0)
//	{
//		super.SetupPlane(dropPosition, name, maxRadius, height, speed, container, warningProximityMsg, airdropCreatedMsg, containerLifeTime);
//
//		vector worldCenter = GetDayZGame().GetWorldCenterPosition();
//		string westEast;
//		string northSouth;
//
//		if (dropPosition[0] <= worldCenter[0])
//			westEast = "WEST";
//		else
//			westEast = "EAST";
//
//		if (dropPosition[2] <= worldCenter[2])
//			northSouth = "SOUTH";
//		else
//			northSouth = "NORTH";
//
//		string msg = "We've got a cargo plane in-bound to the " + northSouth + "-" + westEast + " quadrant to deliver a supply drop. Stand by for updates.";
//		ExpansionAirdropContainerBase.NotifyRadiosOfAirdropInbound(msg);
//	}
}