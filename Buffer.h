#pragma once

#include<vector>


class Buffer
{
public:

	Buffer() = default;

	Buffer & operator << (const int val);
	bool operator >> (int & val);


	void reset_offset(const size_t new_offset = 0);
	std::ostream & write_out(std::ostream & ost) const;

private:
	std::vector<size_t> m_data;
	size_t m_cuttent_offset{ 0u };
};