#pragma once

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

	static std::string AddParse(std::vector<std::string> input, const sqlite3* dbase)
	{
		if (input.size() > 1)
		{
			if (input[0] == "item" && input[0] == "recipe")
			{

			}
			else if (input[0] == "equipment" && input[0] == "recipe")
			{

			}
		}
		else if (input[0] == "item")
		{
			CreateItem(dbase);
			return "";

		}
		else if (input[0] == "equipment")
		{

		}
		else if (input[0] == "itemrecipe")
		{

		}
		else if (input[0] == "equipmentrecipe")
		{

		}
		else
		{
			return "Add command not recognized.";
		}
	}

private:
	static void CreateItem(const sqlite3* dbase)
	{
		char* gError = 0;
		std::string input;
		std::string sql = "Insert Into Item(Name, Value, ImageFile) Values(";

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

		std::cout << "Item image file path:\n";
		std::getline(std::cin, input);
		sql += "'";
		sql += input;
		sql += "');";

		int ctable = sqlite3_exec(const_cast<sqlite3*>(dbase), sql.c_str(), NULL, 0, &gError);

		std::cout << std::endl;
		if (ctable == SQLITE_OK)
		{
			std::cout << "Command ran successfully" << std::endl;
		}
		else
		{
			std::cout << "Command failed to run" << std::endl;
			std::cout << "Error: " << std::string(gError) << std::endl;
		}
	}

};