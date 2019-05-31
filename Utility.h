#pragma once

#include <vector>
#include<string>
#include<regex>

#include "String to tokens.h"

//std::vector<std::string>  split(std::string in, const std::string & regex = " ")
//{
//
//	in.erase(std::unique_copy(std::begin(in), std::end(in),
//		std::begin(in), [](const char c1, const char c2)
//	{
//		return c1 == ' ' && c2 == ' ';
//	}), std::end(in));
//
//	const std::regex re(regex);
//	const std::sregex_token_iterator first
//	{ std::begin(in),std::end(in), re,-1 };
//
//	const std::sregex_token_iterator last;
//	return { first,last };
//
//}



int to_int(const std::string& num){}

std::size_t to_size_t(const std::string&num){}

double to_double(const std::string &num) { return std::stod(num); }