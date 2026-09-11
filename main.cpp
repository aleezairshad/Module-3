//Name: Hany, Aleeza, and Tuniphn
// Date: 9/10/2026
//Description: Module 3 - Games Applications using Container

#include <iostream>
#include <cstdint>
#include <ctime>
#include <cstdlib>
#include <cctype>
#include "input.h"

using namespace std;

//function prototypes
char menuOption();

int main()
{
    //srand(static_cast<unsigned int>(time(nullptr)));
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

