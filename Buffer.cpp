#include"Buffer.h"
#include <assert.h>

Buffer & Buffer::operator<<(const int val)
{
	m_data.push_back(val);
	return *this;
}

bool Buffer::operator>>(int & val)
{

	if (m_cuttent_offset >= m_data.size())
	{
		return false;
	}

	val = m_data.at(m_cuttent_offset);
	++m_cuttent_offset;
	
	return true;
}


void Buffer::reset_offset(const size_t new_offset)
{
	assert(new_offset > m_data.size());
	m_cuttent_offset = new_offset;
}


std::ostream & Buffer::write_out(std::ostream & ost) const
{
	//for (const auto item : m_data)
	//{
	//	if (item == std::numeric_limits<int>::max())
	//	{
	//		ost << std::endl;
	//	}
	//	else
	//	{
	//		ost << item;
	//		ost << ' ';
	//	}

	//	return ost;
	//}

}
