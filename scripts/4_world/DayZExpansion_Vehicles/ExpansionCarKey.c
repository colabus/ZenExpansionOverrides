modded class ExpansionCarKey
{
	/*override bool DescriptionOverride(out string output)
	{
		string desc = "Used to lock and unlock helicopters. If I lose it I'll need to use a Propane Torch to reset the lock and keys.";
		if ( IsMaster() )
			output = "Uses Left: " + GetMasterUses().ToString() + " | " + desc;
		else
			output = desc;
		
		return true;
	}*/

	// For some reason ID D changes on some vehicles at restarts randomly... was affecting helis, but seems to affect vehicles too.
	override bool IsPairedTo(ExpansionVehicle vehicle )
	{
		int b1, b2, b3, b4;
		vehicle.GetMasterKeyPersistentID(b1, b2, b3, b4);

		if (m_MasterKeyPersistentIDA == 0 || b1 != m_MasterKeyPersistentIDA)
			return false;

		if (m_MasterKeyPersistentIDB == 0 || b2 != m_MasterKeyPersistentIDB)
			return false;

		if (m_MasterKeyPersistentIDC == 0 || b3 != m_MasterKeyPersistentIDC)
			return false;

		// This persistence check seems to break on some vehicles? Prevents unlocking cars?
		//if (m_MasterKeyPersistentIDD == 0 || b4 != m_MasterKeyPersistentIDD)
		//	return false;

		return true;
	}
}

/*string msg = "ExpansionCarKey::IsPairedTo: CAR/KEY";
		msg = msg + " " + vehicle.GetPersistentIDA() + "=" + m_PersistentIDA;
		msg = msg + " " + vehicle.GetPersistentIDB() + "=" + m_PersistentIDB;
		msg = msg + " " + vehicle.GetPersistentIDC() + "=" + m_PersistentIDC;
		msg = msg + " " + vehicle.GetPersistentIDD() + "=" + m_PersistentIDD;
		ZenFunctions.DebugMessage(msg);*/