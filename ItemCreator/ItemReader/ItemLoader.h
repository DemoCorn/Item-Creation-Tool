#pragma once

#include <filesystem>

namespace ItemLibrary
{
	struct Item;
	struct Equipment;
	struct Recipe;

	struct ItemLoader
	{
		std::string Load(std::filesystem::path FilePath);

		static Item* GetItem(int id, std::vector<Item*> items);

		std::vector<Item*> items;
		std::vector<Recipe*> recipes;

		~ItemLoader();
	};
}