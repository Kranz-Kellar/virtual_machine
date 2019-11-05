#include "GRUMachine.h"



GRUMachine::GRUMachine() : stack(), memory(), registers(), isRunning(false)
{
}

void GRUMachine::Init()
{
	printf("Virtual machine start...\n");
	STACK_POINTER = -1;
	isRunning = true;
	instructions[PSH] = &GRUMachine::PSH_Impl;
	instructions[POP] = &GRUMachine::POP_Impl;
	instructions[ADD] = &GRUMachine::ADD_Impl;
	instructions[SUB] = &GRUMachine::SUB_Impl;
	instructions[SET] = &GRUMachine::SET_Impl;
	instructions[HLT] = &GRUMachine::HLT_Impl;

	//Prgram for test
	memory[0] = PSH;
	memory[1] = 1;
	memory[2] = PSH;
	memory[3] = 2;
	memory[4] = ADD;
	memory[5] = POP;
	memory[6] = SET;
	memory[7] = registers[A];
	memory[8] = 5;
	memory[9] = HLT;
}

void GRUMachine::RunMachine()
{
	printf("Running\n");
	while (isRunning) {
		ExecuteInstruction(FetchInstruction());
		PROGRAM_COUNTER++;
	}
	printf("Stop\n");
}


uint32_t GRUMachine::FetchInstruction()
{
	return memory[PROGRAM_COUNTER];
}

void GRUMachine::ExecuteInstruction(uint32_t instruction)
{
	if (instructions[instruction] != nullptr) {
		void(GRUMachine::*Func)() = instructions[instruction];
		(this->*Func)();
		
	}
}

void GRUMachine::PSH_Impl()
{
	stack.Push(memory[++PROGRAM_COUNTER]);
}

void GRUMachine::POP_Impl()
{
	printf("Popped value: %d\n", stack.Pop());
}

void GRUMachine::ADD_Impl()
{
	GetTwoOperandFromStackInToRegisters(A, B);
	registers[A] += registers[B];

	stack.Push(registers[A]);
}

void GRUMachine::SUB_Impl()
{
	GetTwoOperandFromStackInToRegisters(A, B);
	registers[A] *= registers[B];

	stack.Push(registers[A]);
}

void GRUMachine::SET_Impl()
{
	registers[memory[++PROGRAM_COUNTER]] = memory[++PROGRAM_COUNTER];
}

void GRUMachine::HLT_Impl()
{
	isRunning = false;
}

void GRUMachine::GetTwoOperandFromStackInToRegisters(GRURegisters first, GRURegisters second)
{
	registers[first] = stack.Pop();
	registers[second] = stack.Pop();
}
