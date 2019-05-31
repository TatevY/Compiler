#pragma once

enum class Command
{
	assign,
	print,
	cmp,
	jump,
	jz,
	jnz,
	jo,
	jno,
	jc,
	jnc,
	add,
	sub,
	mul,
	div,
	and_,
	or_,
	xor_,
	not_,
	mov,
	call,
	ret,
	end,
	push,
	pop,
	label,
};


enum  class Type
{
	char_type,
	byte_type,
	word_type,
	dword_type,
	qword_type

};