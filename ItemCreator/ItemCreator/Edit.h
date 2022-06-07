#pragma once

#include <sqlite3.h>
#include <string>
#include <iostream>
#include <vector>

class EditLibrary
{
public:
	static std::string EditHelp()
	{
		return "The \"Edit\" command requires a type of item, a field to edit, the value to set it to and an index\n" +
			(std::string)"Try one of the following\n" +
			"Add Item Name Jackson Brener 8\n" +
			"Add Equipment HealthBoost 20 1\n" +
			"Add Recipe Item4Amount 2 3\n";
	}

	static void EditParse(std::vector<std::string> input, const sqlite3* dbase)
	{
		char* gError = 0;
		std::string sql = "Update ";

		if (input[0] == "item")
		{
			sql += "Item";
		}
		else if (input[0] == "equipment")
		{
			sql += "Equipment";
		}
		else if (input[0] == "recipe")
		{
			sql += "ItemRecipe";
		}
		else if (input[0] == "help")
		{
			system("cls");
			std::cout << EditHelp();
			return;
		}
		else
		{
			system("cls");
			std::cout << "Edit command not recognized.\n";
			return;
		}
		input.erase(input.begin());

		sql += " Set " + input[0] + " = '";
		input.erase(input.begin());

		while (input.size() > 1)
		{
			sql += input[0] + " ";
			input.erase(input.begin());
		}
		sql.pop_back();
		sql += "' where ID = " + input[0] + ";";

		int ctable = sqlite3_exec(const_cast<sqlite3*>(dbase), sql.c_str(), NULL, 0, &gError);

		system("cls");
		if (ctable == SQLITE_OK)
		{
			std::cout << "Entry edited successfully" << std::endl;
		}
		else
		{
			std::cout << "Entry failed to edit" << std::endl;
			std::cout << "Error: " << std::string(gError) << std::endl;
		}
	}
};