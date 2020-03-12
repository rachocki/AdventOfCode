#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

/*
Position 0: Opcode.
	1 = Read the numbers from index of positions 1 and 2, add them, and store the sum in the index of position 3
	2 = Same as 1, but multiply instead of adding
	99 = Halt
	Else = Error
Once the operation is done, step forward to next operation (i.e. add 4 to index)

Once you have a working computer, the first step is to restore the gravity assist program (your puzzle input) to the
"1202 program alarm" state it had just before the last computer caught fire. To do this, before running the program,
replace position 1 with the value 12 and replace position 2 with the value 2. What value is left at position 0 after
the program halts?
*/

int main() {
	int index = 0;
	int placeholder;
	int orig3;
	std::string prog;
	std::vector<int> progVec;
	bool checkMemInBounds(int loc, vector<int> vec);
	//Read in program input to a string. From there it can be parsed into the vector as ints via stringstream.
	cout << "ENTER PROGRAM >> ";
	getline(cin, prog);
	//replaces commas with whitespace so stringstream delimiting is easier
	size_t pos;
	while ((pos = prog.find(",")) != std::string::npos) {
		prog.replace(pos, 1, " ");
	}
	istringstream progstream(prog);
	while (!progstream.eof()) {
		progstream >> placeholder;
		progVec.push_back(placeholder); 
	}
	
    //Loop through program: Start index at 0, read opcode, carry out operation. 
	//If 1 or 2, do those. If 99 exit. Else exit and print an error code.

	while (index < progVec.size())
	{
		switch (progVec[index])
		{
		case 1:
			//ADDITION. Checks if memory locations are in bounds. If not, 
			if (checkMemInBounds(progVec[index + 1], progVec) && checkMemInBounds(progVec[index + 2], progVec) && checkMemInBounds(progVec[index + 3], progVec)){
				cout << "ADD " << progVec[progVec[index + 1]] << " + " << progVec[progVec[index + 2]] << " -> ";
				orig3 = progVec[progVec[index + 3]];
				progVec[progVec[index + 3]] = progVec[progVec[index + 1]] + progVec[progVec[index + 2]];
				cout << "SUM " << progVec[orig3] << " -> ";
				index += 4;
			}
			else {
				cout << "MEMORY OUT OF BOUNDS; TERMINATING PROGRAM."; 
				index = progVec.size() + 1; // TODO just asking for hacks. find a better way to do this.
			}
			break;
		case 2:
			//do mutliplication TODO SOMETHING WRONG HERE, result is being calculated correctly and stored at the correct index, but it isn't printing correctly.
			if (checkMemInBounds(progVec[index + 1], progVec) && checkMemInBounds(progVec[index + 2], progVec) && checkMemInBounds(progVec[index + 3], progVec)) {
				cout << "MULTIPLY " << progVec[progVec[index + 1]] << " * " << progVec[progVec[index + 2]] << " -> ";
				orig3 = progVec[progVec[index + 3]];
				(progVec[progVec[index + 3]]) = (progVec[progVec[index + 1]]) * (progVec[progVec[index + 2]]);
				cout << "PRODUCT " << progVec[orig3] << " -> ";
				index += 4;
			}
			else {
				cout << "MEMORY OUT OF BOUNDS; TERMINATING PROGRAM.";
				index = progVec.size() + 1; // TODO just asking for hacks. find a better way to do this.
			}
			break;
		case 99:
			cout << "TERMINATION SYMBOL FOUND; END PROGRAM. ";
			index = progVec.size() + 1; // TODO just asking for hacks. find a better way to do this.
			break;
		default:
			cout << "ERROR: UNKNOWN SYMBOL FOUND; TERMINATING PROGRAM. ";
			index = progVec.size() + 1; //ditto
			//error
			break;
		}
	}
	index = 0;
	while (index < progVec.size()) {
		cout << progVec[index] << ","; //TODO don't print comma after end of last memory value. Minor, cosmetic change.
		index++;
	}
}

bool checkMemInBounds(int loc, vector<int> vec) {
	if (loc < vec.size() && loc >= 0) {
		return true;
	}
	else {
		return false;
	}
}