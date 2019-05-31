#pragma once

#include <regex>

/**
* @brift Code by Karen Nikoghosyan
*/

class RegexCollection
{

public:

   const std::regex var_forward_decl
	{
		"(BYTE|CHAR|WORD|DWORD|QWORD)"
		"([ \t]*[a-zA-Z_][a-zA-Z0-9_]*);"
	};


	 const std::regex var_defin_init
	{
		"(BYTE|CHAR|WORD|DWORD|QWORD)"
		"([ \t]*[a-zA-Z_][a-zA-Z0-9_]*)"
		"([ \t]*=[ \t]*)"
		"('.'|\\d*);"
	};


	 const std::regex array_decl
	{
		"(BYTE|CHAR|WORD|DWORD|QWORD)"
		"([ \t]*[a-zA-Z_][a-zA-Z0-9_]*)"
		"(\\[\\d*\\]|\\[\\]);"
	};


	 const std::regex string_array_decl_init
	{
		"(CHAR)"
		"([ \t]*[a-zA-Z_][a-zA-Z0-9_]*)"
		"(\\[\\])"
		"([ \t]*=[ \t]*)"
		"(\".*\");"
	};

	  const std::regex array_decl_init
	{
		"(BYTE|CHAR|WORD|DWORD|QWORD)"
		"([ \t]*[a-zA-Z_][a-zA-Z0-9_]*)"
		"(\\[\\d*\\]|\\[\\])"
		"([ \t]*=[ \t]*)"
		"(\\{(-?\\d*,[ \t]*)*\\};)"
	};

};
