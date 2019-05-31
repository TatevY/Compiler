#include "File.h"
#include <cassert>
#include <exception>
#include <string>


File::File(const std::string & file_name)
	: m_buffer{ file_name, std::fstream::out | std::fstream::in } {}

File::~File()
{
	try
	{
		m_buffer.close();
	}
	catch (...)
	{
		assert(false);
	}
}

std::vector<std::string> File::read_in()
{
	std::vector<std::string> result;
	m_buffer.seekg(0);
	if (std::string line; m_buffer.is_open())
	{
		while (getline(m_buffer, line))
		{
			if (line.empty())
			{
				continue;
			}
			result.push_back(line);
		}
	}

	return result;
}

void File::write_out(const std::vector<std::string>& lines)
{
	if (!m_buffer.is_open())
	{
		throw std::exception{ "fatal error: no input files" };
	}

	for (const auto& line : lines)
	{
		m_buffer << line << std::endl;
	}
}
