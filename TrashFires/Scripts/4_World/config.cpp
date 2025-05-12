class CfgPatches
{
	class FirstMod
	{
		requiredAddons[] =
		{
			// ""
		};
	};
};

class CfgMods
{
	class FirstMod
	{
		type = "mod";

		class defs
		{
			class worldScriptModule
			{
				value = "";
				files[] = { "FirstMod/Scripts/4_World" };
			};
		};
	};
};

class CfgSlots {
	class Slot_TrashFuel
	{
		name="TrashFuel";
		displayName="Trash Fuel";
		ghostIcon="set:trash_icon image:trash_icon";
		stackMax=15;
	};
}

class CfgVehicles 
{
	class FireplaceBase;
	class Inventory_Base;
	class SodaCan_ColorBase;
	class Edible_Base;
	 
	// Overriding item to get an empty can after drinking
	// Just pipsi and cereal for the time being as a proof of concept
	class SodaCan_Pipsi: SodaCan_ColorBase
	{
		destroyOnEmpty=0;
		varQuantityDestroyOnMin=0;

		scope=2;
		displayName="$STR_CfgVehicles_SodaCan_Pipsi0";
		descriptionShort="$STR_CfgVehicles_SodaCan_Pipsi1";
		hiddenSelectionsTextures[]=
		{
			"\dz\gear\drinks\Data\SodaCan_pipsi_co.paa"
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class SodaCan_in_B
				{
					soundSet="SodaCan_in_B_SoundSet";
					id=202;
				};
				class WellPond_loop
				{
					soundSet="WellPond_loop_SoundSet";
					id=209;
				};
				class WellBottle_loop
				{
					soundSet="WellBottle_loop_SoundSet";
					id=210;
				};
				class pickup
				{
					soundSet="SodaCan_pickup_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="SodaCan_drop_SoundSet";
					id=898;
				};
			};
		};
	};

	class BoxCerealCrunchin: Edible_Base
	{
		destroyOnEmpty=0;
		varQuantityDestroyOnMin=0;


		scope=2;
		displayName="$STR_CfgVehicles_BoxCerealCrunchin0";
		descriptionShort="$STR_CfgVehicles_BoxCerealCrunchin1";
		model="\dz\gear\food\BoxCereal.p3d";
		debug_ItemCategory=6;
		rotationFlags=17;
		weight=12;
		itemSize[]={3,3};
		varTemperatureFreezePoint=-25;
		varTemperatureThawPoint=-25;
		varTemperatureFreezeTime=7920;
		varTemperatureThawTime=7920;
		varTemperatureMax=80;
		varQuantityInit=250;
		varQuantityMin=0;
		varQuantityMax=250;
		isMeleeWeapon=1;
		temperaturePerQuantityWeight=4.5;
		hiddenSelections[]=
		{
			"camoGround"
		};
		hiddenSelectionsTextures[]=
		{
			"\dz\gear\food\Data\CerealBox_01_CO.paa"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=20;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\gear\food\data\Cereal_box.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\gear\food\data\Cereal_box.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\gear\food\data\Cereal_box_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\gear\food\data\Cereal_box_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\gear\food\data\Cereal_box_destruct.rvmat"
							}
						}
					};
				};
			};
		};
		class Nutrition
		{
			fullnessIndex=2;
			energy=400;
			water=0;
			nutritionalIndex=1;
			toxicity=0;
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class openTunaCan
				{
					soundSet="openTunaCan_SoundSet";
					id=204;
				};
				class pickup
				{
					soundSet="BoxCerealCrunchin_pickup_SoundSet";
					id=797;
				};
				class Eating_TakeFood
				{
					soundSet="Eating_TakeFood_Soundset";
					id=889;
				};
				class Eating_BoxOpen
				{
					soundSet="Eating_BoxOpen_Soundset";
					id=893;
				};
				class Eating_BoxShake
				{
					soundSet="Eating_BoxShake_Soundset";
					id=894;
				};
				class Eating_BoxEnd
				{
					soundSet="Eating_BoxEnd_Soundset";
					id=895;
				};
				class drop
				{
					soundset="BoxCerealCrunchin_drop_SoundSet";
					id=898;
				};
			};
		};
		class InventorySlotsOffsets
		{
			class DirectCookingA
			{
				position[]={0.059999999,0.017000001,0};
				orientation[]={0,90,180};
			};
			class DirectCookingB
			{
				position[]={0.059999999,0.017000001,0};
				orientation[]={0,270,0};
			};
			class DirectCookingC
			{
				position[]={0.059999999,0.017000001,0};
				orientation[]={0,90,0};
			};
		};
	};

	class TrashCompactor: Inventory_Base
	{
		scope=2;
		displayName="Trash compactor";
		descriptionShort="Compresses trash items into burnable fuel pellets";
		model="\dz\gear\tools\CanOpener.p3d";
		debug_ItemCategory=2;
		animClass="Knife";
		rotationFlags=12;
		isMeleeWeapon=1;
		itemSize[]={1,2};
		weight=150;
		fragility=0.0099999998;
		soundImpactType="metal";
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=20;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\gear\tools\data\Loot_CanOpener.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\gear\tools\data\Loot_CanOpener.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\gear\tools\data\Loot_CanOpener_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\gear\tools\data\Loot_CanOpener_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\gear\tools\data\Loot_CanOpener_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};

	class TrashFuel: Inventory_Base
	{
		scope=2;

		canBeSplit=1;
		varQuantityInit=1;
		varQuantityMin=0;
		varQuantityMax=10;
		varQuantityDestroyOnMin=1;
		varStackMax=10;

		displayName="TrashFuel";
		descriptionShort="Fuel made from trash which can be burned for warmth and cooking";
		model="\dz\gear\medical\charcoal_tablets.p3d";
		debug_ItemCategory=2;
		rotationFlags=17;
		itemSize[]={1,2};
		weight=20;
		absorbency=0.89999998;	 	
		inventorySlot[]=
			{
				"TrashFuel"
			};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=30;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\gear\medical\data\charcoal_tablets.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\gear\medical\data\charcoal_tablets.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\gear\medical\data\charcoal_tablets_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\gear\medical\data\charcoal_tablets_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\gear\medical\data\charcoal_tablets_destruct.rvmat"
							}
						}
					};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickup
				{
					soundSet="purificationtablets_pickup_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="purificationtablets_drop_SoundSet";
					id=898;
				};
			};
		};
	};

	class TrashFire: FireplaceBase
	{
		scope=2;
		displayName="Trash fire";
		descriptionShort="Fire of trash";
		model="\dz\gear\cooking\Fireplace.p3d";
		overrideDrawArea="80.0";
		slopeTolerance=0.30000001;
		physLayer="item_large";
		openable=0;
		lootCategory="Crafted";
		itemSize[]={4,2};
		itemsCargoSize[]={10,6};
		useEntityHierarchy="true";
		attachments[]=
		{
			"TrashFuel",
			"Bark"
		};
		class GUIInventoryAttachmentsProps
		{
			class CookingEquipment
			{
				name="$STR_attachment_CookingEquipment0";
				description="";
				attachmentSlots[]=
				{
					"CookingTripod",
					"CookingEquipment"
				};
				icon="set:dayz_inventory image:cat_fp_cooking";
				view_index=1;
			};
			class Smoking
			{
				name="$STR_attachment_Smoking";
				description="";
				attachmentSlots[]=
				{
					"SmokingA",
					"SmokingB",
					"SmokingC",
					"SmokingD"
				};
				icon="set:dayz_inventory image:cookingequipment";
				view_index=2;
			};
			class DirectCooking
			{
				name="$STR_attachment_CookingEquipment0";
				description="";
				attachmentSlots[]=
				{
					"DirectCookingA",
					"DirectCookingB",
					"DirectCookingC"
				};
				icon="set:dayz_inventory image:cookingequipment";
				view_index=3;
			};
			class Upgrade
			{
				name="$STR_attachment_Upgrade0";
				description="";
				attachmentSlots[]=
				{
					"Stones"
				};
				icon="set:dayz_inventory image:cat_fp_upgrade";
				view_index=4;
			};
			class Fuel
			{
				name="$STR_attachment_Fuel0";
				description="";
				attachmentSlots[]=
				{
					"TrashFuel"
				};
				icon="set:trash_icon image:trash_icon";
				view_index=5;
			};
			class Kindling
			{
				name="$STR_attachment_Kindling0";
				description="";
				attachmentSlots[]=
				{
					"Rags",
					"MedicalBandage",
					"Paper",
					"Bark"
				};
				icon="set:dayz_inventory image:cat_fp_kindling";
				view_index=6;
			};
		};
		hiddenSelections[]=
		{
			"ashes",
			"inventory"
		};
		hiddenSelectionsTextures[]=
		{
			"\dz\gear\cooking\data\stoneground_co.paa",
			"\dz\gear\cooking\data\fireplacekit_co.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"\dz\gear\cooking\data\stonegroundnoemit.rvmat",
			"\dz\gear\cooking\data\fireplacekit.rvmat"
		};
		hologramMaterial="FireplaceKit";
		hologramMaterialPath="dz\gear\cooking\data";
	};
}