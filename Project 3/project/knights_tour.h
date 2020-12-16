/**
 *        @file: knights_tour.h
 *      @author: Ethan Dowalter
 *        @date: October 27, 2020
 *       @brief: Definition for the knights tour alogrithm
 */

#ifndef KNIGHTS_TOUR_H
#define KNIGHTS_TOUR_H

#include <vector>
using namespace std;

class KnightsTour {

public:
	KnightsTour(int board_size);

	int generate(int row, int col);

private:
	void move(int row, int col, int& m, int& num_tours);
	void get_moves(int row, int col, int row_moves[], int col_moves[], int& num_moves);
	void print();

	int board_size;
	vector<vector<int> > board;

};

#endif
