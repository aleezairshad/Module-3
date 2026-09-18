//Name: Hany, Aleeza, and Tuniphn
// Date: 9/10/2026
//Description: Module 3 - Games Applications using Container

#include <iostream>
#include <cstdint>
#include <ctime>
#include <cstdlib>
#include <cctype>
#include "input.h"
#include "Tic_tac_toe.h"
#include "TowerOfHanoi.h"
#include "nQueens.h"

using namespace std;

//function prototypes
char menuOption();
void runTicTacToe();
void runTowerOfHanoi();
void runNQueens();


int main()
{
    srand(static_cast<unsigned int>(time(0)));
    bool running = true;
    char option;

    while (running)
    {
        system("cls");
        option = menuOption();
        switch (option)
        {
        case '1':
            system("cls");
           runTicTacToe(); // Call the function to run the Tic-Tac-Toe game
            break;
        case '2':
			system("cls");
			runTowerOfHanoi(); // Call the function to run the Tower of Hanoi game

            break;
        case '3':
			system("cls");
			runNQueens(); // Call the function to run the n-Queens game
           
            break;
        case '0':
            running = false;
            break;
        default:
            cout << "Invalid option. Please try again.\n";
            break;
        }
    }

    return 0;
}


// precondition: None
// postcondition: Displays the menu options and returns the user's choice
char menuOption()
{
    cout << "\tCMPR131 Chapter 3 - Games Applications using Container by Hany, Aleeza, and Tuniphn\n";
    cout << "\t" << string(90, char(205));
    cout << "\n\t\t1> Tic-Tac-Toe\n";
    cout << "\t\t2> Tower of Hanoi\n";
    cout << "\t\t3> n-Queens\n";
    cout << "\t" << string(90, char(196));
    cout << "\n\t\t0. Exit\n";
    cout << "\t" << string(90, char(205));

    char option = toupper(inputChar("\n\toption: ", static_cast<string>("1,2,3,0")));
    return option;
}


