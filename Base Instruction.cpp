#include "Base Instruction.h"


ArithmeticInstructions::ArithmeticInstructions(const size_t left, const size_t right)
	:m_left{ left }, m_right{ right } {}


JumpInstructions::JumpInstructions(const size_t new_ip)
	: m_new_ip{ new_ip } {}


LogicalInstructions::LogicalInstructions(const size_t left, const size_t right)
	: m_left{ left }, m_right{ right } {}


OtherLogicalInstructions::OtherLogicalInstructions(const size_t val)
	: m_val{ val } {}
