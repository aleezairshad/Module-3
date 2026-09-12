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

using namespace std;

//function prototypes
char menuOption();
void runTicTacToe();

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
            cout << "Tower of Hanoi\n";
            break;
        case '3':
            cout << "n-Queens\n";
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
	Tic_tac_toe game; // Create an instance of the Tic_tac_toe class to manage the game
    char again = 'Y';
	// Display the game instructions
    cout << "\tTic-tac-toe (also known as Noughts and crosses or Xs and Os) " << "is a game for two\n";
    cout << "\tplayers, X and O, who take turns marking the spaces in a " << "3x3 grid. The player who\n";
    cout << "\tsucceeds in placing three of their marks in a horizontal, " << "vertical, or diagonal\n";
    cout << "\trow wins the game.\n";
    cout << "\tThis tic-tac-toe program plays against the computer. " << "Human player, X, will always\n";
    cout << "\tfirst. Time will be recorded for the fastest and the " << "slowest game. Average time will\n";
    cout << "\tthen be calculated and displayed.\n";
    
	while (toupper(again) == 'Y') // Loop to allow the user to play multiple games
    {
		game.resetBoard(); // Reset the board for a new game

		int moves = 0; // Variable to keep track of the number of moves made in the game
		bool hasWinner = false; 

        cout << "\n\tGame begins...\n";
		game.displayBoard(); // Display the initial empty board

		time_t startTime = time(0); // Record the start time of the game
		bool gameOver = false; // Variable to track if the game is over
		// Main game loop
        while (!gameOver)
        {
            cout << "\n\tHUMAN moves...\n\n";
            
			int row = inputInteger("\t\tEnter the board's row # (1..3) or 0 to forfeit: ", 0, 3); // Get the row input from the user
			// Check if the user wants to forfeit the game
            if (row == ZERO)
            {
                cout << "\n\tDumb AI has actually won.\n";
                break;
            }

			int column = inputInteger("\t\tEnter the board's column # (1..3) or 0 to forfeit: ", 0, 3); // Get the column input from the user
			// Check if the user wants to forfeit the game
            if (column == ZERO)
            {
                cout << "\n\tDumb AI has actually won.\n";
                break;
            }

			// Attempt to make the move on the board for the human player (X)
            if (!game.makeMove(row - ONE, column - ONE, 'X'))
            {
                cout << "\n\tERROR: Illegal move. " << "The square is already owned. " << "Please re-specify.\n";
                continue;
            }

			moves++; // Increment the move count for the human player

			game.displayBoard(); // Display the updated board after the human player's move
			// Check if the human player has won the game
            if (game.checkWin('X'))
            {
                cout << "\n\tHUMAN has actually won.\n";
				hasWinner = true;
                break;
            }
			// Check if the board is full, indicating a draw
            if (game.isBoardFull())
            {
                cout << "\n\tIt's a draw.\n";
                break;
            }

            cout << "\n\tDumb AI moves...\n";

			game.computerMove('O'); // Let the computer make its move (O)
            game.displayBoard();
			// Check if the computer has won the game
            if (game.checkWin('O'))
            {
                cout << "\n\tDumb AI has actually won.\n";
				hasWinner = true;
                break;
            }
			// Check if the board is full, indicating a draw
            if (game.isBoardFull())
            {
                cout << "\n\tIt's a draw.\n";
                break;
            }
        }
		// If there is a winner, calculate the game time and update the statistics
        if (hasWinner)
        {
            time_t endTime = time(0);
            int gameTime =
                static_cast<int>(difftime(endTime, startTime));
            game.updateStatistics(gameTime, moves);
		}

		again = toupper(inputChar("\n\tPlay again? (Y-yes or N-no) ", static_cast<string>("Y,N"))); // Ask the user if they want to play again
    }

    game.displayStatistics();
    cout << "\n";
    system("pause");
}