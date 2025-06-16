#include <bits/stdc++.h>
using namespace std;

map<pair<int,int>, vector<vector<int>>> allBoard; // stores valid ans for given N and all {i,j} considered as starting point
                                                  //{i,j}->2d vector if answer is found

vector<pair<int, int>> sol_found;

// Arrays for the 8 possible moves of a knight (these are constant)
int dr1[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int dc2[8] = {1, 2, 2, 1, -1, -2, -2, -1};

// Function to check if a square (x, y) is inside the board of size N
bool isValid(int x, int y, int N)
{
    return (x >= 0 && x < N && y >= 0 && y < N);
}

// Function to check if a square has been visited
bool isUnvisited(int x, int y, vector<vector<int>> &board)
{
    int N = board.size();
    if (isValid(x, y, N) && (board[x][y] == -1))
        return 1;
    return 0;
}

// Function to calculate the number of unvisited onward moves from a square (its "degree")
int getDegree(int x, int y, vector<vector<int>> &board)
{
    int count = 0;
    for (int i = 0; i < 8; i++)
    {
        if (isUnvisited(x + dr1[i], y + dc2[i], board))
        {
            count++;
        }
    }
    return count;
}

// Calculates the Euclidean distance of a square from the center of the board.
double distanceFromCenter(int x, int y, int N)
{
    double center = (N - 1) / 2.0;
    return sqrt(pow(x - center, 2) + pow(y - center, 2));
}

// The main function that solves the Knight's Tour problem for a board of size N
bool solveKnightTour(int N, int start_x, int start_y, vector<vector<int>> &path)
{
    vector<vector<int>> board(N, vector<int>(N, -1));

    int curr_x = start_x;
    int curr_y = start_y;
    board[curr_x][curr_y] = 1;

    for (int move_count = 2; move_count <= N * N; move_count++)
    {
        int min_degree = 10; // Initialized to 10 since maximum value is 8
        int next_x = -1, next_y = -1;
        double max_dist = -1.0;

        for (int i = 0; i < 8; i++)
        {
            int new_x = curr_x + dr1[i];
            int new_y = curr_y + dc2[i];

            if (isUnvisited(new_x, new_y, board))
            {
                int degree = getDegree(new_x, new_y, board);
                double dist = distanceFromCenter(new_x, new_y, N);

                if (degree < min_degree)
                {
                    min_degree = degree;
                    next_x = new_x;
                    next_y = new_y;
                    max_dist = dist;
                }
                else if (degree == min_degree)
                {
                    if (dist > max_dist)
                    {
                        next_x = new_x;
                        next_y = new_y;
                        max_dist = dist;
                    }
                }
            }
        }

        if (next_x == -1)
        {
            return false; // Trapped
        }

        curr_x = next_x;
        curr_y = next_y;
        board[curr_x][curr_y] = move_count;
    }

    path = board;
    return true;
}

void precomputeAllKnightTours(int N)
{
    int start_x, start_y;

    int cnt = 0;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            start_x = i;
            start_y = j;
            vector<vector<int>> path;
            if (!solveKnightTour(N, start_x, start_y, path))
            { // No solution found
                cnt++;
            }
            else
            {
                allBoard[{i, j}] = path;
                sol_found.push_back({i, j}); // solution found for given {i,j}
            }
        }
    }

}
