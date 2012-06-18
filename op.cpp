#include <iostream>

#include <sstream>

#include <string>

#include <stdlib.h>

#include <stdio.h>

#include "op.h"

#include "dataManipulation.h"

#include "validation.h"

#include "memoryHandling.h"

using namespace std;


double operation (char op, double a, double b) 						//Check which operation and return its result.
{
	if (op == '*')
		return a*b;
	if (op == '/')
	{
		if(b==0) 
		{
			cout<< "  Oh God! You've just divided by zero, didn't you?"<<endl;
			return 0;
		}
		return a/b;
	}
	if (op == '+')
		return a+b;
	if (op == '-')
		return a-b;
}

string operate(string input)
{
	double a, b,c;
	stringstream output;
	char op;
	int opPos;
	string var;
	//change back the "#" to the minus sign "-"

	if (input.find('*',0) != string::npos)
		opPos = input.find('*',0);
	if (input.find('/',0) != string::npos)
		opPos = input.find('/',0);
	if (input.find('+',0) != string::npos)
		opPos = input.find('+',0);
	if (input.find('-',0) != string::npos)
		opPos = input.find('-',0);
        if (input[opPos+1] != '#'&&(input[opPos+1] < '0'|| input[opPos+1] > '9'))
         {       
                 var = input;
		 var.erase(0,opPos+1);
		 var = Mem::search (var);
		 if (var == "error")
			 return "error";
		 input.erase(opPos+1,input.size()-opPos);
		 input.insert(opPos+1,var);
         }
	if (input[0] != '#' &&(input[0] < '0'||input[0] > '9'))
	{
		var = input;
		var.erase(opPos,var.size()-opPos+1);
		var = Mem::search (var);
		if (var == "error")
			return "error";
		input.erase(0,opPos);
		input.insert(0,var);
	}
        if (input.find('*',0) != string::npos)
                 opPos = input.find('*',0);
         if (input.find('/',0) != string::npos)
                 opPos = input.find('/',0);
         if (input.find('+',0) != string::npos)
                 opPos = input.find('+',0);
         if (input.find('-',0) != string::npos)
                 opPos = input.find('-',0);
	while (input.find('#',0) != string::npos)
	{
		int hashPos = input.find('#',0);
		input[hashPos] = '-';
	}

	op = input[opPos];
	a = DataM::stringToDouble(input,0,opPos-1);
	b = DataM::stringToDouble(input,opPos+1,input.size()-1);
	c = operation(op, a, b);
	input.clear();
	output << c;
	input = output.str();
	if (input[0] == '-')
		input[0] = '#';
	return input;
}

string recursiveHell(string input)
{
	string aux;

	//checking if the first number in the input is negative, substituting the minus sign with a "#", making it easier to differentiate between the minus operation and the negative numbers:
	if (input[0] == '-')
		input[0] = '#';
	
	if (input[0] == '+')
		input.erase(0,1);				//Plus sign in the first position means positive. Delete the sign.

	//Getting rid of the parentheses, running the function recursevely to operate around them:
	while (input.find('(',0) != string::npos)
	{
		int parpos, otherpar, openpar;
		aux = input;
		parpos = input.rfind(')',input.size());
		otherpar = parpos;
		openpar = input.rfind('(',parpos);
		while ((input.rfind(')',otherpar-1) != string::npos) && (input.rfind(')',otherpar-1) >= (input.rfind('(',openpar))))
		{
			otherpar = input.rfind(')',otherpar-1);
			openpar = input.rfind('(',openpar-1);
		}
		aux = aux.erase(parpos,aux.size());
		aux = aux.erase(0,openpar+1);
		aux = recursiveHell (aux);

		input = input.erase(openpar,parpos-openpar+1);
		input = input.insert(openpar,aux);
	}

	//Operations part:
	int op, opprev, oppos;
	opprev = -1;
	oppos = input.size();

	//interpreting which operation, considering the operations precedences:
	if (input.rfind('/') != string::npos)
		op = input.rfind('/');
	else
		if (input.rfind('*') != string::npos)
			op = input.rfind('*');
		else
			if (input.rfind('+') != string::npos)
				op = input.rfind('+');
			else
				if (input.rfind('-') != string::npos)
					op = input.rfind('-');

	//getting the selected operation boundaries:
	if (input.find_last_of("*/+-",op-1) != string::npos)
		opprev = input.find_last_of("*/+-",op-1);
	if (input.find_first_of("*/+-",op+1) != string::npos)
		oppos = input.find_first_of("*/+-",op+1);
	
	//erasing the boundaries, running the function recursevely:
	
		//first, the sentences after the boundaries are erased, if they exist (mult and div):
		if (oppos != input.size())
		{
			aux = input;
			aux = aux.erase (oppos, aux.size());
			aux = recursiveHell (aux);
			input = input.erase (0, oppos);
			input = input.insert (0, aux);
			input = recursiveHell (input);
			return input;
		}
	
		//then, the senteces before the boundaries are erased (all ops):
		if (opprev != -1)
		{
			aux = input;
			aux = aux.erase (0, opprev+1);
			aux = recursiveHell (aux);
			input = input.erase (opprev+1, input.size());
			input = input.insert (opprev+1, aux);
			input = recursiveHell (input);
			return input;
		}

	//Operating the numbers:
	if (input.find_first_of("*/+-",0) == string::npos)
	{
		if (input[0] < '0' || input[0] > '9')
			input = Mem::search(input);	
		return input;
	}
	else
		aux = operate (input);

	return aux;
}

int Op::run(string input)
{
	int err = 0;
	string aux = "quit";	

	while (input.size() != 0 && err != 1 && err!= 2 && err != 3)  //err=1 means quit, err=2 means bad sub-input, err=3 means more equal signs in an attribution.
	{
		if (DataM::subInput(input) != "quit")
		{
			aux = DataM::subInput(input);
			err = Val::subInputVal(aux);
		}
		else
			err = Val::subInputVal("quit");
		if (err == 6)				//Sentence code.
		{
			int it = 0;
			while (it<aux.size()&& aux[it] != '+'&&aux[it] != '-'&&aux[it] != '*'&&aux[it] != '/')
			{
				it++;
			}
			if (it == aux.size())
			{
				stringstream buff;
				string value;
				value = Mem::search(aux);
				if (value == "error")
					return 2;
				if (value[0] == '#')
					value[0] = '-';
				buff << aux << "="<<value;
				aux = buff.str();
				cout<<"  "<<aux<<endl;
				return 2;
			}
			else
			{
				aux = recursiveHell(aux);
				if (aux == "error")
					return 2;
				input = DataM::rmSubInput(input); 
			}
		}
		if (err == 7)				//Attribution code. Must create a new variable in the memory, operate just like a sentence, then pass the result in "aux" to the variable.
		{
			int eqPos=0;
			while (aux[eqPos] != '=')
				eqPos++;
			string value, name;
			name = aux;
			value = aux;
			name.erase(eqPos,name.size()-eqPos+1);
			value.erase(0,eqPos+1);
			value = recursiveHell(value);
			if (value == "error")
				return 2;
			Mem::add(name, value);
			aux.replace(2, aux.size()-2,value);			//Temporary! Variables could have longer names!

			input = DataM::rmSubInput(input);
		}
	}
	if (err != 2 && err!= 3)
	{
		if (aux.find('#')!=string::npos)
			aux[aux.find('#')] = '-';		
		cout << "  "<< aux<<endl;
	}
	return err;	
}
