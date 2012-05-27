UFRJ
Electronics and Computational Engeneering
Programming Languages Course

Group:
Gabriel Bastos
Luiz Felipe Santos Vecchietti
Luiz Henrique Vasconcelos
Natália França
Pedro Goñi Coelho
Phellipe Moura

1)Install:
In a Unix machine, simple run the line "make" in the terminal, making sure all the files are in the current folder. You can use other C++ compilers. The "makefile" is editable to that end.


2)Program:
A command line calculator, written in C++.


3)Operations:
The program suports the following operations:

-Addition; 
-Subtraction;
-Multiplication;
-Division (Division by zero -an undifined operation- results in zero. The User is told to disconsider the result);
-Precedence (by parentheses. Brackets and curly brackets are not suported);
-Attribution (by the equal sign. Only one attribution per sentence. Variables in this version can only have one character).


4)Use:
A sentence with any number of valid opererations can be entered, as long as it is terminated by a semicolon.
	Eg: >>2 + 2 (4) / (5 * 7 - 2);

The result of any valid sentence can be attributed to a variable.
	Eg: >>x = 2 + 2 (4) / (5 * 7 - 2);

Multiple sentences can be entered in line, if they are separated by semicolons. It is only displayed the result of the last sentence.
	Eg: >>2 + 2; 4 (2); 5 / 2;
	      2.5	

Also, variables created in previous sentences can be viewed entering it's name.
	Eg: >>x;
	      x=2.24242

And can be used in following sentences.
	Eg: >>y = x + 2;
	      y=4.24242

To quit the Calculator simply enter the line "quit".