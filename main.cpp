#include <stdio.h>
#include "IVirtualMachine.h"
#include "GRUMachine.h"


int main() {

	IVirtualMachine* machine = new GRUMachine();
	machine->Init();
	machine->RunMachine();

	return 0;
}
