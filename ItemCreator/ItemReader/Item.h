#pragma once

#include <string>
#include <filesystem>

namespace ItemLibrary
{
	enum class ItemTypes
	{
		Item,
		Equipment
	};

	struct Item
	{
		int id = -1;
		std::string name;
		std::string description;
		float value = 0.0f;
		std::filesystem::path imageFile;
		ItemTypes type = ItemTypes::Item;
	};
}