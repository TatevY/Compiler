#include"Interpreter.h"


Interpreter::Interpreter(Divide_to_Segments div_s)
	:m_cpu{div_s.stack_size()}
{
	this->init(div_s);
}



void Interpreter::run()
{

	while (m_cpu.m_IP<m_instr_table.size())
	{
		
		const auto current_ip = m_cpu.m_IP;
		++m_cpu.m_IP;
		m_instr_table[current_ip]->execute(m_cpu);

	}

}



void Interpreter::init(Divide_to_Segments div_s)
{

	Instruction_list insr_list;
	m_instr_table = insr_list.generate_program(div_s);

}
