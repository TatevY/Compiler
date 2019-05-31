#include"CPU.h"
#include <cassert>
#include <string>


auto CPU::is_add_overflow(const size_t left, const size_t right) noexcept->bool
{
	return(m_REG[right] > 0) &&
		(m_REG[left] > std::numeric_limits<int>::max() - m_REG[right]);
}


auto CPU::is_add_underflow(const size_t left, const size_t right) noexcept->bool
{
	return(m_REG[right] < 0) &&
		(m_REG[left] < std::numeric_limits<int>::min() - m_REG[right]);
}



auto CPU::is_sub_overflow(const size_t left, const size_t right) noexcept->bool
{
	return(m_REG[right] < 0) &&
		(m_REG[left] > std::numeric_limits<int>::max() + m_REG[right]);
}



auto CPU::is_sub_underflow(const size_t left, const size_t right) noexcept->bool
{
	return(m_REG[right] > 0) &&
		(m_REG[left] < std::numeric_limits<int>::min() + m_REG[right]);
}



auto CPU::is_mul_overflow(const size_t left, const size_t right) noexcept->bool
{
	return(m_REG[left] > std::numeric_limits<int>::max() / m_REG[right])
		|| ((m_REG[left] == -1) && (m_REG[right] == std::numeric_limits<int>::min()));
}


auto CPU::is_mul_underflow(const size_t left, const size_t right) noexcept->bool
{
	return(m_REG[left] < std::numeric_limits<int>::min() / m_REG[right])
		|| ((m_REG[left] == -1) && (m_REG[right] == std::numeric_limits<int>::min()));
}


void CPU::add(const size_t left, const size_t right)
{
	m_status_reg.OF = is_add_overflow(left, right) || is_add_underflow(left, right);
	m_REG[left] += m_REG[right];
	m_status_reg.ZF = (m_REG[left] == 0);
	m_status_reg.CF = ((m_REG[left] >> 31) & 1u);
}


void CPU::sub(const size_t left, const size_t right)
{
	m_status_reg.OF = is_sub_overflow(left, right) || is_sub_underflow(left, right);
	m_REG[left] -= m_REG[right];
	m_status_reg.ZF = (m_REG[left] == 0);
	m_status_reg.CF = ((m_REG[left] >> 31) & 1u);
}



void CPU::mul(const size_t left, const size_t right)
{
	m_status_reg.OF = is_mul_overflow(left, right) || is_mul_underflow(left, right);
	m_REG[left] *= m_REG[right];
	m_status_reg.ZF = (m_REG[left] == 0);
	m_status_reg.CF = ((m_REG[left] >> 31) & 1u);
}



void CPU::div(const size_t left, const size_t right)
{
	m_status_reg.OF = false;
	m_REG[left] /= m_REG[right];
	m_status_reg.ZF = (m_REG[left] == 0);
	m_status_reg.CF = ((m_REG[left] >> 31) & 1u);
}



void CPU::and_(const size_t left, const size_t right)
{
	m_status_reg.OF = false;
	m_REG[left] &= m_REG[right];
	m_status_reg.ZF = (m_REG[left] == 0);
	m_status_reg.CF = ((m_REG[left] >> 31) & 1u);
}



void CPU::or_(const size_t left, const size_t right)
{
	m_status_reg.OF = false;
	m_REG[left] |= m_REG[right];
	m_status_reg.ZF = (m_REG[left] == 0);
	m_status_reg.CF = ((m_REG[left] >> 31) & 1u);
}


void CPU::xor_(const size_t left, const size_t right)
{
	m_status_reg.OF = false;
	m_REG[left] ^= m_REG[right];
	m_status_reg.ZF = (m_REG[left] == 0);
	m_status_reg.CF = ((m_REG[left] >> 31) & 1u);
}



void CPU::cmp(const size_t left, const size_t right)
{
	m_status_reg.OF = is_sub_overflow(left, right) || is_sub_underflow(left, right);
	auto res = m_REG[left] - m_REG[right];
	m_status_reg.ZF = (res == 0);
	m_status_reg.CF = ((res >> 31) & 1u);
}


//void CPU::mov(const size_t left, const size_t right)
//{
//	m_REG[left] = m_REG[right];
//}
//
//
//
//void CPU::not_(const size_t val)
//{
//	m_REG[val] = !m_REG[val];
//}
//
//
//
//void CPU::shl(const size_t val)
//{
//	m_REG[val] >> m_REG[val];
//}
//
//
//void CPU::shr(const size_t val)
//{
//	m_REG[val] << m_REG[val];
//}



void CPU::mov(const size_t left, const size_t right)
{
	m_REG[left] = m_REG[right];
}


auto CPU::get_register_value(const size_t id) -> int
{
	return m_REG.at(id);
}



void CPU::set_register_value(const size_t id, const int value)
{
	m_REG[id] = value;
}



void CPU::set_ip(const std::size_t new_ip)
{
	m_IP = new_ip;
}

size_t CPU::get_ip() const
{
	return m_IP;
}



void CPU::stack_push(const RegSize::R_Size type_size, const int64_t value)
{
	auto load_in_stack = [this](const auto val)
	{
		using type = decltype(val);
		type tmp = static_cast<type>(val);
		m_SP -= sizeof(type);
		std::memcpy(m_SP, &tmp, sizeof(type));
	};

	switch (type_size)
	{
	case RegSize::R_Size::B:
		load_in_stack(static_cast<int8_t>(value));
		break;
	case RegSize::R_Size::W:
		load_in_stack(static_cast<int16_t>(value));
		break;
	case RegSize::R_Size::DB:
		load_in_stack(static_cast<int32_t>(value));
		break;
	case RegSize::R_Size::DW:
		load_in_stack(static_cast<int64_t>(value));
		break;
	default:
		assert(false);
	}
}


int64_t CPU::stack_pop(const RegSize::R_Size type_size)
{
	switch (type_size)
	{
	case RegSize::R_Size::B:
	{
		int8_t tmp{ 0 };
		std::memcpy(&tmp, m_SP, sizeof(int8_t));
		m_SP += sizeof(int8_t);
		return tmp;
	}
	case RegSize::R_Size::W:
	{
		int16_t tmp{ 0 };
		std::memcpy(&tmp, m_SP, sizeof(int16_t));
		m_SP += sizeof(int16_t);
		return tmp;
	}
	case RegSize::R_Size::DB:
	{
		int32_t tmp{ 0 };
		std::memcpy(&tmp, m_SP, sizeof(int32_t));
		m_SP += sizeof(int32_t);
		return tmp;
	}
	case RegSize::R_Size::DW:
	{
		int64_t tmp{ 0 };
		std::memcpy(&tmp, m_SP, sizeof(int64_t));
		m_SP += sizeof(int64_t);
		return tmp;
	}
	default:
		assert(false);
	}
	return {};
}



CPU::CPU()
	:m_IP{ 0 }
	, m_status_reg{}
	, m_call_stack{ new char[m_stack_size] }
	, m_SP{ m_call_stack + m_stack_size } {}



CPU::~CPU()
{
	delete[] m_call_stack;
}
