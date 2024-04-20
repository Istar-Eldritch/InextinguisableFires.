modded class FireplaceBase
{

	protected ref Timer m_refuelTimer;

	override void DeferredInit()
	{
		super.DeferredInit();
		if (GetGame().IsServer())
		{
			IE_IF_Config conf = GetIF_Config();
			bool isfire = conf.IsFireAtPos(GetPosition());
			if (isfire)
			{
				IEIF_LOG.Info("Initializing inextinguisable fire @ " + GetPosition());
				IEIF_RefuelAndFire();
				if (!m_refuelTimer)
				{
					m_refuelTimer = new Timer();
					m_refuelTimer.Run(60, this, "IEIF_RefuelAndFire", NULL, true);
				}
			}
		}
	}

	void IEIF_RefuelAndFire()
	{
		IEIF_LOG.Debug("Refueling fire at @ " + GetPosition());
		ItemBase firewood = ItemBase.Cast(GetInventory().FindAttachmentByName("FireWood"));

		if (firewood == null)
			firewood = ItemBase.Cast(GetInventory().CreateInInventory("FireWood"));

		if (firewood != null)
			firewood.SetQuantity(firewood.GetQuantityMax());

		ItemBase paper = ItemBase.Cast(GetInventory().FindAttachmentByName("Paper"));
		if (paper == null)
			paper = ItemBase.Cast(GetInventory().CreateInInventory("Paper"));
	
		if (paper != null)
			paper.SetQuantity(paper.GetQuantityMax());

		StartFire();
		Synchronize();
	}
}

modded class BarrelHoles_ColorBase
{
	override void IEIF_RefuelAndFire()
	{
		m_Openable.Open();
		super.IEIF_RefuelAndFire();
		m_Openable.Close();
	}
}