class TrashFuel extends ItemBase {
  override bool HasFlammableMaterial()
	{
		return true;
	}

  override bool CanBeIgnitedBy( EntityAI igniter = NULL )
	{
		if ( GetHierarchyParent() ) return false;
		
		return true;
	}	
  
  override void OnIgnitedTarget( EntityAI target_item )
	{
	}
	
	override void OnIgnitedThis( EntityAI fire_source )
	{
		TrashFire.IgniteEntityAsTrashfire( this, fire_source );
	}

	override bool IsThisIgnitionSuccessful( EntityAI item_source = NULL )
	{
		return TrashFire.CanIgniteEntityAsTrashfire( this );
	}	

	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionAttach);
		AddAction(ActionDetach);
	}
}