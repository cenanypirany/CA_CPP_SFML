#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class GOL
{
private:
	int gridSize;
	int blockSize;
	int weight;
	int side;

	vector<vector<int>> getNewGrid(bool populated);
	int getOneZero();

public:
	GOL(int gridSize, int blockSize, int weight);
	void run();
};

