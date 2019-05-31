#pragma once
#include "Instruction.h"
#include <iostream>

Assign::Assign(const size_t reg, const int val)
	:m_reg{ reg }, m_value{ val } {}

void Assign::execute(CPU & cpu) const
{
	cpu.set_register_value(m_reg, m_value);
}

Print::Print(const size_t reg)
	:m_reg{ reg } {}

void Print::execute(CPU & cpu) const
{
	//	std::cout << cpu.get_register_value(m_reg) << std::endl;
}

Mov::Mov(const size_t left, const size_t right)
	: m_left{ left }, m_right{ right } {}

void Mov::execute(CPU & cpu) const
{
	cpu.mov(m_left, m_right);
}

Cmp::Cmp(const size_t left, const size_t right)
	:ArithmeticInstructions{ left,right } {}

void Cmp::execute(CPU & cpu) const
{
	cpu.cmp(m_left, m_right);
}

Jump::Jump(const size_t new_ip)
	: JumpInstructions{ new_ip - 1 } {}

void Jump::execute(CPU & cpu) const
{
	cpu.set_ip(m_new_ip);
}

Jz::Jz(const size_t new_ip)
	:JumpInstructions{ new_ip - 1 } {}


void Jz::execute(CPU & cpu) const
{
	if (cpu.m_status_reg.ZF)
	{
		cpu.set_ip(m_new_ip);
	}
}

Jnz::Jnz(const size_t new_ip)
	: JumpInstructions{ new_ip - 1 } {}

void Jnz::execute(CPU & cpu) const
{
	if (!cpu.m_status_reg.ZF)
	{
		cpu.set_ip(m_new_ip);
	}
}


Jo::Jo(const size_t new_ip)
	: JumpInstructions{ new_ip - 1 } {}

void Jo::execute(CPU & cpu) const
{
	if (cpu.m_status_reg.OF)
	{
		cpu.set_ip(m_new_ip);
	}
}

Jno::Jno(const size_t new_ip)
	: JumpInstructions{ new_ip - 1 } {}

void Jno::execute(CPU & cpu) const
{
	if (!cpu.m_status_reg.OF)
	{
		cpu.set_ip(m_new_ip);
	}
}

Jc::Jc(const size_t new_ip)
	: JumpInstructions{ new_ip - 1 } {}

void Jc::execute(CPU & cpu) const
{
	if (cpu.m_status_reg.CF)
	{
		cpu.set_ip(m_new_ip);
	}
}

Jnc::Jnc(const size_t new_ip)
	: JumpInstructions{ new_ip - 1 } {}

void Jnc::execute(CPU & cpu) const
{
	if (!cpu.m_status_reg.CF)
	{
		cpu.set_ip(m_new_ip);
	}
}

Add::Add(const size_t left, const size_t right)
	: ArithmeticInstructions{ left, right } {}

void Add::execute(CPU & cpu) const
{
	cpu.add(m_left, m_right);
}

Sub::Sub(const size_t left, const size_t right)
	: ArithmeticInstructions{ left, right } {}

void Sub::execute(CPU & cpu) const
{
	cpu.sub(m_left, m_right);
}

Mul::Mul(const size_t left, const size_t right)
	: ArithmeticInstructions{ left, right } {}

void Mul::execute(CPU & cpu) const
{
	cpu.mul(m_left, m_right);
}

Div::Div(const size_t left, const size_t right)
	: ArithmeticInstructions{ left, right } {}

void Div::execute(CPU & cpu) const
{
	cpu.div(m_left, m_right);
}

And::And(const size_t left, const size_t right)
	: LogicalInstructions{ left, right } {}

void And::execute(CPU & cpu) const
{
	cpu.and_(m_left, m_right);
}

Or::Or(const size_t left, const size_t right)
	: LogicalInstructions{ left, right } {}

void Or::execute(CPU & cpu) const
{
	cpu.or_(m_left, m_right);
}

Xor::Xor(const size_t left, const size_t right)
	: LogicalInstructions{ left, right } {}

void Xor::execute(CPU & cpu) const
{
	cpu.xor_(m_left, m_right);
}



void Label::execute(CPU & cpu) const
{
	std::ignore = cpu;
}



//Not::Not(const size_t val)
//	: OtherLogicalInstructions{val}{}
//
//void Not::execute(CPU & cpu) const
//{
//	cpu.not_(val);
//}
//
//Shl::Shl(const size_t val)
//	: OtherLogicalInstructions{ val } {}
//
//void Shl::execute(CPU & cpu) const
//{
//	cpu.shl(val)
//}
//
//Shr::Shr(const size_t val)
//	: OtherLogicalInstructions{ val } {}
//
//void Shr::execute(CPU & cpu) const
//{
//}
//





Call::Call(const size_t new_ip)
	:JumpInstructions{ new_ip } {}

void Call::execute(CPU & cpu) const
{
	std::cout << "call" << std::endl;
	cpu.stack_push(RegSize::R_Size::W, cpu.get_ip());
	cpu.set_ip(m_new_ip);
}

Ret::Ret(const size_t new_ip)
	:JumpInstructions{ new_ip } {}

void Ret::execute(CPU & cpu) const
{
	cpu.set_ip(cpu.stack_pop(RegSize::R_Size::W));
}

void End::execute(CPU & cpu) const
{
	cpu.set_ip(std::numeric_limits<decltype(cpu.m_IP)>::max());
	std::cout << "End" << std::endl;
}

Push::Push(RegSize::R_Size reg_size, size_t reg_id)
	: m_reg_size(reg_size)
	, m_reg_id(reg_id) {}


void Push::execute(CPU & cpu) const
{
	cpu.stack_push(m_reg_size, cpu.get_register_value(m_reg_id));
}


Pop::Pop(RegSize::R_Size reg_size, size_t reg_id)
	: m_reg_size(reg_size)
	, m_reg_id(reg_id) {}


void Pop::execute(CPU & cpu) const
{
	cpu.set_register_value(m_reg_id, cpu.stack_pop(m_reg_size));
}
