#pragma once

#include <iostream>
#include <vector>

namespace StringManipulation
{
	std::vector<std::string> ParseString(std::string toParse, std::string ParseCharecter)
	{
		std::vector<std::string> output;
		size_t pos = 0;
		while ((pos = toParse.find(ParseCharecter)) != std::string::npos) {
			output.push_back(toParse.substr(0, pos));
			toParse.erase(0, pos + ParseCharecter.length());
		}
		if (!toParse.empty());
		output.push_back(toParse);
		return output;
	}

	std::string tolower(std::string input)
	{
		for (uint32_t i = 0; i < input.size(); i++)
		{
			input[i] = std::tolower(input[i]);
		}
		return input;
	}
}