#include <iostream>

#include <string>

#include <math.h>

#include "dataManipulation.h"

using namespace std;

string DataM::getUserInput()
{
	string input;
	cout << ">>";
	getline (cin, input);
	return input;
}

string DataM::subInput(string input)
{
	input = input.substr (0, input.find(';',0));
	return input;
}

string DataM::rmSubInput(string input)
{
	int i = input.find(';',0) + 1;
	input = input.erase (0,i);
	return input;
}

string DataM::delSpaces (string input)
{
	while (input.find(' ',0) != string::npos)
		input.erase( input.find(' ',0), 1);
	return input;
}

string DataM::insMult (string input)
{
	if (input.find('(',1) != string::npos)
	{
		int noMultPos = input.find('(',1);
		do{
			if (input.find_last_of("/*+-;(",noMultPos-1) != noMultPos-1)
				{
					input = input.insert(noMultPos,1,'*');
					noMultPos = input.find ('(',noMultPos+2);
				}
			else
				noMultPos = input.find('(',noMultPos+1);
      		   }while(noMultPos != string::npos);
	}

	if (input.find(')',1) != string::npos)
	{
		int noMultPos = input.find(')',1);
			do{
				if (input.find_first_of("/*+-;)",noMultPos+1) != noMultPos+1)
				{
					input = input.insert(noMultPos+1,1,'*');
					noMultPos = input.find (')',noMultPos+2);
				}	
			else
				noMultPos = input.find(')',noMultPos+1);
			}while(noMultPos != string::npos);
	}
	
	int varPos = 1;
	while (varPos < input.size())
	{
		if (((input[varPos] >= 'a' && input[varPos] <= 'z') || (input[varPos] >= 'A' && input[varPos] <= 'Z'))&& (input[varPos-1] >= '0' && input[varPos-1] <= '9'))
			input.insert (varPos,1,'*');
		varPos++;	
	}
	return input;
}

string DataM::justParentheses(string input)
{
	int i = 0;
	while (i < input.size())
	{
		if (input[i] != '(' && input[i] != ')')
			input[i] = ' ';
		i++;
	}
	input = DataM::delSpaces(input);
	return input;
}

double DataM::stringToDouble(string input,int s,int e)
{		
	double outNum = 0;
	int ppos, i, found;
	if (s>0)
		input = input.erase(0,s);
	else
	{	
	if (e<input.size())
		input = input.erase(e+1,input.size());
	}
	ppos = input.size();
	i = input.size();
	found = 0;
	if (input.find('.',0) != string::npos)
	{
		ppos = input.find('.',0);
		i--;
	}
	for(; i > -1; i--)
	{
		if (i == ppos)
			found = 1;
		else 
			if (i == 0 && input[i] == '-')
				outNum *= (-1);
		else
			outNum +=  double((input[i] - '0') * pow(10, (ppos-i-found)));
	}
	return outNum;
}
