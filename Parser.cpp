#include"Parser.h"
#include"Parser Instructions.h"
#include <assert.h>


Parser::Parser(const std::vector<std::string>& txt_file)
	:m_stack_size{0}
	,m_free_var_id{0}
{
	auto end_phase = this->stack_size(std::cbegin(txt_file), std::cend(txt_file));
	end_phase = this->data_segment(end_phase, std::cend(txt_file));
	end_phase = this->code_segment(end_phase, std::cend(txt_file));

}



Divide_to_Segments Parser::div_to_segments() const
{
	return Divide_to_Segments{ m_stack_size,m_data_segment_buffer,m_code_segment_buffer };
}



void Parser::forward_decl(std::cmatch & tokens)
{

	auto it = ++std::begin(tokens);
	m_data_segment_buffer << static_cast<int>(find_type(*it));
	const auto var = (*(++it)).str();


	m_var_name_to_id_map[std::string{ var }] = m_free_var_id;
	++m_free_var_id;
	m_data_segment_buffer << 1;
	m_data_segment_buffer << 0;

	assert(++it == std::end(tokens));

}




void Parser::def_and_init(std::cmatch & tokens)
{

	auto it = ++std::begin(tokens);
	const auto type = find_type(*it);
	m_data_segment_buffer << static_cast<int>(type);
	const auto var = (*(++it)).str();


	m_var_name_to_id_map[std::string{}] = m_free_var_id;
	m_data_segment_buffer << m_free_var_id;
	++m_free_var_id;
	m_data_segment_buffer << 1;

	++it;

	const auto val = std::string{ (*(++it)).str };
	if (Type::char_type == type)
	{
		assert(val.length() == 3);
		m_data_segment_buffer << static_cast<int>(val[1]);
	}

	m_data_segment_buffer << to_int(val);

	assert(++it == std::end(tokens));
}





void Parser::array_decl(std::cmatch & tokens)
{

	auto it = ++std::begin(tokens);
	const auto type = find_type(*it);
	m_data_segment_buffer << static_cast<int>(type);
	const auto var = (*(++it)).str();


	m_var_name_to_id_map[std::string{ var }] = m_free_var_id;
	m_data_segment_buffer << m_free_var_id;
	++m_free_var_id;

	auto str_count = std::string{ (*(++it)).str() };
	str_count.erase(std::begin(str_count));
	str_count.erase(std::end(str_count)-1);
	const auto count = to_int(str_count);

	for (auto i = 0; i < count; ++i)
	{
		m_data_segment_buffer << 0;
	}

	assert(++it == std::end(tokens));

}




void Parser::string_array_decl_init(std::cmatch & tokens)
{

	auto it = ++std::begin(tokens);
	const auto type = find_type(*it);
	m_data_segment_buffer << static_cast<int>(type);
	const auto var = (*(++it)).str();

	m_var_name_to_id_map[std::string{ var }] = m_free_var_id;
	m_data_segment_buffer << m_free_var_id;
	++m_free_var_id;

	++it; ++it; ++it;

	auto str_val = std::string{ (*(it)).str() };
	str_val.erase(std::begin(str_val));
	str_val.erase(std::end(str_val) - 1);
	const auto count = std::size(str_val);
	m_data_segment_buffer << count;

	for (const auto ch:str_val)
	{
		m_data_segment_buffer << static_cast<int>(ch);
	}


	assert(++it == std::end(tokens));
}





void Parser::array_decl_init(std::cmatch & tokens)
{


	auto it = ++std::begin(tokens);
	const auto type = find_type(*it);
	m_data_segment_buffer << static_cast<int>(type);
	const auto var = (*(++it)).str();

	m_var_name_to_id_map[std::string{ var }] = m_free_var_id;
	m_data_segment_buffer << m_free_var_id;
	++m_free_var_id;

	++it; ++it; ++it;

	auto string_val = std::string{ (*(it)).str() };
	string_val = string_val.substr(1, std::size(string_val) - 4);
	const auto values = split(string_val, ",");
	const auto count = std::size(values);


	m_data_segment_buffer << count;
	for (const auto & val:values)
	{
		m_data_segment_buffer << to_int(val);
	}

	assert(++++it == std::end(tokens));

}





using code_iterator = std::vector<std::string>::const_iterator;




code_iterator Parser::stack_size(code_iterator begin, code_iterator end)
{
	auto it = begin;
	for (; it != end; ++it)
	{
		const auto res = (*it).find(".STACK");

		if (std::string::npos != res)
		{
			break;
		}
	}


	assert(it != end);
	std::smatch match;
	const std::regex regx("([[:digit::]]+)");
	std::regex_search(*it, match, regx);

	m_stack_size = to_size_t(match[1]);

	return ++it;
}



