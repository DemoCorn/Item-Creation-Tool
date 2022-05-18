#include <iostream>
#include <sqlite3.h>
#include <vector>

std::vector<std::string> ParseString(std::string toParse, std::string ParseCharecter)
{
	std::vector<std::string> output;
	size_t pos = 0;
	while ((pos = toParse.find(ParseCharecter)) != std::string::npos) {
		output.push_back(toParse.substr(0, pos));
		toParse.erase(0, pos + ParseCharecter.length());
	}
}

void ProcessArguments(std::string input)
{
	std::vector<std::string> arguments = ParseString(input, " ");

	if (arguments[0] == "Add")
	{
		// Add Item
	}
	else if (arguments[0] == "Delete")
	{
		// Delete item by index
	}
	else if (arguments[0] == "Edit")
	{
		// Edit item
	}
	else if (arguments[0] == "Output")
	{
		// Show table
	}
	else if (arguments[0] == "Quit")
	{
		// Quit
	}
}

int main()
{
	return 0;
}