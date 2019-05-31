#include"Compiler.h"

Compiler::Compiler(std::string file_name)
	:m_file_name{ file_name }

{}

Divide_to_Segments Compiler::compile_code() const
{
	File f{ std::string{m_file_name} };
	const auto txt_code = f.read_in();
	Parser parser{ txt_code };
	return parser.div_to_segments();
}
