#include "String to tokens.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <regex>



std::vector<std::string> split(std::string input,
	const std::string & regex)
	//{
	//	std::vector<std::string> tokens;
	//	std::stringstream check1(input);
	//	std::string intermediate;
	//
	//	while (getline(input, intermediate,regex))
	//	{
	//		tokens.push_back(intermediate);
	//	}
	//
	//
	//	for (int i = 0; i < tokens.size(); i++)
	//	return tokens[i];
	//}

{
	input.erase(std::unique_copy(std::begin(input), std::end(input), std::begin(input)
		, [](const char c1, const char c2)
	{
		return c1 == ' ' && c2 == ' ';
	}), std::end(input));
	const std::regex re(regex);
	const std::sregex_token_iterator first{ std::begin(input), std::end(input), re, -1 };
	const std::sregex_token_iterator last;
	return { first, last };
}