// precondition: None
// postcondition: Runs the Tic-Tac-Toe game, allowing the user to play against the computer
void runTicTacToe()
{
    const int ONE = 1, ZERO = 0;
    Tic_tac_toe game; // Create an instance of the Tic_tac_toe class
    char again = 'Y';

    // Variables for game statistics
    int gamesPlayed = 0;
    int totalTime = 0;
    int fastestTime = 0;
    int slowestTime = 0;
    int fastestMoves = 0;
    int slowestMoves = 0;

    // Display the game instructions
    cout << "\tTic-tac-toe (also known as Noughts and crosses or Xs and Os) " << "is a game for two\n";
    cout << "\tplayers, X and O, who take turns marking the spaces in a " << "3x3 grid. The player who\n";
    cout << "\tsucceeds in placing three of their marks in a horizontal, " << "vertical, or diagonal\n";
    cout << "\trow wins the game.\n";
    cout << "\tThis tic-tac-toe program plays against the computer. " << "Human player, X, will always\n";
    cout << "\tfirst. Time will be recorded for the fastest and the " << "slowest game. Average time will\n";
    cout << "\tthen be calculated and displayed.\n";

    // Loop to allow the user to play multiple games
    while (toupper(again) == 'Y')
    {
        game.resetBoard(); // Reset board for a new game

        int moves = 0;
        bool hasWinner = false;

        cout << "\n\tGame begins...\n";
        game.displayBoard(); // Display initial empty board

        // Record the starting time
        time_t startTime = time(0);

        bool gameOver = false;

        // Main game loop
        while (!gameOver)
        {
            cout << "\n\tHUMAN moves...\n\n";

            int row = inputInteger( "\t\tEnter the board's row # (1..3) or 0 to forfeit: ", 0, 3);

            // Check if user wants to forfeit
            if (row == ZERO)
            {
                cout << "\n\tDumb AI has actually won.\n";
                break;
            }

            int column = inputInteger( "\t\tEnter the board's column # (1..3) or 0 to forfeit: ", 0, 3);

            // Check if user wants to forfeit
            if (column == ZERO)
            {
                cout << "\n\tDumb AI has actually won.\n";
                break;
            }

            // Check if the human move is illegal
            if (game.checkillegalMove(row - ONE, column - ONE))
            {
                cout << "\n\tERROR: Illegal move. " << "The square is already owned. " << "Please re-specify.\n";
                continue;
            }

            // Place X on the board
            game.setCellValue(row - ONE, column - ONE);

            // Increment the human move count
            moves++;

            game.displayBoard();

            // Check if human has won
            if (game.checkWinner() == 'X')
            {
                cout << "\n\tHUMAN has won.\n";
                hasWinner = true;
                break;
            }

            // Check for a draw
            if (game.checkDraw())
            {
                cout << "\n\tIt's a draw.\n";
                break;
            }

            cout << "\n\tDumb AI moves...\n";

            // Computer makes a move
            game.computerMove();

            game.displayBoard();

            // Check if computer has won
            if (game.checkWinner() == 'O')
            {
                cout << "\n\tDumb AI has actually won.\n";
                hasWinner = true;
                break;
            }

            // Check for a draw
            if (game.checkDraw())
            {
                cout << "\n\tIt's a draw.\n";
                break;
            }
        }

        // Only games with a winner are included in statistics
        if (hasWinner)
        {
            time_t endTime = time(0);

            int gameTime = static_cast<int>(difftime(endTime, startTime));

            gamesPlayed++;
            totalTime += gameTime;

            // First completed game
            if (gamesPlayed == ONE)
            {
                fastestTime = gameTime;
                slowestTime = gameTime;

                fastestMoves = moves;
                slowestMoves = moves;
            }
            else
            {
                // Check for fastest game
                if (gameTime < fastestTime)
                {
                    fastestTime = gameTime;
                    fastestMoves = moves;
                }

                // Check for slowest game
                if (gameTime > slowestTime)
                {
                    slowestTime = gameTime;
                    slowestMoves = moves;
                }
            }
        }

        // Ask if user wants to play another game
        again = toupper(inputChar( "\n\tPlay again? (Y-yes or N-no) ", static_cast<string>("Y,N")));
    }

    // Display game statistics
    if (gamesPlayed == ZERO)
    {
        cout << "\n\tNo game statistic collected.\n";
    }
    else
    {
        cout << "\n\tGame statistics:\n\n";

        // Display number of games played
        if (gamesPlayed == ONE)
        {
            cout << "\t1 game of Tic-Tac-Toe was played.\n";
        }
        else
        {
            cout << "\t" << gamesPlayed << " games of Tic-Tac-Toe were played.\n";
        }

        // Display fastest game
        cout << "\t\tThe fastest time was " << fastestTime << " seconds in " << fastestMoves << " moves.\n";

        // Display slowest game
        cout << "\t\tThe slowest time was " << slowestTime << " seconds in " << slowestMoves << " moves.\n";

        // Calculate average game time
        double averageTime = static_cast<double>(totalTime) / gamesPlayed;

        cout << "\t\tThe average time was " << averageTime << " second(s).\n";
    }

    cout << "\n";
    system("pause");
} 

