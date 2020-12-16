 
#include <iostream>
#include <cmath>
#include "nQueenPuzzle.h"

using namespace std;

int main()
{
	nQueensPuzzle queens(12);

	queens.queensConfiguration(0);
	cout << "Number of Solutions: " << queens.solutionsCount() << endl;

	return 0;
}