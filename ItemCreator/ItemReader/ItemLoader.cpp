#include <sqlite3.h>

#include "ItemLoader.h"
#include "Item.h"
#include "Equipment.h"
#include "Recipe.h"

namespace
{
	static int LoadItems(void* data, int argc, char** argv, char** azColName) 
	{
		std::vector<ItemLibrary::Item*>* returnData = (std::vector<ItemLibrary::Item*>*)data;
		ItemLibrary::Equipment* item = new ItemLibrary::Equipment;

		item->id = std::stoi((std::string)argv[0]);
		item->name = (std::string)argv[1];
		item->description = (std::string)argv[2];
		item->value = std::stof((std::string)argv[3]);
		item->imageFile = (std::string)argv[4];
		item->type = ItemLibrary::ItemTypes::Item;

		returnData->push_back(item);
		data = returnData;
		return 0;
	}

	static int LoadEquipment(void* data, int argc, char** argv, char** azColName) 
	{
		std::vector<ItemLibrary::Item*>* returnData = (std::vector<ItemLibrary::Item*>*)data;
		ItemLibrary::Equipment* item = static_cast<ItemLibrary::Equipment*>(ItemLibrary::ItemLoader::GetItem(std::stoi((std::string)argv[1]), *returnData));


		item->durability = std::stof((std::string)argv[2]);
		item->attack = std::stof((std::string)argv[3]);
		item->defence = std::stof((std::string)argv[4]);
		item->health = std::stof((std::string)argv[5]);
		item->type = ItemLibrary::ItemTypes::Equipment;

		return 0;
	}

	static int LoadRecipe(void* data, int argc, char** argv, char** azColName) 
	{
		ItemLibrary::ItemLoader* returnData = (ItemLibrary::ItemLoader*)data;

		ItemLibrary::Recipe* recipe = new ItemLibrary::Recipe;

		for (int i = 0; i < 4; i++)
		{
			recipe->ingredients[i] = std::make_pair(ItemLibrary::ItemLoader::GetItem(std::stoi((std::string)argv[i + 1]), returnData->items), std::stoi((std::string)argv[i+5]));
		}

		recipe->output = std::make_pair(ItemLibrary::ItemLoader::GetItem(std::stoi((std::string)argv[9]), returnData->items), std::stoi((std::string)argv[10]));

		returnData->recipes.push_back(recipe);
		data = returnData;
		return 0;
	}
}

std::string ItemLibrary::ItemLoader::Load(std::filesystem::path FilePath)
{
	if (!std::filesystem::exists(FilePath))
	{
		return "File does not exist";
	}

	std::string returnMessage = "";

	sqlite3* dbase;
	char* errMsg;
	int sq = 0;
	std::string sql;

	sq = sqlite3_open(FilePath.string().c_str(), &dbase);
	if (!sq == SQLITE_OK)
	{
		sqlite3_close(dbase);
		return "Could not open database";
	}

	sql = "SELECT * from Item";
	sq = sqlite3_exec(dbase, sql.c_str(), LoadItems, &items, &errMsg);

	if (sq != SQLITE_OK) {
		returnMessage = (std::string)errMsg;
		sqlite3_free(errMsg);
		sqlite3_close(dbase);
		return returnMessage;
	}

	sql = "SELECT * from Equipment";
	sq = sqlite3_exec(dbase, sql.c_str(), LoadEquipment, &items, &errMsg);

	if (sq != SQLITE_OK) {
		returnMessage = (std::string)errMsg;
		sqlite3_free(errMsg);
		sqlite3_close(dbase);
		return returnMessage;
	}

	sql = "SELECT * from ItemRecipe";
	sq = sqlite3_exec(dbase, sql.c_str(), LoadRecipe, this, &errMsg);

	if (sq != SQLITE_OK) {
		returnMessage = (std::string)errMsg;
		sqlite3_free(errMsg);
		sqlite3_close(dbase);
		return returnMessage;
	}

	return returnMessage;
}

ItemLibrary::Item* ItemLibrary::ItemLoader::GetItem(int id, std::vector<Item*> items)
{
	for (Item* item : items)
	{
		if (item->id == id)
		{
			return item;
		}
	}
	return nullptr;
}

ItemLibrary::ItemLoader::~ItemLoader()
{
	for (Item* item : items)
	{
		delete(item);
		item = nullptr;
	}
	for (Recipe* rec : recipes)
	{
		delete(rec);
		rec = nullptr;
	}
}