#ifndef KNIGHT_TOUR_GAME_H
#define KNIGHT_TOUR_GAME_H

#include <bits/stdc++.h>   
using namespace std; 

void play_game_KnightTour(int boardSize, int startRow, int startCol);
void print_solution(int start_row,int start_col,vector<vector<int>> ans);

extern int dr[8];
extern int dc[8];
extern void setColor(int color);

#endif
