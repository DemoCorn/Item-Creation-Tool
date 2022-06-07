#pragma once

#include "Item.h"

namespace ItemLibrary
{
	struct Equipment : public Item
	{
		float durability;
		float attack;
		float defence;
		float health;
	};
}