#pragma once


#include "CPU.h"
#include "Base Instruction.h"
#include "Divide  to Segments.h"
#include "Instruction List.h"

using TInstructionTable = std::vector<std::unique_ptr<BaseInstruction>>;


class Interpreter
{
public:

	Interpreter(Divide_to_Segments);
	void run();


private:

	void init(Divide_to_Segments);


private:

	CPU m_cpu;
	TInstructionTable m_instr_table;

};
