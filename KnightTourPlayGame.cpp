#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
#include "KnightTourPlayGame.h"
using namespace std;

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int N;
int dr[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int dc[8] = {1, 2, 2, 1, -1, -2, -2, -1};

vector<vector<string>> grid;

bool Valid(int row, int col)
{
    return (row >= 0 && col >= 0 && row < N && col < N);
}

void enableANSI()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= 0x0004; // ENABLE_VIRTUAL_TERMINAL_PROCESSING
    SetConsoleMode(hOut, dwMode);
}

// moves cursor to position row and col of terminal(console) +1 add since terminal is 1-based indexed
void moveCursor(int row, int col)
{
    cout << "\033[" << (row + 1) << ";" << (col + 1) << "H";
}

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
    cout << "S: Moves 2 units UP, then 1 unit LEFT\n\n";
}

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

                setColor(240);
                cout << padded;
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

void clearLine(int row) {
    moveCursor(row, 0);
    cout << string(300, ' '); 
    moveCursor(row, 0);       
}

bool Occupy(int row, int col, int &flag, int &count_lines)
{
    if (grid[row][col] == " ")
    {
        return 0;
    }
    else
    {
        setColor(12);
        clearLine(2*N + 13);
        cout << "Knight already placed at that cell..\n";
        cout << "Please select different move.\n";
        setColor(7);
        count_lines += 2;
        flag = 1;
        return 1;
    }
}

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
                clearLine(2*N + 13);
                cout << "Your move leads you to out of board.\n";
                cout << "Please press correct key.\n";
            }
            else
            {
                clearLine(2*N + 13);
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

        clearLine(2*N + 13);
        drawGrid(row, col, cur);

        if (cur == N * N + 1)
        {
            setColor(13);
            clearLine(2*N + 13);
            cout << "\nCONGRATULATIONS YOU HAVE COMPLETED THE GAME!!\n\n";
            setColor(7);
            count_lines++;
            flag = 3;
            break;
        }

        if (Caught(row, col))
        {
            setColor(12);
            clearLine(2*N + 13);
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