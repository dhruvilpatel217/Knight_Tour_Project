#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
#include "KnightTourPlayGame.h"
using namespace std;

int N; // board size
int dr[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int dc[8] = {1, 2, 2, 1, -1, -2, -2, -1};

vector<vector<string>> grid;

// Sets the text color using ANSI escape codes (cross-platform)
void setColor(int color)
{
    switch (color)
    {
    case 0:  cout << "\033[30m"; break; // Black
    case 1:  cout << "\033[34m"; break; // Blue
    case 2:  cout << "\033[32m"; break; // Green
    case 3:  cout << "\033[36m"; break; // Aqua / Cyan
    case 4:  cout << "\033[31m"; break; // Red
    case 5:  cout << "\033[35m"; break; // Purple / Magenta
    case 6:  cout << "\033[33m"; break; // Yellow (Dark Yellow)
    case 7:  cout << "\033[37m"; break; // Light Gray
    case 8:  cout << "\033[90m"; break; // Dark Gray
    case 9:  cout << "\033[94m"; break; // Light Blue
    case 10: cout << "\033[92m"; break; // Light Green
    case 11: cout << "\033[96m"; break; // Light Cyan
    case 12: cout << "\033[91m"; break; // Light Red
    case 13: cout << "\033[95m"; break; // Light Magenta
    case 14: cout << "\033[93m"; break; // Light Yellow
    case 15: cout << "\033[97m"; break; // White (Bright)
    case 240: cout << "\033[30;47m"; break; // Black text on White background (used for current cell)
    default: cout << "\033[0m"; break; // Reset to default
    }
}

// Checks if the given cell is within the bounds of the board
bool Valid(int row, int col)
{
    return (row >= 0 && col >= 0 && row < N && col < N);
}

// Enables ANSI escape codes for formatting in the Windows terminal
void enableANSI()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= 0x0004;
    SetConsoleMode(hOut, dwMode);
}

// Moves the terminal cursor to a specific row and column
void moveCursor(int row, int col)
{
    cout << "\033[" << (row + 1) << ";" << (col + 1) << "H";
}

// Prints the keyboard instructions for knight moves
void printKnightMoveInstructions()
{
    cout << "Knight Move Instructions (Each move is in an 'L' shape):\n";
    cout << "W: Moves 2 units UP, then 1 unit RIGHT\n";
    cout << "E: Moves 2 units RIGHT, then 1 unit UP\n";
    cout << "D: Moves 2 units RIGHT, then 1 unit DOWN\n";
    cout << "C: Moves 2 units DOWN, then 1 unit RIGHT\n";
    cout << "X: Moves 2 units DOWN, then 1 unit LEFT\n";
    cout << "Z: Moves 2 units LEFT, then 1 unit DOWN\n";
    cout << "A: Moves 2 units LEFT, then 1 unit UP\n";
    cout << "S: Moves 2 units UP, then 1 unit LEFT\n";
    cout << "NOTE : Press 'q' to quit the game.\n\n";
}

// Draws the game board with the knight's current position
void drawGrid(int cursorRow, int cursorCol, int &cur_move)
{
    moveCursor(0, 0);

    setColor(14);
    cout << endl
         << endl;
    printKnightMoveInstructions();

    // Top border
    setColor(10);
    cout << "+";
    for (int j = 0; j < N; ++j)
        cout << "----+";
    cout << "\n";

    for (int i = 0; i < N; ++i)
    {

        setColor(10);
        cout << "|";
        for (int j = 0; j < N; ++j)
        {
            string tmp = grid[i][j];

            // Format value into fixed 4-width cell
            if (i == cursorRow && j == cursorCol)
            {
                tmp = to_string(cur_move);
                grid[i][j] = tmp;

                string padded;
                if (tmp.size() == 1)
                    padded = "  " + tmp + " ";
                else if (tmp.size() == 2)
                    padded = " " + tmp + " ";
                else
                    padded = " " + tmp;

                cout << "\033[30;47m" << padded << "\033[0m";
                setColor(10);
                cout << "|";
            }
            else
            {
                if (tmp == " ")
                    tmp = "    ";
                else if (tmp.size() == 1)
                    tmp = "  " + tmp + " ";
                else if (tmp.size() == 2)
                    tmp = " " + tmp + " ";
                else
                    tmp = " " + tmp;

                setColor(9);
                cout << tmp;
                setColor(10);
                cout << "|";
            }
        }
        cout << "\n";

        // Separator border
        setColor(10);
        cout << "+";
        for (int j = 0; j < N; ++j)
            cout << "----+";
        cout << "\n";
    }

    setColor(7);
    cur_move++;
}

