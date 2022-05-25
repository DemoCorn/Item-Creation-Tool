#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <cstdint>
#include <filesystem>
#include <string>

#include "StringManipulation.h"
#include "Add.h"


void CreateDatabase(const sqlite3* dbase)
{
	char* gError = 0;
	std::string sql;

	sql = "Create Table Item("
		"ID		integer		primary key autoincrement,"
		"Name	text(40),"
		"Value	text(40),"
		"ImageFile text(" + std::to_string(FILENAME_MAX) + "));"

		"Create Table Equipment("
		"ID		integer		primary key autoincrement,"
		"ItemID int,"
		"Durability int,"
		"AttackBoost int,"
		"DefenceBoost int,"
		"HealthBoost int,"
		"SpeedBoost int,"
		"Foreign Key(ItemID) References Item(ID));"

		"Create Table ItemRecipe("
		"ID    integer		primary key autoincrement,"
		"Item1 int,"
		"Item2 int,"
		"Item3 int,"
		"Item4 int,"
		"Output int,"
		"Foreign Key(Item1) References Item(ID)"
		"Foreign Key(Item2) References Item(ID)"
		"Foreign Key(Item3) References Item(ID)"
		"Foreign Key(Item4) References Item(ID)"
		"Foreign Key(Output) References Item(ID));"

		"Create Table EquipmentRecipe("
		"ID    integer		primary key autoincrement,"
		"Item1 int,"
		"Item2 int,"
		"Item3 int,"
		"Item4 int,"
		"Output int,"
		"Foreign Key(Item1) References Item(ID)"
		"Foreign Key(Item2) References Item(ID)"
		"Foreign Key(Item3) References Item(ID)"
		"Foreign Key(Item4) References Item(ID)"
		"Foreign Key(Output) References Equipment(ID));";

	int ctable = sqlite3_exec(const_cast<sqlite3*>(dbase), sql.c_str(), NULL, 0, &gError);

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

bool ProcessArguments(std::string input, const sqlite3* dbase)
{
	// Cleaning and parsing input
	input = StringManipulation::tolower(input);
	std::vector<std::string> arguments = StringManipulation::ParseString(input, " ");

	if (arguments[0] == "add")
	{
		if (arguments.size() < 2)
		{
			std::cout << AddLibrary::AddHelp() << std::endl;
			return false;
		}
		arguments.erase(arguments.begin());

		AddLibrary::AddParse(arguments, dbase);
		// Add Item
	}
	else if (arguments[0] == "delete")
	{
		// Delete item by index
	}
	else if (arguments[0] == "edit")
	{
		// Edit item
	}
	else if (arguments[0] == "output")
	{
		// Show table
	}
	else if (arguments[0] == "help")
	{
		// Show Command List
	}
	else if (arguments[0] == "quit")
	{
		return true;
	}
}

int main(int argc, char* argv[])
{
	sqlite3* dbase;
	char* gError = 0;
	std::string sql;

	bool createFile = !std::filesystem::exists(argv[1]);

	int sq = sqlite3_open(argv[1], &dbase);

	if (sq == SQLITE_OK)
	{
		std::cout << "Database created/opened successfully" << std::endl;
	}

	else
	{
		std::cout << "Database creation/opening failed" << std::endl;
		std::cout << "Error Code: " << sq << std::endl;
	}

	if (createFile)
	{
		CreateDatabase(dbase);
	}

	ProcessArguments("Add Item", dbase);

	sqlite3_close(dbase);

	return 0;
}