#pragma once

#include"Instruction.h"
#include"Divide  to Segments.h"
#include"Commands and types .h"
#include"Utility.h"

#include<assert.h>
#include<string>
#include<regex>
#include<forward_list>


using TInstructionTable = std::vector<std::unique_ptr<BaseInstruction>>;


class Instruction_list
{


public:
	Instruction_list()
		:m_label_id_to_label_map()
		,m_label_to_id_map(){}

	TInstructionTable generate_program(const Divide_to_Segments &code);


private:

	void make_jumps(TInstructionTable & program);
	std::unique_ptr<BaseInstruction> create_instruction_print(const size_t id);
	static std::unique_ptr<BaseInstruction> create_instruction_assign(const size_t id, const int value);


	template <class T>
	static std::unique_ptr<BaseInstruction> create_instruction_ls(const size_t reg_size, const size_t reg_id);

	template <class T, class... TArgs>
	std::unique_ptr<BaseInstruction> create_instruction_jump(const int label_id);




	std::unordered_map<int, std::forward_list<JumpInstructions*>> m_label_id_to_label_map;
	std::unordered_map<Label*, int> m_label_to_id_map;

};

template<class T>
inline std::unique_ptr<BaseInstruction> Instruction_list::create_instruction_ls(const size_t reg_size, const size_t reg_id)
{
	return std::make_unique<T>(static_cast<RegSize::R_Size>(reg_size), reg_id);
}



template<class T, class ...TArgs>
inline std::unique_ptr<BaseInstruction> Instruction_list::create_instruction_jump(const int label_id)
{
	auto inst = std::make_unique<T>();
	m_label_id_to_label_map[label_id].push_front(inst.get());

	return inst;
}
