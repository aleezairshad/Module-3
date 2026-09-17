#include "TowerOfHanoi.h"
#include <string>

// Constructor initializes the number of disks to 0 and clears the pegs
TowerOfHanoi::TowerOfHanoi()
{
	numberOfDisks = 0;
}

// precondition: None
// postcondition: Resets the Tower of Hanoi game by clearing all pegs and placing disks on peg A
void TowerOfHanoi::reset()
{
	const int ONE = 1;
	pegA.clear();
	pegB.clear();
	pegC.clear();
	for (int disk = numberOfDisks; disk >= ONE; --disk)
	{
		pegA.push_back(disk);
	}
}

//precondition: n is a positive integer representing the number of disks
//postcondition: Sets the number of disks and resets the Tower of Hanoi game
void TowerOfHanoi::setNumberOfDisks(int n)
{
	numberOfDisks = n;
	reset();
}

// precondition: None
// postcondition: Returns the current number of disks in the Tower of Hanoi game
int TowerOfHanoi::getNumberOfDisks() const
{
	return numberOfDisks;
}

// precondition: None
// postcondition: Returns the top disk on peg A, or 0 if peg A is empty
int TowerOfHanoi::getTopPegA() const
{
	if (pegA.empty())
	{
		return 0; // Return 0 if peg A is empty
	}
	return pegA.back(); // Return the top disk on peg A
}

// precondition: None
// postcondition: Returns the top disk on peg B, or 0 if peg B is empty
int TowerOfHanoi::getTopPegB() const
{
	if (pegB.empty())
	{
		return 0; // Return 0 if peg B is empty
	}
	return pegB.back(); // Return the top disk on peg B
}

// precondition: None
// postcondition: Returns the top disk on peg C, or 0 if peg C is empty
int TowerOfHanoi::getTopPegC() const
{
	if (pegC.empty())
	{
		return 0; // Return 0 if peg C is empty
	}
	return pegC.back(); // Return the top disk on peg C
}

// precondition: None
// postcondition: Returns true if peg A is empty, false otherwise
bool TowerOfHanoi::isEmptyPegA() const
{
	return pegA.empty();
}

// precondition: None
// postcondition: Returns true if peg B is empty, false otherwise
bool TowerOfHanoi::isEmptyPegB() const
{
	return pegB.empty();
}

// precondition: None
// postcondition: Returns true if peg C is empty, false otherwise
bool TowerOfHanoi::isEmptyPegC() const
{
	return pegC.empty();
}

// precondition: sourcePeg and targetPeg are valid peg identifiers ('A', 'B', or 'C')
// postcondition: Moves the top disk from the source peg to the target peg if the move is valid
void TowerOfHanoi::moveDisk(char sourcePeg, char targetPeg)
{
	vector<int>* source = nullptr; // Pointer to the source peg
	vector<int>* target = nullptr; // Pointer to the target peg
	// Determine the source peg based on the input character
	switch (sourcePeg)
	{
	case 'A':
		source = &pegA;
		break;
	case 'B':
		source = &pegB;
		break;
	case 'C':
		source = &pegC;
		break;
	default:
		return; // Invalid source peg
	}
	// Determine the target peg based on the input character
	switch (targetPeg)
	{
	case 'A':
		target = &pegA;
		break;
	case 'B':
		target = &pegB;
		break;
	case 'C':
		target = &pegC;
		break;
	default:
		return; // Invalid target peg
	}
	if (source->empty())
	{
		return; // Cannot move from an empty peg
	}
	int diskToMove = source->back(); // Get the top disk from the source peg
	// Check if the target peg is not empty and the top disk on the target peg is smaller than the disk to move
	if (!target->empty() && target->back() < diskToMove)
	{
		return; // Cannot place a larger disk on a smaller one
	}
	source->pop_back(); // Remove the top disk from the source peg
	target->push_back(diskToMove); // Place the disk on the target peg
}

