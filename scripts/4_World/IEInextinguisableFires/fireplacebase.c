modded class FireplaceBase {

    protected ref Timer m_refuelTimer;

	override void DeferredInit() {
		super.DeferredInit();
		Print("HEre!");
		if(GetGame().IsServer())
		{
			IE_IF_Config conf = GetIF_Config();
			bool isfire = conf.IsFireAtPos(GetPosition());
			if (isfire) {
				CF_Log.Info("[IE_IF] Initializing inextinguisable fire @ " +  GetPosition());
				IE_IF_RefuelAndFire();
				if (!m_refuelTimer)
				{
					m_refuelTimer = new Timer();
					m_refuelTimer.Run(10, this, "IE_IF_RefuelAndFire", NULL, true);			
				}
			}
		}
	}
	
	void IE_IF_RefuelAndFire() {
		
		ItemBase firewood;
		if (!firewood)
			firewood = ItemBase.Cast(GetInventory().FindAttachmentByName("FireWood"));

		if (!firewood)
			firewood = ItemBase.Cast(GetInventory().CreateAttachment("FireWood"));

		if(firewood)
			firewood.SetQuantity(firewood.GetQuantityMax());
	
		if (!IsBurning()) {
			GetInventory().CreateAttachment("Paper");
			StartFire();
		}
		Synchronize();
	}
}