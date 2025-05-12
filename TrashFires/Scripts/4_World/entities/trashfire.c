class TrashFire extends FireplaceBase {
	bool m_ContactEventProcessing;

	//Attachment types
	//Fuel
	typename ATTACHMENT_TRASHFUEL			= TrashFuel;


  override void EEInit() {
    super.EEInit();
    //m_FireConsumableTypes.Clear();
    m_FireConsumableTypes.Insert(ATTACHMENT_TRASHFUEL, 		new FireConsumableType(ATTACHMENT_TRASHFUEL, 30, false, "TrashFuel"));
  }

	override void OnIgnitedThis( EntityAI fire_source )
	{	
		//remove grass
		Object cc_object = GetGame().CreateObjectEx( OBJECT_CLUTTER_CUTTER , GetPosition(), ECE_PLACE_ON_SURFACE );
		cc_object.SetOrientation ( GetOrientation() );
		GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( DestroyClutterCutter, 200, false, cc_object );
		
		//start fire
		StartFire();
		
		if ( fire_source )
		{
			Man player = fire_source.GetHierarchyRootPlayer();
			
			if ( player )
			{
				EFireIgniteType ignate_type = EFireIgniteType.Unknow;
				
				if ( fire_source.ClassName() == "Matchbox"  )
				{
					ignate_type = EFireIgniteType.Matchbox;
				}
				else if ( fire_source.ClassName() == "Roadflare"  )
				{
					ignate_type = EFireIgniteType.Roadflare;
				}
				else if ( fire_source.ClassName() == "HandDrillKit"  )
				{
					ignate_type = EFireIgniteType.HandDrill;
				}
				
				
				SyncEvents.SendPlayerIgnatedFireplace( player, ignate_type );
			}
		}
	}

	override bool IsThisIgnitionSuccessful( EntityAI item_source = NULL )
	{
		SetIgniteFailure( false );
		Param1<bool> failure;
		
		//check kindling
		if ( !HasAnyKindling() )
		{
			return false;
		}
		
		//check roof
		if ( !IsOven() )
		{
			if ( !IsCeilingHighEnoughForSmoke() && IsOnInteriorSurface() )
			{
				return false;
			}
		}
		
		//check surface
		if ( IsOnWaterSurface() )
		{
			return false;
		}

		//check wetness
		if ( IsWet() )
		{
			SetIgniteFailure( true );
			
			failure = new Param1<bool>( GetIgniteFailure() );
			GetGame().RPCSingleParam( this, FirePlaceFailure.WET, failure, true );
			return false;
		}

		// check if the fireplace isnt below a roof
		//  excluding this check whein oven stage
		CheckForRoofLimited(0);
		if ( !IsOven() && !IsRoofAbove() )
		{
			// if not, check if there is strong rain or wind
			if ( IsRainingAbove() )
			{
				SetIgniteFailure( true );
				
				failure = new Param1<bool>( GetIgniteFailure() );
				GetGame().RPCSingleParam( this, FirePlaceFailure.WET, failure, true );
				return false;
			}
			
			if ( IsWindy() )
			{
				SetIgniteFailure( true );
				
				failure = new Param1<bool>( GetIgniteFailure() );
				GetGame().RPCSingleParam( this, FirePlaceFailure.WIND, failure, true );
				return false;
			}
		}
		
		return true;	
	}

		override bool CanIgniteItem( EntityAI ignite_target = NULL )
	{
		if ( IsBurning() )
		{
			return true;
		}
		
		return false;
	}
	
	override bool CanObstruct()
	{
		return IsOven();
	}
	
	override bool IsIgnited()
	{
		return IsBurning();
	}

	override bool CanReleaseAttachment(EntityAI attachment)
	{
		if (!super.CanReleaseAttachment(attachment))
		{
			return false;
		}
		
		ItemBase item = ItemBase.Cast(attachment);
		if (IsKindling(item) || IsFuel(item))
		{
			return !IsBurning();
		}
		
		return true;
	}

  override bool IsBaseFireplace()
	{
		return true;
	}

	override void EEItemAttached(EntityAI item, string slot_name)
	{
		super.EEItemAttached(item, slot_name);
		
		ItemBase item_base = ItemBase.Cast(item);
		
		if (IsKindling(item_base) || IsFuel(item_base))
		{
			AddToFireConsumables(item_base);
		}
		
		//cookware
		if (item_base.IsCookware())
			SetCookingEquipment(item_base);
		
		if (GetGame().IsServer() && !IsOven())
		{
			if (item_base.Type() == ATTACHMENT_COOKING_POT)
				item_base.SetAnimationPhase(ANIMATION_COOKWARE_HANDLE, 0);
			if (item.Type() == ATTACHMENT_CAULDRON)
				item_base.SetAnimationPhase(ANIMATION_CAULDRON_HANDLE, 0);
		}
		
		// direct cooking/smoking slots
		bool edible_base_attached = false;
		switch (slot_name)
		{
		case "DirectCookingA":
			m_DirectCookingSlots[0] = item_base;
			edible_base_attached = true;
		break;
		case "DirectCookingB":
			m_DirectCookingSlots[1] = item_base;
			edible_base_attached = true;
		break;
		case "DirectCookingC":
			m_DirectCookingSlots[2] = item_base;
			edible_base_attached = true;
		break;

		case "SmokingA":
			m_SmokingSlots[0] = item_base;
			edible_base_attached = true;
		break;
		case "SmokingB":
			m_SmokingSlots[1] = item_base;
			edible_base_attached = true;
		break;
		case "SmokingC":
			m_SmokingSlots[2] = item_base;
			edible_base_attached = true;
		break;
		case "SmokingD":
			m_SmokingSlots[3] = item_base;
			edible_base_attached = true;
		break;
		}
		
		//TODO
		//add SetViewIndex when attaching various attachments
		
		RefreshFireplaceVisuals();
	}

		override void EEItemDetached(EntityAI item, string slot_name)
	{
		super.EEItemDetached(item, slot_name);
		
		ItemBase item_base = ItemBase.Cast(item);
		
		if (IsKindling(item_base) || IsFuel(item_base))
		{
			RemoveFromFireConsumables(GetFireConsumableByItem(item_base));
		}

		//cookware
		if (item_base.IsCookware())
		{
			ClearCookingEquipment(item_base);
			item_base.RemoveAudioVisualsOnClient();
		}
		
		if (item_base.IsLiquidContainer()) //boiling bottle effects stop
			item_base.RemoveAudioVisualsOnClient();
		
		if (GetGame().IsServer())
		{
			if (item_base.Type() == ATTACHMENT_COOKING_POT)
				item_base.SetAnimationPhase(ANIMATION_COOKWARE_HANDLE, 1);
			if (item_base.Type() == ATTACHMENT_CAULDRON)
				item_base.SetAnimationPhase(ANIMATION_CAULDRON_HANDLE, 1);
		}
		
		// direct cooking/smoking slots
		switch (slot_name)
		{
		case "DirectCookingA":
			m_DirectCookingSlots[0] = null;
		break;
		case "DirectCookingB":
			m_DirectCookingSlots[1] = null;
		break;
		case "DirectCookingC":
			m_DirectCookingSlots[2] = null;
		break;

		case "SmokingA":
			m_SmokingSlots[0] = null;
		break;
		case "SmokingB":
			m_SmokingSlots[1] = null;
		break;
		case "SmokingC":
			m_SmokingSlots[2] = null;
		break;
		case "SmokingD":
			m_SmokingSlots[3] = null;
		break;
		}
		
		//no attachments left, no cargo items & no ashes are present
		CheckForDestroy();
		RefreshFireplaceVisuals();
	}
		override void RefreshPhysics()
	{
		super.RefreshPhysics();
		
		//Oven
		if ( IsOven() )
		{
			RemoveProxyPhysics( ANIMATION_OVEN );
			AddProxyPhysics( ANIMATION_OVEN );
		}
		else
		{
			RemoveProxyPhysics( ANIMATION_OVEN );
		}
		
		//Tripod
		if ( IsItemTypeAttached( ATTACHMENT_TRIPOD ) )
		{
			RemoveProxyPhysics( ANIMATION_TRIPOD );
			AddProxyPhysics( ANIMATION_TRIPOD );
		}
		else
		{
			RemoveProxyPhysics( ANIMATION_TRIPOD );
		}	
	}	
	
	override bool HasFlammableMaterial()
	{
		return true;
	}
	
	override void RefreshFireplacePhysics()
	{
		RefreshPhysics();
	}

	void DestroyClutterCutter( Object clutter_cutter )
	{
		GetGame().ObjectDelete( clutter_cutter );
	}

  	override void EOnTouch( IEntity other, int extra )
	{
		ContactEvent( other, GetPosition() );
	}
	
	override void EOnContact( IEntity other, Contact extra )
	{
		ContactEvent( other, extra.Position );
	}
	
	void ContactEvent( IEntity other, vector position )
	{		
		if ( GetGame().IsServer() && !m_ContactEventProcessing && dBodyIsActive(this) && !IsSetForDeletion() )
		{
			m_ContactEventProcessing = true;
			MiscGameplayFunctions.ThrowAllItemsInInventory(this, 0);
			CheckForDestroy();
			m_ContactEventProcessing = false;
		}
	}

	override void RefreshFireplaceVisuals()
	{
		super.RefreshFireplaceVisuals();
		
		if (GetGame().IsServer())
		{
			// fuel state
			if (IsItemTypeAttached(ATTACHMENT_TRASHFUEL))
				SetAnimationPhase(ANIMATION_ASHES, 0);
			else
				SetAnimationPhase(ANIMATION_ASHES, 1);
		}
	}

  static TrashFire IgniteEntityAsTrashfire( notnull EntityAI entity, notnull EntityAI fire_source )
	{
		//get player
		PlayerBase player = PlayerBase.Cast( fire_source.GetHierarchyRootPlayer() );
		
		//create TrashFire
		TrashFire trashFire = TrashFire.Cast( GetGame().CreateObjectEx( "TrashFire" , entity.GetPosition(), ECE_PLACE_ON_SURFACE ) );
		
		//attach
		if ( !GetGame().IsMultiplayer() )		//clear inventory reservation (single player)
		{
			InventoryLocation loc = new InventoryLocation;
			entity.GetInventory().GetCurrentInventoryLocation( loc );
			player.GetInventory().ClearInventoryReservationEx( entity, loc );
		}
		
		if ( GetGame().IsServer() && GetGame().IsMultiplayer() )
		{
			player.ServerTakeEntityToTargetAttachment( trashFire, entity ); // multiplayer server side
		}
		else
		{
			player.LocalTakeEntityToTargetAttachment( trashFire, entity ); // single player or multiplayer client side
		}
		
		//start fire
		trashFire.StartFire();
		trashFire.OnIgnitedThis(fire_source);
		
		return trashFire;
	}

	static bool CanIgniteEntityAsTrashfire(notnull EntityAI entity)
	{
		//check surface
		if (FireplaceBase.IsEntityOnWaterSurface(entity))
		{
			return false;
		}
		
		entity.CheckForRoofLimited(); //TODO: limit more severely? Should update at least once during UATimeSpent.FIREPLACE_IGNITE 
		if (!entity.IsRoofAbove())
			return !FireplaceBase.IsRainingAboveEntity(entity);
		
		//check ceiling (enough space for smoke)
		if (IsEntityOnInteriorSurface(entity) && MiscGameplayFunctions.IsUnderRoof(entity, FireplaceBase.MIN_CEILING_HEIGHT))
		{
			return false;
		}
		
		return true;
	}

}