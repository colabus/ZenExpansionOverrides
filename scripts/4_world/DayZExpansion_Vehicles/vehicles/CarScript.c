modded class CarScript
{
	static const int LOCKED_TIME_SECS = 600; // 10 mins

	protected PlayerBase m_LastKnownDriver;
	protected string m_LastKnownDriverID;
	protected bool m_ZenTraderLocked = false;
	protected ref Timer m_UnlockTimer;

	void CarScript()
	{
		RegisterNetSyncVariableBool("m_ZenTraderLocked");
	}

	void ~CarScript()
	{
		if (m_UnlockTimer)
		{
			if (m_UnlockTimer.IsRunning())
				m_UnlockTimer.Stop();
		}
	}

	void ZenFillUpCarFluids()
	{
		FillUpCarFluids();
	}

	override bool CanReleaseAttachment(EntityAI attachment)
	{
		if (m_ZenTraderLocked)
			return false;

		return super.CanReleaseAttachment(attachment);
	}

	override bool CanReleaseCargo(EntityAI cargo)
	{
		if (m_ZenTraderLocked)
			return false;

		return super.CanReleaseCargo(cargo);
	}

	override bool CanSwapItemInCargo(EntityAI child_entity, EntityAI new_entity)
	{
		if (m_ZenTraderLocked)
			return false;

		return super.CanSwapItemInCargo(child_entity, new_entity);
	}

	/*override bool CanReceiveAttachment(EntityAI attachment, int slotId)
	{
		if (m_ZenTraderLocked)
			return false;

		return super.CanReceiveAttachment(attachment, slotId);
	}

	override bool CanReceiveItemIntoCargo(EntityAI item)
	{
		if (m_ZenTraderLocked)
			return false;

		return super.CanReceiveItemIntoCargo(item);
	}*/

	void SetTraderLocked(notnull PlayerBase player)
	{
		//GetInventory().LockInventory(LOCK_FROM_SCRIPT);

		m_LastKnownDriver = player;
		m_ZenTraderLocked = true;

		SetSynchDirty();
		SetLockTimer();

		if (m_LastKnownDriver.GetIdentity())
		{
			m_LastKnownDriverID = m_LastKnownDriver.GetCachedID();
			string notifyTxt = "Your vehicle has been locked for " + (LOCKED_TIME_SECS / 60) + " minutes. After this time anyone can enter driver seat or take items - so don't leave it unattended for too long!\n\nNote: If you close your doors/hood/etc then players cannot open them or enter your vehicle.";
			ExpansionNotification("VEHICLE LOCKED", notifyTxt).Error(player.GetIdentity());

			if (IsServerPVE())
				
				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(NotifySafeZoneFine, 8000, false, player);
		}
	}

	void NotifySafeZoneFine(PlayerBase player)
	{
		if (!player)
			return;

		string notifyTxt = "You've parked in a restricted area! You can leave your car here for 2 hours. After 2 hours you may receive a fine. The fine depends on how much loot is inside the car.\n\nIf the fine is not paid your car may be deleted. Please park away from the safezone if you plan to stay longer than 2 hours.";
		ExpansionNotification("PARKING METER", notifyTxt).Error(player.GetIdentity());
	}

	void SetLockTimer()
	{
		if (!m_UnlockTimer)
			m_UnlockTimer = new Timer();
		else
		if (m_UnlockTimer.IsRunning())
			m_UnlockTimer.Stop();

		m_UnlockTimer.Run(LOCKED_TIME_SECS, this, "UnlockTraderCar", NULL, false);
	}

	void UnlockTraderCar()
	{
		//GetInventory().UnlockInventory(LOCK_FROM_SCRIPT);

		if (m_UnlockTimer != NULL && m_UnlockTimer.IsRunning())
			m_UnlockTimer.Stop();

		m_ZenTraderLocked = false;
		SetSynchDirty();

		if (m_LastKnownDriver && m_LastKnownDriver.GetIdentity())
		{
			string notifyTxt = "Your vehicle has been unlocked! If you don't want it stolen, enter the driver's seat to re-lock it.";
			ExpansionNotification("VEHICLE UNLOCKED", notifyTxt).Error(m_LastKnownDriver.GetIdentity());
		}
	}

	bool IsTraderLocked(notnull PlayerBase player)
	{
		return m_ZenTraderLocked && (player != m_LastKnownDriver && player.GetCachedID() != m_LastKnownDriverID);
	}

	bool IsTraderLockedSyncCheck()
	{
		return m_ZenTraderLocked;
	}

	string GetLastKnownDriverID()
	{
		return m_LastKnownDriverID;
	}

	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionZenUnlockCar);
	}
}