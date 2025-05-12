Mission CreateCustomMission(string path)
{
	return new MissionGameplay();
}

void main()
{
	PlayerBase player;
	ItemBase item;

	player = PlayerBase.Cast( GetGame().CreatePlayer(NULL, "SurvivorF_Linda", "2200 10 2200", 0, "NONE") );

	player.GetInventory().CreateInInventory("TShirt_Red");
	player.GetInventory().CreateInInventory("ShortJeans_Green");
	
 	player.GetInventory().CreateInInventory("HuntingBag");

 	player.GetInventory().CreateInInventory("WaterBottle");
 	player.GetInventory().CreateInInventory("PetrolLighter");
 	player.GetInventory().CreateInInventory("TrashFuel");
 	player.GetInventory().CreateInInventory("TrashCompactor");
	player.GetInventory().CreateInInventory("SodaCan_Pipsi");
	player.GetInventory().CreateInInventory("BoxCerealCrunchin");

	GetGame().SelectPlayer(NULL, player);
}