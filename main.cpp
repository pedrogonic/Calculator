#include <iostream>

#include "op.h"

#include "dataManipulation.h"

#include "validation.h"

#include "memoryHandling.h"

using namespace std;

int main()
{
	Mem::open();	
	string input;
	int err = 0;
	while (err != 1)
	{
		input = DataM::getUserInput();
		input = DataM::delSpaces(input);
		input = DataM::insMult(input);
		err = Val::inputVal (input);
		if (err == 0)
			err = Op::run(input);	
	}
	Mem::close();
	return 0;
}
