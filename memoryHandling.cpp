#include <iostream>

#include "memoryHandling.h"

using namespace Mem;

my_var *head;
my_var *last;
my_var *current;

int Mem::open()
{
	head = new my_var;
	head->nm = "head";
	head->val = "head";
	head->prev = NULL;
	last = head;	
//	std::cout << "::WELCOME TO CALCULATOR::"<<endl;
	return 0;
}

int Mem::clear()
{
	if (last->nm != "head")
	{
		while (last->nm != "head")
		{
			current = last;
			last = last->prev;
			delete current;
			std::cout<< "  All variables erased!"<<endl;
			return 0;
		}
	}
	std::cout << "  Memory already empty!"<<endl;
	return 1;
}

int Mem::add(string name, string value)
{
	current = new my_var;
	current->nm = name;
	current->val = value;
	current->prev = last;
	last = current;
	return 0;
}

string Mem::search(string name)
{
	if (last->nm != "head")
	{
		current = last;
		while (current->nm != "head")
		{
			if (current->nm == name)
			{
				return current->val;
			}
			current = current->prev;
		}
	}
	std::cout << "  "<< name <<" Not found!"<<endl;
	return "error";
		
}

int Mem::close()
{
	int err = 0;
	if (last->nm != "head")	
		err = Mem::clear();
	if (err = 0)
		delete head;
	return 0;
}
