#pragma once
#include <stdint.h>

class IVirtualMachine
{

	

public:
	void virtual Init() = 0;
	void virtual RunMachine() = 0;
	uint32_t virtual FetchInstruction() = 0;
	void virtual ExecuteInstruction(uint32_t instruction) = 0;
	virtual ~IVirtualMachine() {}
};

