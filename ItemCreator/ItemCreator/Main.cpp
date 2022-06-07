#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <cstdint>
#include <filesystem>
#include <string>

#include "StringManipulation.h"
#include "Add.h"
#include "Delete.h"
#include "Output.h"
#include "Edit.h"

void CreateDatabase(const sqlite3* dbase)
{
	char* gError = 0;
	std::string sql;

	sql = "Create Table Item("
		"ID		integer		primary key autoincrement,"
		"Name	text(40),"
		"Description	text(40),"
		"ItemValue	float,"
		"ImageFile text(" + std::to_string(FILENAME_MAX) + "));"

		"Create Table Equipment("
		"ID		integer		primary key autoincrement,"
		"ItemID int,"
		"Durability float,"
		"AttackBoost float,"
		"DefenceBoost float,"
		"HealthBoost float,"
		"Foreign Key(ItemID) References Item(ID));"

		"Create Table ItemRecipe("
		"ID    integer		primary key autoincrement,"
		"Item1 int,"
		"Item2 int,"
		"Item3 int,"
		"Item4 int,"
		"Item1Amount int,"
		"Item2Amount int,"
		"Item3Amount int,"
		"Item4Amount int,"
		"OutputItem int,"
		"OutputAmount int,"
		"Foreign Key(Item1) References Item(ID)"
		"Foreign Key(Item2) References Item(ID)"
		"Foreign Key(Item3) References Item(ID)"
		"Foreign Key(Item4) References Item(ID)"
		"Foreign Key(OutputItem) References Item(ID));";

	int ctable = sqlite3_exec(const_cast<sqlite3*>(dbase), sql.c_str(), NULL, 0, &gError);

	if (ctable == SQLITE_OK)
	{
		std::cout << "Database setup successfully" << std::endl;
	}
	else
	{
		std::cout << "Database setup failed to run" << std::endl;
		std::cout << "Error: " << std::string(gError) << std::endl;
	}
}

bool ProcessArguments(std::string input, const sqlite3* dbase)
{
	// Cleaning and parsing input
	if (input.empty())
	{
		system("cls");
		return false;
	}
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
	}
	else if (arguments[0] == "delete")
	{
		if (arguments.size() < 2)
		{
			std::cout << DeleteLibrary::DeleteHelp() << std::endl;
			return false;
		}

		arguments.erase(arguments.begin());
		DeleteLibrary::DeleteParse(arguments, dbase);
	}
	else if (arguments[0] == "edit")
	{
		if (arguments.size() < 2)
		{
			std::cout << EditLibrary::EditHelp() << std::endl;
			return false;
		}

		arguments.erase(arguments.begin());
		EditLibrary::EditParse(arguments, dbase);
	}
	else if (arguments[0] == "output")
	{
		if (arguments.size() < 2)
		{
			std::cout << OutputLibrary::OutputHelp() << std::endl;
			return false;
		}

		arguments.erase(arguments.begin());
		OutputLibrary::OutputParse(arguments, dbase);
	}
	else if (arguments[0] == "help")
	{
		system("cls");

		if (arguments.size() > 1)
		{
			if (arguments[1] == "add")
			{
				std::cout << AddLibrary::AddHelp();
			}
			else if (arguments[1] == "delete")
			{
				std::cout << DeleteLibrary::DeleteHelp();
			}
			else if (arguments[1] == "edit")
			{
				std::cout << EditLibrary::EditHelp();
			}
			else if (arguments[1] == "output")
			{
				std::cout << OutputLibrary::OutputHelp();
			}
			else
			{
				std::cout << "Help command not recognized" << std::endl;
			}
		}
		else
		{
			std::cout << "Add: Adds an object\n" <<
				"Delete: Removes an object\n" <<
				"Edit: Changes an entry in an object\n" <<
				"Output: Shows all objects of a type\n" <<
				"Quit: Closes program\n" <<
				"Run anything but quit with help to see commands for it\n";
		}
	}
	else if (arguments[0] == "quit")
	{
		return true;
	}
	else
	{
		system("cls");
		std::cout << "Command not recognized" << std::endl;
	}
	return false;
}

int main(int argc, char* argv[])
{
	sqlite3* dbase;
	char* gError = 0;
	std::string sql;
	std::string input;
	bool userQuit;

	bool createFile = !std::filesystem::exists(argv[1]);

	int sq = sqlite3_open(argv[1], &dbase);

	if (sq == SQLITE_OK)
	{
		std::cout << "Database created/opened successfully\n\n";
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

	do
	{
		std::cout << "\nInput next command:\n";
		std::getline(std::cin, input);
		userQuit = ProcessArguments(input, dbase);
	} while (!userQuit);

	sqlite3_close(dbase);

	return 0;
}