#pragma once

#include <vector>
#include <string>
#include <fstream>

class File
{
public:
	File(const std::string& file_name);
	~File();

	std::vector<std::string> read_in();
	void write_out(const std::vector<std::string>& lines);
	std::fstream m_buffer;
};