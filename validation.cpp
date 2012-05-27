#include <iostream>

#include "validation.h"

#include "dataManipulation.h"

using namespace std;

int Val::inputVal (string input)
{
	if (input == "quit" || input == "quit;")
		return 1;					//return 1 means QUIT.
	if (input[input.size()-1] != ';')
	{
		cout << "  Use: [Num Op Num;]* or" << endl <<"       [Var= Num Op Num;]* or" << endl << "       [Var;] or" << endl << "       [quit] to quit Calculator." << endl;
		return 2;					//return 2 means bad use.
	}


	return 0;						//return 0 means overall input is OK.
}

int sentenceVal (string input)
{
	if (input.find('=',0) != string::npos)
	{
		cout<<"  Syntax Error: Invalid equal sign use!"<<endl;
		return 2;
	}

	//First and last characters can't be multiplication or division signs, and the last character can't be an addition or subtraction sign neither.
	if (input [0] == '*'|| input[0] == '/')
	{
		cout<< "  Syntax Error: Invalid operation input!"<<endl;
		return 2;
	}
	if(input[input.size()-1] == '*' || input[input.size()-1] == '/' || input[input.size()-1] == '+'|| input[input.size()-1] == '-')
	{
		cout<< "  Syntax Error: Invalid operation input!"<<endl;
		return 2;
	}

	//The same rule applies to the end and the start of a sentence inside a parentheses.
	int i = 0;
	while (i < input.size())
	{
		if ((input[i] == '(' && (input[i+1] == '*' || input[i+1] == '/' || input[i+1] == ')')) || (input[i] == ')' && (input[i-1] == '*' || input[i-1] == '/' || input[i-1] == '+' || input[i-1] == '-')))
		{
			cout <<"  Syntax Error: Invalid operation input!"<<endl;
		       	return 2;	
		}
		i++;
	}

	//2 or more operators ina a row, without numbers or variables, are only allowed if they are additions or subtractions.
	i = 0;
	while (i < input.size())
	{
		if ((input[i] == '+' || input[i] == '-') && (input[i+1] == '*' || input[i+1]  == '/'))
		{
			cout << "  Syntax Error: Invalid operation input!"<<endl;
			return 2;
		}
		if ((input[i] == '*' || input[i] == '/') && (input[i+1] == '*' || input[i+1] == '/' || input[i+1] == '+' || input[i+1] == '-'))
		{
			cout << "  Syntax Error: Invalid operation input!"<<endl;
			return 2;
		}
		i++;
	}

	//Parentheses not closed!
	string aux = input;
	aux = DataM::justParentheses(aux);
	int o, c, pos;
	pos = o = c = 0;
	while (pos < aux.size())
	{
		if (aux[pos] == '(')
			o++;
		else
			c++;
		pos++;
	}
	if (o != c)
	{
		cout<< "  Syntax Error: Parentheses not closed properly!"<<endl;
		return 2;
	}
	pos = 0;
	while (aux.size() != 0)
	{
		if (aux[pos] == ')')
		{
			cout<<" Syntax Error: Parentheses not closed properly!"<<endl;
			return 2;
		}
		aux = aux.erase(0,1);
		aux = aux.erase(aux.find(')',0),1);
	}


	return  6;						//return 6 means sentence is valid.
}

int Val::subInputVal (string input)
{
	if (input == "quit" || input == "quit;")
		return 1;					//return 1 means QUIT.

	if (input[1] == '=')
	{
		if (input[0] == '=')
		{
			cout << "  Error: Bad equal sign use!"<<endl;
			return 2;				//return 2 means bad use.
		}
		input = input.substr(2, input.size()-2);
		return sentenceVal (input) + 1;			//return 6+1= 7 means it's an atributtion, and it's valid. 
	}

	return sentenceVal(input);				//return 6 means it's a sentence, and it's valid.
}
