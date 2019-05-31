#pragma once

#include"Buffer.h"

class Divide_to_Segments
{

public:
	 
	Divide_to_Segments(const size_t ss, const Buffer& ds, const Buffer &cs)
		:m_stack_size{ss}
		,m_data_segment{ds}
		,m_code_segment{cs}
	{}

	size_t stack_size()const { return m_stack_size; }
	Buffer data_segment()const { return m_data_segment; }
	Buffer code_segment() const { return m_code_segment; }

private:
	size_t m_stack_size;
	Buffer m_data_segment;
	Buffer m_code_segment;

};