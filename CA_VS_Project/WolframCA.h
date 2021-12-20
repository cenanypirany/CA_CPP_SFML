#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class WolframCA
{
private:
	vector<int> ruleset;
	int blockSize = 5;
	int width = 1305;
	vector<vector<int>> patterns = {
		{1,1,1},
		{1,1,0},
		{1,0,1},
		{1,0,0},
		{0,1,1},
		{0,1,0},
		{0,0,1},
		{0,0,0}
	};
	int fps;

public:
	WolframCA(vector<int> ruleset, int fps);

	void run();
};

