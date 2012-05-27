#This is a makefile that installs the Calculator on your computer.
#To install, run "make" on the terminal, making sure that the folder you're on has all the files of the calculator.
#To unistall run "make clean".


all:
	g++ -o Calculator main.cpp op.cpp dataManipulation.cpp validation.cpp memoryHandling.cpp

clean:
	rm Calculator
