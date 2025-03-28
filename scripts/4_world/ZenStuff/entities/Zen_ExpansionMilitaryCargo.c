class Zen_ExpansionMilitaryCargo extends Container_Base
{
	static int CONTAMINATED_COUNT = 0;
	static int MILITARY_COUNT = 0;

	bool m_isInventoryBlocked = true;
	string m_lootType;

	void Zen_ExpansionMilitaryCargo()
	{
		RegisterNetSyncVariableBool("m_isInventoryBlocked");

		if (GetType().Contains("Contam"))
			CONTAMINATED_COUNT++;
		else
			MILITARY_COUNT++;
	}

	override void EEInit()
	{
		super.EEInit();

		SetHealth(GetMaxHealth());
		SetAllowDamage(false);
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(InitContainer, 1000, false);
	}

	void InitContainer()
	{
		if (GetGame().IsDedicatedServer())
		{
			if (GetType().Contains("Contam"))
				Print("[ZenCrates] ZenCrate CONTAMINATED spawned @ " + GetPosition() + " count=" + CONTAMINATED_COUNT);
			else
				Print("[ZenCrates] ZenCrate MILITARY spawned @ " + GetPosition() + " count=" + MILITARY_COUNT);
		}

		vector myPos = GetPosition();
		float surfaceY = GetGame().SurfaceY(myPos[0], myPos[2]);
		myPos[1] = surfaceY;

		SetPosition(myPos);

		if (!m_isInventoryBlocked)
			SetLifetime(1800);
		else
			SetLifetime(604800);
	}

	void SpawnLoot()
	{
		ExpansionLootContainer container;
		for (int i = 0; i < GetExpansionSettings().GetAirdrop().Containers.Count(); i++)
		{
			container = GetExpansionSettings().GetAirdrop().Containers[i];
			if (container.Container.Contains(m_lootType))
				break;
		}

		ExpansionLootSpawner.SpawnLoot(this, container.Loot, container.ItemCount);
	}

	override bool CanPutInCargo(EntityAI parent)
	{
		return false;
	}

	override bool CanPutIntoHands(EntityAI parent)
	{
		return false;
	}

	override bool CanReceiveItemIntoCargo(EntityAI item)
	{
		// Only allow putting loot inside when crate is unopened to prevent players using it as storage
		return super.CanReceiveItemIntoCargo(item) && m_isInventoryBlocked;
	}

	override bool CanDisplayCargo()
	{
		if (GetGame().IsClient())
		{
			return !m_isInventoryBlocked;
		}

		return super.CanDisplayCargo();
	}
	
	void UnlockInventory()
	{
		m_isInventoryBlocked = false;
		SetSynchDirty();
	}

	bool CanBreakOpen()
	{
		return m_isInventoryBlocked;
	}

	// For server restart persistence
	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);
		ctx.Write(m_isInventoryBlocked);
	}
	
	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		super.OnStoreLoad(ctx, version);

		if (!ctx.Read(m_isInventoryBlocked))
			return false;

		return true;
	}
}

class Zen_ExpansionMilitaryCargo_Contam extends Zen_ExpansionMilitaryCargo  
{
};