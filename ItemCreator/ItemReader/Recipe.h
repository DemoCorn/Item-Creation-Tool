#pragma once

#include "Item.h"

namespace ItemLibrary
{
	struct Recipe
	{
		std::pair<Item*, int> ingredients[4];
		std::pair<Item*, int> output;
	};
}