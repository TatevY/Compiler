#pragma once
#include "Status Registers.h"
#include "CPU.h"

class BaseInstruction
{
public:
	BaseInstruction() = default;
	~BaseInstruction() = default;
	virtual void execute(CPU &cpu) const = 0;
};


class ArithmeticInstructions : public BaseInstruction
{
public:
	ArithmeticInstructions(const size_t left, const size_t right);

protected:
	const size_t m_left;
	const size_t m_right;
};



class JumpInstructions : public BaseInstruction
{
public:
	JumpInstructions(const size_t new_ip);
	void set_ip(const size_t ip) { m_new_ip = ip; }

protected:
	size_t m_new_ip;
};


class LogicalInstructions :public BaseInstruction
{
public:
	LogicalInstructions(const size_t left, const size_t right);


protected:
	const size_t m_left;
	const size_t m_right;
};


class OtherLogicalInstructions :public BaseInstruction
{
public:
	OtherLogicalInstructions(const size_t val);
protected:
	const size_t m_val;
};