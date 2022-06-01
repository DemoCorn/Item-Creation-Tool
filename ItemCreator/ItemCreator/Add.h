#pragma once

#include <sqlite3.h>
#include <string>
#include <iostream>
#include <vector>

class AddLibrary
{
public:
	static std::string AddHelp()
	{
		return "The \"Add\" command requires a type of item\n" +
			(std::string)"Try one of the following\n" +
			"Add Item\n" +
			"Add Equipment\n" +
			"Add Item Recipe\n" +
			"Add Equipment Recipe\n";
	}

	static void AddParse(std::vector<std::string> input, const sqlite3* dbase)
	{
		if (input.size() > 1)
		{
			if (input[0] == "item" && input[1] == "recipe")
			{
				CreateItemRecipe(dbase);
			}
			else if (input[0] == "equipment" && input[1] == "recipe")
			{
				CreateEquipmentRecipe(dbase);
			}
		}
		else if (input[0] == "item")
		{
			CreateItem(dbase);
		}
		else if (input[0] == "equipment")
		{
			CreateEquipment(dbase);
		}
		else if (input[0] == "itemrecipe")
		{
			CreateItemRecipe(dbase);
		}
		else if (input[0] == "equipmentrecipe")
		{
			CreateEquipmentRecipe(dbase);
		}
		else if (input[0] == "help")
		{
			system("cls");
			std::cout << AddHelp();
		}
		else
		{
			system("cls");
			std::cout << "Add command not recognized.\n";
		}
	}

private:
	static void CreateItem(const sqlite3* dbase)
	{
		char* gError = 0;
		std::string input;
		std::string sql = "Insert Into Item(Name, ItemValue, Description, ImageFile) Values(";

		std::cout << "Item name:\n";
		std::getline(std::cin, input);
		sql += "'";
		sql += input;
		sql += "',";

		std::cout << "Item value:\n";
		std::getline(std::cin, input);
		sql += "'";
		sql += input;
		sql += "',";

		std::cout << "Item Description:\n";
		std::getline(std::cin, input);
		sql += "'";
		sql += input;
		sql += "',";

		std::cout << "Item image file path:\n";
		std::getline(std::cin, input);
		sql += "'";
		sql += input;
		sql += "');";

		int ctable = sqlite3_exec(const_cast<sqlite3*>(dbase), sql.c_str(), NULL, 0, &gError);
		system("cls");

		if (ctable == SQLITE_OK)
		{
			std::cout << "Item added successfully" << std::endl;
		}
		else
		{
			std::cout << "Item failed to add" << std::endl;
			std::cout << "Error: " << std::string(gError) << std::endl;
		}
	}

	static void CreateEquipment(const sqlite3* dbase)
	{
		char* gError = 0;
		std::string input;
		std::string sql = "Insert Into Equipment(ItemID, Durability, AttackBoost, DefenceBoost, HealthBoost) Values(";

		std::cout << "Linked Item ID: ";
		std::getline(std::cin, input);
		sql += "'";
		sql += input;
		sql += "',";

		std::cout << "Equipment durability: ";
		std::getline(std::cin, input);
		sql += "'";
		sql += input;
		sql += "',";

		std::cout << "Equipment attack boost: ";
		std::getline(std::cin, input);
		sql += "'";
		sql += input;
		sql += "',";

		std::cout << "Equipment defence boost: ";
		std::getline(std::cin, input);
		sql += "'";
		sql += input;
		sql += "',";

		std::cout << "Equipment health boost: ";
		std::getline(std::cin, input);
		sql += "'";
		sql += input;
		sql += "');";

		int ctable = sqlite3_exec(const_cast<sqlite3*>(dbase), sql.c_str(), NULL, 0, &gError);

		system("cls");
		if (ctable == SQLITE_OK)
		{
			std::cout << "Equipment added successfully" << std::endl;
		}
		else
		{
			std::cout << "Equipment failed to add" << std::endl;
			std::cout << "Error: " << std::string(gError) << std::endl;
		}
	}

	static void CreateRecipe(const sqlite3* dbase, std::string sql)
	{
		char* gError = 0;
		std::string input;

		for (int i = 0; i < 4; ++i)
		{
			std::cout << "Component " + std::to_string(i+1) + "s ID: ";
			std::getline(std::cin, input);
			sql += "'";
			sql += input;
			sql += "',";

			std::cout << "Component " + std::to_string(i+1) + "s Amount: ";
			std::getline(std::cin, input);
			sql += "'";
			sql += input;
			sql += "',";
		}

		std::cout << "Result ID: ";
		std::getline(std::cin, input);
		sql += "'";
		sql += input;
		sql += "',";

		std::cout << "Result Amount: ";
		std::getline(std::cin, input);
		sql += "'";
		sql += input;
		sql += "');";

		int ctable = sqlite3_exec(const_cast<sqlite3*>(dbase), sql.c_str(), NULL, 0, &gError);

		system("cls");
		if (ctable == SQLITE_OK)
		{
			std::cout << "Recipe added successfully" << std::endl;
		}
		else
		{
			std::cout << "Recipe failed to add" << std::endl;
			std::cout << "Error: " << std::string(gError) << std::endl;
		}
	}

	static void CreateItemRecipe(const sqlite3* dbase)
	{
		CreateRecipe(dbase, "Insert Into ItemRecipe(Item1, Item1Amount, Item2, Item2Amount, Item3, Item3Amount, Item4, Item4Amount, OutputItem, OutputAmount) Values(");
	}

	static void CreateEquipmentRecipe(const sqlite3* dbase)
	{
		CreateRecipe(dbase, "Insert Into Equipment(Item1, Item1Amount, Item2, Item2Amount, Item3, Item3Amount, Item4, Item4Amount, OutputItem, OutputAmount) Values(");
	}
};