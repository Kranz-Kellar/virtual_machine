#include <stdio.h>

#include "Registers.h"
#include "Instructions.h"

int stack[256];
int registers[NUM_OF_REGISTERS];

#define instructionPointer registers[IP]
#define stackPointer registers[SP]

int fetchNextInstruction();
void executeInstruction(int instruction);

const int program[] = {
		PSH, 5,
		PSH, 6,
		ADD,
		POP,
		SET, IP, -1,
		HLT
};

bool running = true;

int main() {

	stackPointer = -1;

	while (running) {
		executeInstruction(fetchNextInstruction());
		if (running == false) {
			break;
		}

		instructionPointer++;

		printf("%d", instructionPointer);
	}

	return 0;
}

int fetchNextInstruction() {
	return program[instructionPointer];
}

void executeInstruction(int instruction) {
	switch (instruction)
	{
	case HLT:
		running = false;
		break;

	case PSH:
		stackPointer++;
		stack[stackPointer] = program[++instructionPointer];
		break;

	case POP:
		registers[A] = stack[stackPointer--];

		printf("Popped value: %d", registers[A]);
		break;

	case ADD:
		registers[A] = stack[stackPointer--];
		registers[B] = stack[stackPointer--];

		registers[A] = registers[A] + registers[B];
		stackPointer++;
		stack[stackPointer] = registers[A];
		break;

	case SET:
		registers[A] = program[++instructionPointer];
		registers[registers[A]] = program[++instructionPointer];

		break;
	}
}