code_iterator Parser::data_segment(code_iterator begin, code_iterator end)
{

	auto it = begin;
	for (; it != end; ++it)
	{
		const auto res = (*it).find(".DATA");
		if (std::string::npos != res)
		{
			break;
		}
	}

	assert(it != end);
	++it;


	for (; it != end; ++it)
	{
		const auto &line = *it;
		std::cmatch result;

		if (std::regex_match(line.c_str(), result,RegexCollection::var_forward_decl))
		{
			this->forward_decl(result);
		}
		
		else if (std::regex_match(line.c_str(), result, RegexCollection::var_defin_init))
		{
			this->def_and_init(result);
		}

		else if (std::regex_match(line.c_str(), result, RegexCollection::array_decl))
		{
			this->array_decl(result);
		}

		else if (std::regex_match(line.c_str(), result, RegexCollection::string_array_decl_init))
		{
			this->string_array_decl_init(result);
		}

		else if (std::regex_match(line.c_str(), result, RegexCollection::array_decl_init))
		{
			this->array_decl_init(result);
		}

		else
		{
			const auto res = (*it).find(".CODE");
			if (std::string::npos != res)
			{
				break;
			}
			assert(false);
		}

		m_data_segment_buffer << this->chack_point;

	}


	return it;

}

code_iterator Parser::code_segment(code_iterator begin, code_iterator end)
{
	
	auto it = begin;
	for (; it != end; ++it)
	{
		const auto res = (*it).find(".CODE");
		if (std::string::npos != res)
		{
			break;
		}
	}

	assert(it != end);
	++it;



	for (; it != end; ++it)
	{
		const auto tokens = split(*it);

		const auto command = find_command(tokens[0]);
		m_code_segment_buffer << static_cast<int>(command);

		switch (command)
		{

		case Command::assign:
		case Command::add:
		case Command::sub:
		case Command::mul:
		case Command::div:
		case Command::mov:
		case Command::cmp:
		case Command::and_:
		case Command::or_:
		case Command::xor_:

			if (std::size(tokens) != 3)
			{
				assert(true);
			}
			m_code_segment_buffer << to_int(tokens[1]) << to_int(tokens[2]);
			break;

		case Command::print:
		case Command::not_:
		case Command::jz:
		case Command::jnz:
		case Command::jo:
		case Command::jno:
		case Command::jc:
		case Command::jnc:
		case Command::call:


			if (std::size(tokens) != 2)
			{
				assert(true);
			}
			m_code_segment_buffer << to_int(tokens[1]);
			break;


		case Command::label:
		{

			const auto& label_name = tokens[2];

			m_label_name_to_id_map[label_name] = m_free_label_id;
			m_code_segment_buffer << m_free_label_id;
			++m_free_label_id;

			break;
		}


		case Command::end:
		case Command::ret:
		{
			const auto command = find_command(tokens[0]);
			m_code_segment_buffer << static_cast<int>(command);
			break;
		}
		

		case Command::push:
		case Command::pop:

		default:
			assert(false);

		}

		m_code_segment_buffer << this->chack_point;

	}

	return it;

}




Type Parser::find_type(const std::string & type_name)
{
	return type_enum_map.at(type_name);
}


Command Parser::find_command(const std::string & command_name)
{
	return command_enum_map.at(command_name);
}



const std::unordered_map<std::string, Command> Parser::command_enum_map
{

	{ "ASSIGN", Command::assign },
	{ "PRINT", Command::print },
	{ "CMP", Command::cmp },
	{ "JUMP", Command::jump },
	{ "JZ", Command::jz },
	{ "JNZ", Command::jnz },
	{ "JO", Command::jo },
	{ "JNO", Command::jno },
	{ "JC", Command::jc },
	{ "JNC", Command::jnc },
	{ "ADD", Command::add },
	{ "SUB", Command::sub },
	{ "MUL", Command::mul },
	{ "DIV", Command::div },
	{ "MOV", Command::mov },
	{ "AND", Command::and_ },
	{ "OR", Command::or_ },
	{ "XOR", Command::xor_ },
	{ "NOT", Command::not_ },
	{ "CALL", Command::call },
	{ "RET", Command::ret },
	{ "END", Command::end },
	{ "PUSH", Command::push },
	{ "POP", Command::pop },
	{ "LABEL", Command::label },

};

const std::unordered_map<std::string, Type> Parser::type_enum_map
{

	{ "BYTE", Type::byte_type },
	{ "CHAR", Type::char_type },
	{ "WORD", Type::word_type },
	{ "DWORD", Type::dword_type },
	{ "QWORD", Type::qword_type },
};