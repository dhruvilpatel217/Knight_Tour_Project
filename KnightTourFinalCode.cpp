#include <bits/stdc++.h>
#include "knight_tour_helper.h"
#include "KnightTourPlayGame.h"
#include <conio.h>
#include <windows.h>
using namespace std;

class Knight_tour
{
private:
    void display_heading();
    void print_rules();
    void display_information();
    void start_game();
    void end_game();
    int st_row;
    int st_col;

public:
    Knight_tour()
    {
        display_heading();
        display_information();
    }

    ~Knight_tour()
    {
        end_game();
    }
};

void Knight_tour::display_heading()
{
    setColor(5);

    string s = "WELCOME TO THE KNIGHT'S TOUR";
    int n = s.size();
    cout << " ";
    for (int i = 0; i < s.size() + 2; i++)
        cout << "_";
    cout << endl;
    cout << "|";
    for (int i = 0; i < s.size() + 2; i++)
        cout << " ";
    cout << "|" << endl
         << "|";
    cout << " ";
    setColor(6);
    cout << s;
    setColor(5);
    cout << " |" << endl;
    cout << "|";
    for (int i = 0; i < s.size() + 2; i++)
        cout << "_";
    cout << "|" << endl
         << endl;

    setColor(7);
}

void Knight_tour::print_rules()
{
    setColor(10);
    cout << "\n\n KNIGHT'S TOUR RULES:\n\n";

    setColor(14);
    cout << " Objective:\n";
    setColor(7);
    cout << "  - Visit every square of the chessboard exactly once using only knight moves.\n\n";

    setColor(14);
    cout << " Movement Rules:\n";
    setColor(7);
    cout << "  - The knight moves in an \"L\" shape:\n";
    cout << "    * 2 squares in one direction and then 1 square perpendicular.\n";

    setColor(14);
    cout << " Constraints:\n";
    setColor(7);
    cout << "  - You cannot revisit any square.\n";
    cout << "  - The knight must stay within the board boundaries.\n";
    cout << "  - All moves must be valid knight moves.\n\n";

    setColor(14);
    cout << " Winning Condition:\n";
    setColor(7);
    cout << "   Successfully visit all squares without repeating any cell.\n\n";

    setColor(14);
    cout << " Losing Condition:\n";
    setColor(7);
    cout << "   No legal moves left before completing all squares.\n\n";

    setColor(7);
}

void Knight_tour::display_information()
{
    setColor(3);
    cout << "For reading rules press 'r' and for playing games press 'p' : ";
    char ch;
    ch = _getch();
    while (!((ch == 'p') || (ch == 'r')))
    {
        setColor(4);
        cout << "!INVALID KEY PRESS.\n";
        setColor(3);
        cout << "For reading rules press 'r' and for playing games press 'p' : ";
        ch = _getch();
    }

    if (ch == 'r' || ch == 'p')
    {
        cout << ch;
        if (ch == 'r')
        {
            print_rules();
            setColor(3);
            cout << "\nPress 'p' to start the game : ";
            ch = _getch();
            while (ch != 'p')
            {
                setColor(4);
                cout << "!INVALID KEY PRESS.\n";
                setColor(3);
                cout << "Please press 'p' to start the game : ";
                ch = _getch();
            }

            cout << ch;
            // start game
            start_game();
        }
        else if (ch == 'p')
        {
            // start game
            start_game();
        }
    }
}

void Knight_tour::start_game()
{
    setColor(3);
    cout << "\n\nPlease enter the size of checkboard you want (minimum is 5 and maximum is 10) : ";
    int si;
    char ch;
    ch = _getch();
    cout << ch << endl;
    si = ch - '0';

    while (si <= 4 || si >= 11)
    {
        setColor(4);
        cout << "!INVALID SIZE ENTERED.\n";
        cout << "Please enter the size again\n";
        setColor(7);
        ch = _getch();
        si = ch - '0';
    }

    precomputeAllKnightTours(si); // this function is defined in knight_tour_helper.cpp

    // To select random starting point in the board
    random_device rd;
    mt19937 gen(time(0));
    uniform_int_distribution<> dis(0, sol_found.size() - 1);

    int rnd_idx = dis(gen);
    st_row = sol_found[rnd_idx].first;
    st_col = sol_found[rnd_idx].second;

    play_game_KnightTour(si, st_row, st_col); // this function is defined in KnightTourPlayGame.cpp
}

void Knight_tour::end_game()
{
    cout << "WAIT WAIT ,to view the solution for your board size press 's' or press any other key to end game.\n\n";
    char ch;
    ch = _getch();
    if (ch == 's' || ch == 'S')
    {
        print_solution(st_row, st_col, allBoard[{st_row, st_col}]);
    }

    setColor(3);
    cout << "\n\n!!THANKS FOR PLAYING GAME!!\n";
    setColor(7);
}

int main()
{
    setColor(7);
    Knight_tour kt;

    return 0;
}