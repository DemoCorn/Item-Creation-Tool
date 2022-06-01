#pragma once

#include <string>
#include <iostream>
#include <vector>

class DeleteLibrary
{
public:
	static std::string DeleteHelp()
	{
		return "The \"Delete\" command requires a type of item and an index\n" +
			(std::string)"Try one of the following\n" +
			"Delete Item 2\n" +
			"Delete Equipment 0\n" +
			"Delete Item Recipe 1\n" +
			"Delete Equipment Recipe All\n";
	}

	static void DeleteParse(std::vector<std::string> input, const sqlite3* dbase)
	{
		char* gError = 0;
		std::string sql = "Delete From ";

		if (input.size() > 2)
		{
			if (input[0] == "item" && input[1] == "recipe")
			{
				sql += "ItemRecipe";
				input.erase(input.begin());
			}
			else if (input[0] == "equipment" && input[1] == "recipe")
			{
				sql += "EquipmentRecipe";
				input.erase(input.begin());
			}
		}

		if (input[0] == "item")
		{
			sql += "Item";
		}
		else if (input[0] == "equipment")
		{
			sql += "Equipment";
		}
		else if (input[0] == "itemrecipe")
		{
			sql += "ItemRecipe";
		}
		else if (input[0] == "equipmentrecipe")
		{
			sql += "EquipmentRecipe";
		}
		else if (input[0] == "help")
		{
			system("cls");
			std::cout << DeleteHelp();
			return;
		}
		else
		{
			system("cls");
			std::cout << "Delete command not recognized.\n";
			return;
		}

		if (input[1] != "all")
		{
			sql += " Where ID =" + input[1];
		}
		sql += ";";

		int ctable = sqlite3_exec(const_cast<sqlite3*>(dbase), sql.c_str(), NULL, 0, &gError);

		system("cls");
		if (ctable == SQLITE_OK)
		{
			std::cout << "Entry deleted successfully" << std::endl;
		}
		else
		{
			std::cout << "Entry failed to delete" << std::endl;
			std::cout << "Error: " << std::string(gError) << std::endl;
		}
	}
};