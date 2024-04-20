modded class MissionBase
{
    void MissionBase()
    {
		if (GetGame().IsServer())
		{
			GetIF_Config();
            IEIF_Metrics.ReportServerStarted();
		}
    }
}