#pragma once

#pragma once
#include<string>
#include <unordered_map>
#include"Status Registers.h"
#include"Register Size.h"



class CPU
{
public:
	bool is_add_overflow(const size_t left, const size_t right) noexcept;
	bool is_add_underflow(const size_t left, const size_t right) noexcept;
	bool is_sub_overflow(const size_t left, const size_t right) noexcept;
	bool is_sub_underflow(const size_t left, const size_t right) noexcept;
	bool is_mul_overflow(const size_t left, const size_t right) noexcept;
	bool is_mul_underflow(const size_t left, const size_t right) noexcept;


public:
	void add(const size_t left, const size_t right);
	void sub(const size_t left, const size_t right);
	void mul(const size_t left, const size_t right);
	void div(const size_t left, const size_t right);
	void and_(const size_t left, const size_t right);
	void or_(const size_t left, const size_t right);
	void xor_(const size_t left, const size_t right);
	void mov(const size_t left, const size_t right);
	void cmp(const size_t left, const size_t right);
	//	void not_(const size_t val);
	//	void shl(const size_t val);
	//	void shr(const size_t val);


	int get_register_value(const size_t id);
	void set_register_value(const size_t id, const int value);
	void set_ip(const std::size_t new_ip);
	size_t get_ip() const;
	void stack_push(const RegSize::R_Size type_size, const int64_t value);
	int64_t stack_pop(const RegSize::R_Size type_size);



public:
	CPU();
	~CPU();
	CPU(const CPU&) = delete;
	CPU& operator=(const CPU&) = delete;


public:
	size_t m_IP;
	StatusRegister m_status_reg;


private:
	std::vector<int> m_REG;
	char* const m_call_stack;
	char* m_SP;
	static constexpr auto registers_count = 10u;
	static constexpr std::size_t m_stack_size = 255u;
};
