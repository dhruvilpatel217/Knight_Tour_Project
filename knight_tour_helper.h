// knight_tour_helper.h
#ifndef KNIGHT_TOUR_HELPER_H
#define KNIGHT_TOUR_HELPER_H

#include <bits/stdc++.h>
using namespace std;

// Declaring the external variables
extern map<pair<int,int>, vector<vector<int>>> allBoard;
extern vector<pair<int, int>> sol_found;

// Declaring the solveKnightTour function
bool solveKnightTour(int N, int start_x, int start_y, vector<vector<int>> &path);
void precomputeAllKnightTours(int N);

#endif