// precondition: None
// postcondition: Runs the Tower of Hanoi game, allowing the user to move disks between pegs
void runTowerOfHanoi()
{
    const int ZERO = 0;
    const int ONE = 1;
    const int TEN = 10;
    const int MIN_DISKS = 1;
    const int MAX_DISKS = 64;

    TowerOfHanoi game;
    char again = 'Y';

    // Statistics
    int gamesPlayed = 0;
    int totalTime = 0;
    int fastestTime = 0;
    int slowestTime = 0;
    int fastestMoves = 0;
    int slowestMoves = 0;
    int disksPlayed = 0;
    // Display instructions
    cout << "\n\tThe Tower of Hanoi also called the Tower of Brahma or Lucas' Tower " << "is a mathematical game.\n";
    cout << "\tIt consists of three pegs and a number of rings of different sizes, " << "which can slide onto\n";
    cout << "\tany peg. The game starts with the rings in a neat stack in ascending " << "order of size on one\n";
    cout << "\tpeg, the smallest at the top, thus making a conical shape.\n\n";
    cout << "\tThe objective of the game is to move the entire stack from the " << "starting peg-A to ending peg-C,\n";
    cout << "\tobeying the following simple rules:\n\n";
    cout << "\t\t1. Only one disk can be moved at a time.\n";
    cout << "\t\t2. Each move consists of taking the upper disk from one of the " << "stacks and\n";
    cout << "\t\t   placing it on top of another stack or on an empty peg.\n";
    cout << "\t\t3. No larger disk may be placed on top of a smaller disk.\n";

    // Allow user to play multiple games
    while (toupper(again) == 'Y')
    {
        int numberOfDisks = inputInteger( "\n\tEnter the number of rings (1..64) to begin: ", MIN_DISKS, MAX_DISKS);
        // Display note for 10..64 disks
        if (numberOfDisks >= TEN)
        {
            cout << "\t\tNote: The rings will be represented with numbers " << "(1 is the smallest size and " << numberOfDisks << " is the largest size).\n";
        }
        // Set up the game
        game.setNumberOfDisks(numberOfDisks);

        int moves = 0;
        bool solved = false;
        bool quit = false;
        // Start timer
        time_t startTime = time(0);

        // Display initial board
        cout << "\n\tTower of Hanoi\n\n";
        game.displayPegs();

        // Main game loop
        while (!solved && !quit)
        {
            char sourcePeg = toupper(inputChar( "\n\tSelect the top disk from the start peg " "(A, B, C, or Q-quit): ", static_cast<string>("A,B,C,Q")));
            // Quit current game
            if (sourcePeg == 'Q')
            {
                quit = true;
                break;
            }

            // Check if source peg is empty
            bool sourceEmpty = false;

            if (sourcePeg == 'A')
            {
                sourceEmpty = game.isEmptyPegA();
            }
            else if (sourcePeg == 'B')
            {
                sourceEmpty = game.isEmptyPegB();
            }
            else if (sourcePeg == 'C')
            {
                sourceEmpty = game.isEmptyPegC();
            }
			// Cannot move from an empty peg
            if (sourceEmpty)
            {
                cout << "\n\tERROR: Cannot move a disk from an empty peg.\n";
                continue;
            }
			// Get the target peg for the move
            char targetPeg = toupper(inputChar( "\tSelect the end peg (A, B, C or Q-quit) " "to move the selected disk: ", static_cast<string>("A,B,C,Q")));
            // Quit current game
            if (targetPeg == 'Q')
            {
                quit = true;
                break;
            }
            // Cannot move to the same peg
            if (sourcePeg == targetPeg)
            {
                cout << "\n\tERROR: Cannot move a disk to the same peg.\n";
                continue;
            }
            // Get the top disk from the source peg
            int sourceDisk = ZERO;

            if (sourcePeg == 'A')
            {
                sourceDisk = game.getTopPegA();
            }
            else if (sourcePeg == 'B')
            {
                sourceDisk = game.getTopPegB();
            }
            else if (sourcePeg == 'C')
            {
                sourceDisk = game.getTopPegC();
            }

            // Get the top disk from the target peg
            int targetDisk = ZERO;
            bool targetEmpty = false;

            if (targetPeg == 'A')
            {
                targetEmpty = game.isEmptyPegA();

                if (!targetEmpty)
                {
                    targetDisk = game.getTopPegA();
                }
            }
            else if (targetPeg == 'B')
            {
                targetEmpty = game.isEmptyPegB();

                if (!targetEmpty)
                {
                    targetDisk = game.getTopPegB();
                }
            }
            else if (targetPeg == 'C')
            {
                targetEmpty = game.isEmptyPegC();

                if (!targetEmpty)
                {
                    targetDisk = game.getTopPegC();
                }
            }

            // Cannot place larger disk on smaller disk
            if (!targetEmpty && sourceDisk > targetDisk)
            {
                cout << "\n\tERROR: Cannot place a larger disk " << "on top of a smaller disk.\n";
                continue;
            }
            // Make the move
            game.moveDisk(sourcePeg, targetPeg);

            moves++;
			// Display the move made
            cout << "\n\tTop disk from peg-" << sourcePeg << " has moved to peg-" << targetPeg << ".\n";

            // Check if all disks have been moved to peg C
            if (game.isEmptyPegA() && game.isEmptyPegB() && !game.isEmptyPegC())
            {
                solved = true;
                cout << "\n";
                game.displayPegs();
                break;
            }
			// Display the current state of the pegs
            cout << "\n\tTower of Hanoi\n\n";
            game.displayPegs();
        }

        // Game was successfully solved
        if (solved)
        {
			time_t endTime = time(0); // Record the ending time
			int gameTime = static_cast<int>(difftime(endTime, startTime)); // Calculate the total time taken to solve the game
			// Display the number of moves taken to solve the game
            cout << "\n\tCongratulation! You have solved the game in " << moves << " moves.\n";

            // Update statistics
            gamesPlayed++;
            totalTime += gameTime;
            disksPlayed = numberOfDisks;
            // First completed game
            if (gamesPlayed == ONE)
            {
                fastestTime = gameTime;
                slowestTime = gameTime;

                fastestMoves = moves;
                slowestMoves = moves;
            }
            else
            {
                // Check fastest game
                if (gameTime < fastestTime)
                {
                    fastestTime = gameTime;
                    fastestMoves = moves;
                }
                // Check slowest game
                if (gameTime > slowestTime)
                {
                    slowestTime = gameTime;
                    slowestMoves = moves;
                }
            }
        }
        // Ask user to play again
        again = toupper(inputChar( "\n\tPlay again? (Y-yes or N-no) ", static_cast<string>("Y,N")));
    }

    // Display statistics
    if (gamesPlayed == ZERO)
    {
        cout << "\n\tNo game statistic collected.\n";
    }
    else
    {
        cout << "\n\tGame statistics:\n\n";

        if (gamesPlayed == ONE)
        {
            cout << "\t1 game using " << disksPlayed << " disks was played.\n";
        }
        else
        {
            cout << "\t" << gamesPlayed << " games using " << disksPlayed << " disks were played.\n";
        }
		// Display fastest game
        cout << "\t\tThe fastest time was " << fastestTime << " seconds in " << fastestMoves << " moves.\n";
		// Display slowest game
        cout << "\t\tThe slowest time was " << slowestTime << " seconds in " << slowestMoves << " moves.\n";
		// Calculate and display average game time
        double averageTime = static_cast<double>(totalTime) / gamesPlayed;
		// Display average game time
        cout << "\t\tThe average time was " << averageTime << " second(s).\n";
    }

    cout << "\n";
    system("pause");
}

