#pragma once

#include "Commands and types .h"
#include "Divide  to Segments.h"
#include "Buffer.h"
#include "Utility.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <regex>



class Parser
{

public:

	Parser(const std::vector<std::string> & txt_file);

	Divide_to_Segments div_to_segments() const;



private:
	using code_iterator = std::vector<std::string>::const_iterator;
	static constexpr auto chack_point = std::numeric_limits<int>::max();


	void forward_decl(std::cmatch & tokens);
	void def_and_init(std::cmatch & tokens);
	void array_decl(std::cmatch & tokens);
	void string_array_decl_init(std::cmatch & tokens);
	void array_decl_init(std::cmatch & tokens);


	code_iterator stack_size(code_iterator begin, code_iterator end);
	code_iterator data_segment(code_iterator begin, code_iterator end);
	code_iterator code_segment(code_iterator begin, code_iterator end);


	Type find_type(const std::string& type_name);
	Command find_command(const std::string & command_name);


private:


	size_t m_stack_size;
	Buffer m_data_segment_buffer;
	Buffer m_code_segment_buffer;


	std::unordered_map<std::string, size_t> m_var_name_to_id_map;
	size_t m_free_var_id;


	std::unordered_map<std::string, size_t> m_label_name_to_id_map;
	size_t m_free_label_id;

	
	static const std::unordered_map<std::string, Command> command_enum_map;
	static const std::unordered_map<std::string, Type> type_enum_map;
};

