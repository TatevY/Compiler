#include "Instruction List.h"

TInstructionTable Instruction_list::generate_program(const Divide_to_Segments & code)
{
	TInstructionTable program;

	auto code_segment = code.code_segment();
	int val = 0;
	while (code_segment >> val)
	{
		std::unique_ptr<BaseInstruction> res = nullptr;
		switch (static_cast<Command>(val))
		{

		case Command::assign:
		{
			int id;	  code_segment >> id;
			int val;  code_segment >> val;

			res = create_instruction_assign(id, val);
			break;
		}

		case Command::print:
		{
			int id;
			code_segment >> id;
			res = create_instruction_print(id);
			break;
		}


		case Command::cmp:
		{
			int id;
			code_segment >> id;
			int id1;
			code_segment >> id1;
			res = std::make_unique<Cmp>(id, id1);
			break;
		}


		case Command::jump:
		{
			int id;
			code_segment >> id;
			res = create_instruction_jump<Jump>(id);
			break;
		}


		case Command::jz:
		{
			int id;
			code_segment >> id;
			res = create_instruction_jump<Jz>(id);
			break;
		}


		case Command::jnz:
		{
			int id;
			code_segment >> id;
			res = create_instruction_jump<Jnz>(id);
			break;
		}


		case Command::jo:
		{
			int id;
			code_segment >> id;
			res = create_instruction_jump<Jo>(id);
			break;
		}


		case Command::jno:
		{
			int id;
			code_segment >> id;
			res = create_instruction_jump<Jno>(id);
			break;
		}


		case Command::jc:
		{
			int id;
			code_segment >> id;
			res = create_instruction_jump<Jc>(id);
			break;
		}


		case Command::jnc:
		{
			int id;
			code_segment >> id;
			res = create_instruction_jump<Jnc>(id);
			break;
		}


		case Command::call:
		{
			int id;
			code_segment >> id;
			res = create_instruction_jump<Call>(id);
			break;
		}


		case Command::add:
		{
			int id;
			code_segment >> id;
			int id1;
			code_segment >> id1;
			res = std::make_unique<Add>(id, id1);
			break;
		}


		case Command::sub:
		{
			int id;
			code_segment >> id;
			int id1;
			code_segment >> id1;
			res = std::make_unique<Sub>(id, id1);
			break;
		}


		case Command::mul:
		{
			int id;
			code_segment >> id;
			int id1;
			code_segment >> id1;
			res = std::make_unique<Mul>(id, id1);
			break;
		}


		case Command::div:
		{
			int id;
			code_segment >> id;
			int id1;
			code_segment >> id1;
			res = std::make_unique<Div>(id, id1);
			break;
		}


		case Command::and_:
		{
			int id;
			code_segment >> id;
			int id1;
			code_segment >> id1;
			res = std::make_unique<And>(id, id1);
			break;
		}


		case Command::or_:
		{
			int id;
			code_segment >> id;
			int id1;
			code_segment >> id1;
			res = std::make_unique<Or>(id, id1);
			break;
		}


		case Command::xor_:
		{
			int id;
			code_segment >> id;
			int id1;
			code_segment >> id1;
			res = std::make_unique<Xor>(id, id1);
			break;
		}


		case Command::mov:
		{
			int id;
			code_segment >> id;
			int id1;
			code_segment >> id1;
			res = std::make_unique<Mov>(id, id1);
			break;
		}


		case Command::ret:
			res = std::make_unique<Ret>();
			break;

		case Command::end:
			res = std::make_unique<End>();
			break;

		//case Command::push:
		//{
		//	int reg_size;
		//	code_segment >> reg_size;
		//	int reg_id;
		//	code_segment >> reg_id;
		//	res = create_instruction_ls<Push>(reg_size, reg_id);
		//	break;
		//}


		//case Command::pop:
		//{
		//	int reg_size;
		//	code_segment >> reg_size;
		//	int reg_id;
		//	code_segment >> reg_id;
		//	res = create_instruction_ls<Pop>(reg_size, reg_id);
		//	break;
		//}


		case Command::label:
		{
			
			auto inst = std::make_unique<Label>();

			assert(inst);

			int id;
			code_segment >> id;
			m_label_to_id_map[inst.get()] = id;

			res = std::move(inst);
			break;
		}

		default:
			assert(false);

		}
		int chack_point;
		code_segment >> chack_point;
		assert(std::numeric_limits<int>::max() == chack_point);

		program.push_back(std::move(res));
	}

	make_jumps(program);
	return program;

}




void Instruction_list::make_jumps(TInstructionTable & program){}


std::unique_ptr<BaseInstruction> Instruction_list::create_instruction_print(const size_t id)
{
	return std::unique_ptr<BaseInstruction>(std::make_unique<Print>(id));
}



std::unique_ptr<BaseInstruction> Instruction_list::create_instruction_assign(const size_t id, const int value)
{
	return std::unique_ptr<BaseInstruction>(
		std::make_unique<Assign>(id, value));
}