// precondition: None
// postcondition: Runs the n-Queens game, allowing the user to place and remove queens on the board
void runNQueens()
{
    cout << "\n\tThe n-queens puzzle is the problem of placing n chess queens on a n?n chessboard";
    cout << "\n\tso that no two queens threaten each other; thus, a solution requires that no two";
    cout << "\n\tqueens share the same row, column, or diagonal. Solutions exist for all natural";
    cout << "\n\tnumbers n with the exception of n = 2 and n = 3.";

    char option = 'X';
    char playAgain = 'Y';
	// Vectors to store game statistics
    vector<int> collectedTimes;
    vector<int> collectedMoves;
    vector<int> matches;
    vector<int> processedSize;
	const int ONE = 1, ZERO = 0, TWO = 2, THREE = 3, FOUR = 4;

    do
    {
        int moves = 0;
        int elapsedTime = 0;
		int size = inputInteger("\n\n\tEnter the board dimension nxn: ", true); // Input the board size from the user
		// Check for invalid board sizes (2 and 3) and prompt the user to enter a valid size
        while (size == 2 || size == 3)
        {
            cout << "\n\tERROR: size cannot be " << size << ", because there is no solution.";
			size = inputInteger("\n\tEnter the board dimension nxn: ", true); // Prompt the user to enter a valid board size
        }
        time_t startTime = time(0);
		nQueens board(size); // Create an instance of the nQueens class with the specified board size
        do
        {
			// Display the game title and board size
            if (size == ONE)
            {
                cout << "\n\t1-Queen";
            }
            else
            {
                cout << "\n\t" << size << "-Queens";
            }

            board.display();

            cout << "\n\tGame Options";
            cout << "\n\t" << string(90, char(205));
            cout << "\n\tA> Place a queen";
            cout << "\n\tB> Remove an existing queen";
            cout << "\n\t" << string(90, char(196));
            cout << "\n\t0> return";
            cout << "\n\t" << string(90, char(205));
            option = inputChar("\n\tOption: ", string("AB0"));
			// Process the user's option
            switch (toupper(option))
            {
            case 'A':
            {
                cout << "\n\tPosition a queen in the row (1.." << board.getSize() << "): ";
                int placeRow = inputInteger("", 1, board.getSize()); 

                cout << "\n\tPosition a queen in the column (1.." << board.getSize() << "): ";
                int placeCol = inputInteger("", 1, board.getSize());
				// Attempt to place a queen on the board and check for conflicts
                int result = board.placeQueen(placeRow, placeCol);
                if (result == 0)
                {
                    moves++;
                    cout << "\n\tQueen is placed";
                }
                else if (result == ONE)
                {
                    cout << "\n\tERROR: A queen already exists at this position.";
                }
                else if (result == TWO)
                {
                    cout << "\n\tERROR: Another queen is in the same row.";
                }
                else if (result == THREE)
                {
                    cout << "\n\tERROR: Another queen is in the same column.";
                }
                else if (result == FOUR)
                {
                    cout << "\n\tERROR: Another queen is on the same diagonal.";
                }

                if (board.solved())
                {
                    cout << "\n\tThe game is solved!";
                    time_t endTime = time(0);
					elapsedTime = static_cast<int>(endTime - startTime); // Calculate the elapsed time in seconds
					collectedTimes.push_back(elapsedTime); // Store the elapsed time for this game
					collectedMoves.push_back(moves); // Store the number of moves for this game
					matches.push_back(size); // Store the board size for this game
                    board.display(); 
                } 

            }
            break;

            case 'B':
            {
                cout << "\n\tPosition a queen in the row (1.." << board.getSize() << "): ";
                int removeRow = inputInteger("", 1, board.getSize());

                cout << "\n\tPosition a queen in the column (1.." << board.getSize() << "): ";
                int removeCol = inputInteger("", 1, board.getSize());

                if (board.removeQueen(removeRow, removeCol))
                {
                    moves++;
                    cout << "\n\tQueen is removed";
                }
                else
                {
                    cout << "\n\tNo such queen existed.";
                }
            }
            break;

            case '0':
            {
            }
            break;

            default:
            {
                cout << "\n\tERROR: Invalid option.\n";
            }
            break;

            }

        } while (option != '0' && !board.solved());

        playAgain = inputChar("\n\tPlay again? (Y-yes or N-no): ", string("YN"));

    } while (playAgain != 'N'); 
	// Display game statistics
    if (matches.empty())
    {
        cout << "\n\tNo game statistic collected.";
    }
    else
    {
        cout << "\n\tGame statistics:";

        for (int i = 0; i < matches.size(); i++)
        {
            int currentSize = matches[i];
            int gameCount = 0;
            int fastest{}; //for time
            int slowest{};
            int fastestMoves{}; //for moves
            int slowestMoves{};
            int totalTime = 0;

            if (find(processedSize.begin(), processedSize.end(), currentSize) == processedSize.end())
            {
                for (int j = 0; j < matches.size(); j++)
                {
                    if (matches[j] == currentSize)
                    {
                        gameCount++;

                        totalTime += collectedTimes[j];

                        if (gameCount == 1)
                        {
                            fastest = collectedTimes[j];
                            slowest = collectedTimes[j];

                            fastestMoves = collectedMoves[j];
                            slowestMoves = collectedMoves[j];
                        }
                        else
                        {
                            if (fastest > collectedTimes[j])
                            {
                                fastest = collectedTimes[j];
                                fastestMoves = collectedMoves[j];
                            }

                            if (slowest < collectedTimes[j])
                            {
                                slowest = collectedTimes[j];
                                slowestMoves = collectedMoves[j];
                            }
                        }
                    }
                }

                processedSize.push_back(currentSize);

				// Display the number of games played for the current board size
                if (gameCount == 1)
                {
                    cout << "\n\t" << gameCount << " game using ";
                    if (currentSize == 1)
                    {
                        cout << currentSize << " queen was played.";
                    }
                    else
                    {
                        cout << currentSize << " queens was played.";
                    }
                }
                else
                {
                    cout << "\n\t" << gameCount << " games using ";
                    if (currentSize == 1)
                    {
                        cout << currentSize << " queen were played.";
                    }
                    else
                    {
                        cout << currentSize << " queens were played.";
                    }
                }

                //second(s) move(s)
                cout << "\n\t\tThe fastest time was " << fastest << " second";
                if (fastest != 1)
                    cout << "s";
                cout << " in " << fastestMoves << " move";
                if (fastestMoves != 1)
                    cout << "s";
                cout << ".";

                cout << "\n\t\tThe slowest time was " << slowest << " second";
                if (slowest != 1)
                    cout << "s";
                cout << " in " << slowestMoves << " move";
                if (slowestMoves != 1)
                    cout << "s";
                cout << ".";
				// Calculate and display average time
                cout << "\n\tThe average time was " << static_cast<double>(totalTime) / gameCount << " second(s)\n";
            }
        }
    }
	system("pause");
}
