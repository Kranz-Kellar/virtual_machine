#pragma once
#include <stdio.h>
#include <stdint.h>
#include <map>
#include "IVirtualMachine.h"
#include "Stack.h"
#include <functional>

#define STACK_SIZE 16
#define MAX_MEMORY_SIZE 512
#define STACK_POINTER registers[SP]
#define PROGRAM_COUNTER registers[PC]

using namespace std;


class GRUMachine : public IVirtualMachine
{
public:
	typedef enum {
		PSH,
		POP,
		ADD,
		SUB,
		SET,
		HLT
	} InstructionSet;

	typedef enum {
		A, B, C, D, E, F, SP, PC,
		NUM_OF_REGISTERS
	} GRURegisters;

	GRUMachine();
	void Init() override;
	void RunMachine() override;
	uint32_t FetchInstruction() override;
	void ExecuteInstruction(uint32_t instruction) override;

private:

	int16_t registers[NUM_OF_REGISTERS];
	Stack<int16_t, STACK_SIZE> stack;
	map<uint32_t, void(GRUMachine::*)()> instructions;
	int memory[512];

	bool isRunning;

	void PSH_Impl();
	void POP_Impl();
	void ADD_Impl();
	void SUB_Impl();
	void SET_Impl();
	void HLT_Impl();

	void GetTwoOperandFromStackInToRegisters(GRURegisters first, GRURegisters second);
};



