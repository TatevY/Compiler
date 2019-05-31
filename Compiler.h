#pragma once

#include "Divide  to Segments.h"
#include "File.h"
#include "Parser.h"

#include<string>


class Compiler
{

public:

	Compiler(std::string);
	~Compiler() = default;

	Divide_to_Segments compile_code() const;

private:
	std::string m_file_name;

};

