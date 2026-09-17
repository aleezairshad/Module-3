#pragma once
#include <iostream>
#include <vector>
using namespace std;

class TowerOfHanoi
{
private:
	vector<int> pegA; // Vector to represent peg A
	vector<int> pegB; // Vector to represent peg B
	vector<int> pegC; // Vector to represent peg C
	int numberOfDisks; // Number of disks in the Tower of Hanoi

public:
	TowerOfHanoi(); // Constructor to initialize the Tower of Hanoi
	void reset(); // Resets the pegs to the initial state with all disks on peg A
	int getNumberOfDisks() const; // Returns the current number of disks
	void setNumberOfDisks(int n); // Sets the number of disks and resets the pegs
	int getTopPegA() const; // Returns the top disk on peg A, or 0 if peg A is empty
	int getTopPegB() const; // Returns the top disk on peg B, or 0 if peg B is empty
	int getTopPegC() const; // Returns the top disk on peg C, or 0 if peg C is empty
	void moveDisk(char sourcePeg, char targetPeg); // Moves the top disk from the source peg to the target peg if the move is valid
	bool isEmptyPegA() const; // Returns true if peg A is empty, false otherwise
	bool isEmptyPegB() const; // Returns true if peg B is empty, false otherwise
	bool isEmptyPegC() const; // Returns true if peg C is empty, false otherwise
	void displayPegs() const; // Displays the current state of the pegs and disks in a graphical format
};

