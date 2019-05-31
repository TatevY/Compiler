
#pragma once
#include<string>
#include<unordered_map>

class RegSize
{
public:
	enum class R_Size
	{
		B, W, DB, DW
	};

	R_Size get_reg_size(const std::string &name)
	{
		return reg_size_name.at(name);
	}

	const std::unordered_map<std::string, RegSize::R_Size> reg_size_name
	{
		{ "B", R_Size::B },
	{ "W", R_Size::W },
	{ "DB", R_Size::DB },
	{ "DW", R_Size::DW },
	};
};



