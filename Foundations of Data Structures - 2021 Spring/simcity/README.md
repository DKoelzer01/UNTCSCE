CSCE2110-002
Assignment 1 - SimCity
Group 32
Mackenzie Feilmeier
Daniel Koelzer
Michael Moser
Jacob Woodson

Compiling
Compile the program by running the provided MAKEFILE with the "make" command.
This will compile all .cpp files needed into one output file titled "sim"

Execution
Execute the program by running one of the following lines of code

make run

or

./sim

"make run" will recompile the program if any changes are detected and immediately run the program after compilation is finished.
"./sim" will run the already compiled program regardless of any changes since last compilation.

The program will immediately prompt the user for a config file to load, and re-prompt the user if an invalid file is input.

After simulation has finished, the user will be prompted to view data relevant to a user-defined region bounded by two (x,y) coordinates.
If improper points (out of bounds, impossible shape) are provided, the program will inform the user, and re-prompt until valid input is given.

**BONUS WAS IMPLEMENTED**