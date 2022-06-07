#pragma once

class OutputLibrary
{
public:
	static std::string OutputHelp()
	{
		return "The \"Output\" command requires a type of item\n" +
			(std::string)"Try one of the following\n" +
			"Output Item\n" +
			"Output Equipment\n" +
			"Output Recipe\n";
	}

	static void OutputParse(std::vector<std::string> input, const sqlite3* dbase)
	{
		char* gError = 0;
		std::string sql = "Select * from ";

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
			std::cout << OutputHelp();
			return;
		}
		else
		{
			system("cls");
			std::cout << "Output command not recognized.\n";
			return;
		}

		system("cls");
		int ctable = sqlite3_exec(const_cast<sqlite3*>(dbase), sql.c_str(), Output, 0, &gError);
	}

private:
	static int Output(void* data, int argc, char** argv, char** azColName) {
		for (int i = 0; i < argc; i++) {
			printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		}

		printf("\n");
		return 0;
	}
};