// Prints the final solution path if the user requests it
void print_solution(int st_row, int st_col, vector<vector<int>> ans)
{
    setColor(10);
    cout << "+";
    for (int j = 0; j < N; ++j)
        cout << "----+";
    cout << "\n";

    for (int i = 0; i < N; ++i)
    {

        setColor(10);
        cout << "|";
        for (int j = 0; j < N; ++j)
        {
            string tmp = to_string(ans[i][j]);

            if (tmp == " ")
                tmp = "    ";
            else if (tmp.size() == 1)
                tmp = "  " + tmp + " ";
            else if (tmp.size() == 2)
                tmp = " " + tmp + " ";
            else
                tmp = " " + tmp;
            setColor(9);
            cout << tmp;
            setColor(10);
            cout << "|";
        }
        cout << "\n";

        // Separator border
        setColor(10);
        cout << "+";
        for (int j = 0; j < N; ++j)
            cout << "----+";
        cout << "\n";
    }

    setColor(7);
}

// Checks whether the knight has no further valid moves
bool Caught(int row, int col)
{
    int cnt = 0;
    for (int i = 0; i < 8; i++)
    {
        int new_row = row + dr[i];
        int new_col = col + dc[i];

        if (Valid(new_row, new_col) && grid[new_row][new_col] == " ")
            cnt++;
    }

    return (cnt == 0);
}

// Clears a specified line from the console screen
void clearLine(int row)
{
    moveCursor(row, 0);
    cout << string(300, ' ');
    moveCursor(row, 0);
}

// Checks if a cell is already visited and handles the error state
bool Occupy(int row, int col, int &flag, int &count_lines)
{
    if (grid[row][col] == " ")
    {
        return 0;
    }
    else
    {
        setColor(12);
        clearLine(2 * N + 13);
        cout << "Knight already placed at that cell..\n";
        cout << "Please select different move.\n";
        setColor(7);
        count_lines += 2;
        flag = 1;
        return 1;
    }
}

// Main function to handle the knight tour gameplay and logic
void play_game_KnightTour(int si, int start_row, int start_col)
{
    N = si;
    grid.assign(N, vector<string>(N, " "));
    enableANSI();
    cout << "\033[2J"; // clear screen

    int row = start_row, col = start_col;
    int cur = 1;
    int count_lines = 0;

    drawGrid(row, col, cur);
    int flag = 0;
    while (true)
    {
        char key = _getch();
        flag = 0;

        if (key == 'q' || key == 'Q')
            break;
        if ((key == 'w' || key == 'W') && Valid(row - 2, col + 1))
            if (!Occupy(row - 2, col + 1, flag, count_lines))
                row -= 2, col++, flag = 3;
        if ((key == 'e' || key == 'E') && Valid(row - 1, col + 2))
            if (!Occupy(row - 1, col + 2, flag, count_lines))
                row--, col += 2, flag = 3;
        if ((key == 'd' || key == 'D') && Valid(row + 1, col + 2))
            if (!Occupy(row + 1, col + 2, flag, count_lines))
                row++, col += 2, flag = 3;
        if ((key == 'c' || key == 'C') && Valid(row + 2, col + 1))
            if (!Occupy(row + 2, col + 1, flag, count_lines))
                row += 2, col++, flag = 3;
        if ((key == 'x' || key == 'X') && Valid(row + 2, col - 1))
            if (!Occupy(row + 2, col - 1, flag, count_lines))
                row += 2, col--, flag = 3;
        if ((key == 'z' || key == 'Z') && Valid(row + 1, col - 2))
            if (!Occupy(row + 1, col - 2, flag, count_lines))
                row++, col -= 2, flag = 3;
        if ((key == 'a' || key == 'A') && Valid(row - 1, col - 2))
            if (!Occupy(row - 1, col - 2, flag, count_lines))
                row--, col -= 2, flag = 3;
        if ((key == 's' || key == 'S') && Valid(row - 2, col - 1))
            if (!Occupy(row - 2, col - 1, flag, count_lines))
                row -= 2, col--, flag = 3;

        if (flag == 0)
        {
            setColor(12);
            if (key == 'w' || key == 'W' || key == 'e' || key == 'E' || key == 'd' || key == 'D' || key == 'c' || key == 'C' || key == 'x' || key == 'X' || key == 'z' || key == 'Z' || key == 'a' || key == 'A' || key == 's' || key == 'S')
            {
                clearLine(2 * N + 13);
                cout << "Your move leads you to out of board.\n";
                cout << "Please press correct key.\n";
            }
            else
            {
                clearLine(2 * N + 13);
                cout << "INVALID key press!\n";
                cout << "Please press correct key.\n";
            }
            setColor(7);
            count_lines += 2;
            flag = 4;
            continue;
        }

        if (flag == 1)
            continue;

        clearLine(2 * N + 13);
        drawGrid(row, col, cur);

        if (cur == N * N + 1)
        {
            setColor(13);
            clearLine(2 * N + 13);
            cout << "\nCONGRATULATIONS YOU HAVE COMPLETED THE GAME!!\n\n";
            setColor(7);
            count_lines++;
            flag = 3;
            break;
        }

        if (Caught(row, col))
        {
            setColor(12);
            clearLine(2 * N + 13);
            cout << "Sorry you lost the game....\n";
            cout << "Your knight does not have any move present.\n";
            setColor(7);
            count_lines += 2;
            flag = 2;
            break;
        }
    }

    moveCursor(2 * N + 16, 0);
}
