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