// precondition: None
// postcondition: Displays the current state of the pegs and disks in a graphical format
void TowerOfHanoi::displayPegs() const
{
	// Constants for display formatting
    const int ONE = 1;
    const int TWO = 2;
    const int THREE = 3;
    const int FIVE = 5;
    const int TEN = 10;
    const int FIXED_WIDTH = 7;
	// ASCII characters for drawing the pegs and disks
    const char VERTICAL_BAR = char(186);       
    const char HORIZONTAL_BAR = char(205);    
    const char BOTTOM_T = char(202);           
    const char TOP_BLOCK = char(223);          

	int totalWidth; // Total width for displaying each peg

    // For 1..9 disks, width changes with number of disks
    if (numberOfDisks < TEN)
    {
        totalWidth = numberOfDisks * TWO + ONE;
    }
    else
    {
        // For 10..64 disks, use fixed width
        totalWidth = FIXED_WIDTH;
    }
    // Display top of the pegs
    cout << "\t";
    cout << string(totalWidth / TWO, ' ') << VERTICAL_BAR << string(totalWidth / TWO, ' ') << string(FIVE, ' ');
    cout << string(totalWidth / TWO, ' ') << VERTICAL_BAR << string(totalWidth / TWO, ' ') << string(FIVE, ' ');
    cout << string(totalWidth / TWO, ' ') << VERTICAL_BAR << "\n";

    // Display each level
	for (int level = numberOfDisks; level >= ONE; level--) // Start from the top level down to the bottom
    {
        cout << "\t";
		// PEG A
		if (level <= static_cast<int>(pegA.size())) // Check if there is a disk at this level on peg A
        {
            int diskSize = pegA[static_cast<size_t>(level) - static_cast<size_t>(ONE)];

            // 1..9 disks: graphical representation
            if (numberOfDisks < TEN)
            {
                int diskWidth = diskSize * TWO + ONE;
                int padding = (totalWidth - diskWidth) / TWO;
				// Display the disk with padding and size
                cout << string(padding, ' ') << string(diskSize, TOP_BLOCK) << diskSize << string(diskSize, TOP_BLOCK) << string(padding, ' ');
            }
            // 10..64 disks: number only
            else
            {
				string disk = to_string(diskSize); // Convert disk size to string for display
				int leftPadding = (totalWidth - static_cast<int>(disk.length())) / TWO; // Calculate left padding for centering the number
				// Calculate right padding for centering the number
                int rightPadding = totalWidth - static_cast<int>(disk.length()) - leftPadding;
				// Display the disk number with padding
                cout << string(leftPadding, ' ') << disk << string(rightPadding, ' ');
            }
        }
        else
        {
			// No disk at this level on peg A, display the vertical bar
            cout << string(totalWidth / TWO, ' ') << VERTICAL_BAR << string(totalWidth / TWO, ' ');
        }
		// Add spacing between pegs
        cout << string(FIVE, ' ');

        // PEG B
        if (level <= static_cast<int>(pegB.size()))
        {
			// Get the disk size at this level on peg B
            int diskSize = pegB[static_cast<size_t>(level) - static_cast<size_t>(ONE)];

            if (numberOfDisks < TEN)
            {
                int diskWidth = diskSize * TWO + ONE;
                int padding = (totalWidth - diskWidth) / TWO;
				// Display the disk with padding and size
                cout << string(padding, ' ') << string(diskSize, TOP_BLOCK) << diskSize << string(diskSize, TOP_BLOCK) << string(padding, ' ');
            }
            else
            {
                string disk = to_string(diskSize);
				// Calculate left and right padding for centering the disk number
                int leftPadding = (totalWidth - static_cast<int>(disk.length())) / TWO;
				// Calculate right padding for centering the disk number
                int rightPadding = totalWidth - static_cast<int>(disk.length()) - leftPadding;
				// Display the disk number with padding
                cout << string(leftPadding, ' ') << disk << string(rightPadding, ' ');
            }
        }
        else
        {
			// No disk at this level on peg B, display the vertical bar
            cout << string(totalWidth / TWO, ' ') << VERTICAL_BAR << string(totalWidth / TWO, ' ');
        }
		// Add spacing between pegs
        cout << string(FIVE, ' ');

        // PEG C
        if (level <= static_cast<int>(pegC.size()))
        {
			// Get the disk size at this level on peg C
            int diskSize = pegC[static_cast<size_t>(level) - static_cast<size_t>(ONE)];
            if (numberOfDisks < TEN)
            {
                int diskWidth = diskSize * TWO + ONE;
                int padding = (totalWidth - diskWidth) / TWO;
                cout << string(padding, ' ') << string(diskSize, TOP_BLOCK) << diskSize << string(diskSize, TOP_BLOCK) << string(padding, ' ');
            }
            else
            {
                string disk = to_string(diskSize);
				// Calculate left and right padding for centering the disk number
                int leftPadding = (totalWidth - static_cast<int>(disk.length())) / TWO;
				// Calculate right padding for centering the disk number
                int rightPadding = totalWidth - static_cast<int>(disk.length()) - leftPadding;
				// Display the disk number with padding
                cout << string(leftPadding, ' ') << disk << string(rightPadding, ' ');
            }
        }
        else
        {
            cout << string(totalWidth / TWO, ' ') << VERTICAL_BAR << string(totalWidth / TWO, ' ');
        }

        cout << "\n";
    }
    cout << "\t";
	// Display the bottom of the pegs
    cout << string(totalWidth / TWO, HORIZONTAL_BAR) << BOTTOM_T << string(totalWidth / TWO, HORIZONTAL_BAR) << string(FIVE, ' ');
    cout << string(totalWidth / TWO, HORIZONTAL_BAR) << BOTTOM_T << string(totalWidth / TWO, HORIZONTAL_BAR) << string(FIVE, ' ');
    cout << string(totalWidth / TWO, HORIZONTAL_BAR) << BOTTOM_T << string(totalWidth / TWO, HORIZONTAL_BAR) << "\n";
	// Display the labels for each peg
    cout << "\t";
    cout << string(totalWidth / TWO, ' ') << 'A' << string(totalWidth / TWO, ' ') << string(FIVE, ' ');
    cout << string(totalWidth / TWO, ' ') << 'B' << string(totalWidth / TWO, ' ') << string(FIVE, ' ');
    cout << string(totalWidth / TWO, ' ') << 'C' << "\n";
}