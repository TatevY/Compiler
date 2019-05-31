#pragma once

#include"Base Instruction.h"
#include"Status Registers.h"
#include"CPU.h"

class Assign :public BaseInstruction
{
public:
	Assign(const size_t reg, const int val);
	~Assign() = default;
	void execute(CPU &cpu) const override;

private:
	const size_t m_reg;
	const int m_value;
};


class Print :public BaseInstruction
{
public:
	Print(const size_t reg);
	~Print() = default;
	void execute(CPU &cpu) const override;

private:
	const size_t m_reg;
};


class Mov :public BaseInstruction
{
public:
	Mov(const size_t left, const size_t right);
	~Mov() = default;
	void execute(CPU &cpu) const override;

private:
	const size_t m_left;
	const size_t m_right;
};


class Cmp :public ArithmeticInstructions
{
public:
	Cmp(const size_t left, const size_t right);
	~Cmp() = default;
	void execute(CPU &cpu) const override;
};


class Jump :public JumpInstructions
{
public:
	Jump(const size_t new_ip);
	~Jump() = default;
	void execute(CPU &cpu) const override;
};


class Jz :public JumpInstructions
{
public:
	Jz(const size_t new_ip);
	~Jz() = default;
	void execute(CPU &cpu) const override;
};


class Jnz :public JumpInstructions
{
public:
	Jnz(const size_t new_ip);
	~Jnz() = default;
	void execute(CPU &cpu) const override;
};


class Jo :public JumpInstructions
{
public:
	Jo(const size_t new_ip);
	~Jo() = default;
	void execute(CPU &cpu) const override;
};


class Jno :public JumpInstructions
{
public:
	Jno(const size_t new_ip);
	~Jno() = default;
	void execute(CPU &cpu) const override;
};


class Jc :public JumpInstructions
{
public:
	Jc(const size_t new_ip);
	~Jc() = default;
	void execute(CPU &cpu) const override;
};



class Jnc :public JumpInstructions
{
public:
	Jnc(const size_t new_ip);
	~Jnc() = default;
	void execute(CPU &cpu) const override;
};


class Add :public ArithmeticInstructions
{
public:
	Add(const size_t left, const size_t right);
	~Add() = default;
	void execute(CPU &cpu) const override;
};


class Sub :public ArithmeticInstructions
{
public:
	Sub(const size_t left, const size_t right);
	~Sub() = default;
	void execute(CPU &cpu) const override;
};


class Mul :public ArithmeticInstructions
{
public:
	Mul(const size_t left, const size_t right);
	~Mul() = default;
	void execute(CPU &cpu) const override;
};


class Div :public ArithmeticInstructions
{
public:
	Div(const size_t left, const size_t right);
	~Div() = default;
	void execute(CPU &cpu) const override;
};


class And :public LogicalInstructions
{
public:
	And(const size_t left, const size_t right);
	~And() = default;
	void execute(CPU &cpu) const override;
};


class Or :public LogicalInstructions
{
public:
	Or(const size_t left, const size_t right);
	~Or() = default;
	void execute(CPU &cpu) const override;
};


class Xor :public LogicalInstructions
{
public:
	Xor(const size_t left, const size_t right);
	~Xor() = default;
	void execute(CPU &cpu) const override;
};


//class Not :public OtherLogicalInstructions
//{
//
//public:
//	Not(const size_t left, const size_t right);
//	~Not() = default;
//	void execute(CPU &cpu) const override;
//};

//
//class Shl :public OtherLogicalInstructions
//{
//public:
//	Shl(const size_t left, const size_t right);
//	~Shl() = default;
//	void execute(CPU &cpu) const override;
//};
//
//
//class Shr :public OtherLogicalInstructions
//{
//public:
//	Shr(const size_t left, const size_t right);
//	~Shr() = default;
//	void execute(CPU &cpu) const override;
//};


class Label :public BaseInstruction
{
public:
	Label() = default;
	~Label() = default;
	void execute(CPU& cpu) const override;
};



class Call :public JumpInstructions
{
public:
	Call(size_t new_ip = 0);
	~Call() = default;
	void execute(CPU& cpu) const override;
};


class Ret :public JumpInstructions
{
public:
	Ret(const size_t new_ip);
	~Ret() = default;
	void execute(CPU& cpu) const override;
};



class End :public BaseInstruction
{
public:
	End() = default;
	~End() = default;
	void execute(CPU& cpu) const override;
};



class Push : public BaseInstruction
{
public:
	Push(RegSize::R_Size reg_size, size_t reg_id);
	~Push() = default;
	void execute(CPU& cpu) const override;

private:
	const RegSize::R_Size  m_reg_size;
	const size_t m_reg_id;
};


class Pop : public BaseInstruction
{
public:
	Pop(RegSize::R_Size reg_size, size_t reg_id);
	~Pop() = default;
	void execute(CPU& cpu) const override;

private:
	const RegSize::R_Size m_reg_size;
	const size_t m_reg_id;
};
