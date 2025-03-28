modded class ActionGetOutTransport
{
	override void OnStartServer(ActionData action_data)
	{
		super.OnStartServer(action_data);

		if (action_data.m_Player && action_data.m_Player.m_WasDriverOfCarZen)
		{
			HumanCommandVehicle vehCommand = action_data.m_Player.GetCommand_Vehicle();
			if (!vehCommand)
			{
				ZenFunctions.DebugMessage("NO CAR FOUND!");
				return;
			}

			Transport trans = vehCommand.GetTransport();
			//if (!trans || trans.GetType().Contains("bastard_"))
			//	return;

			if (vector.Distance(trans.GetPosition(), "5638.0 180.0 10607.0") > 80)
			{
				return;
			}

			CarScript car;
			if (Class.CastTo(car, trans))
			{
				car.SetTraderLocked(action_data.m_Player);
			}
		}

		action_data.m_Player.m_WasDriverOfCarZen = false;
	}
}