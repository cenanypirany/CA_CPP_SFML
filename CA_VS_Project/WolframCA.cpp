#include "WolframCA.h"

WolframCA::WolframCA(vector<int> ruleset, int fps)
{
	this->ruleset = ruleset;
	this->fps = fps;
}

void WolframCA::run()
{
	RenderWindow window(VideoMode(width, 720), "Wolfram Cellular Automata", Style::Close);
	window.setFramerateLimit(fps);

	RectangleShape square;
	square.setSize(Vector2f(blockSize, blockSize));

	vector<int> row;
	for (int i = 0; i < width/blockSize; i++) {
		if (i == ((width / blockSize) - 1) / 2) row.push_back(1);
		else row.push_back(0);
	}

	vector<vector<int>> grid;
	grid.push_back(row);

	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed) window.close();
		}

		window.clear();

		for (int i = 0; i < grid.size(); i++)
		{
			for (int j = 0; j < grid[i].size(); j++) {
				if (grid[i][j] == 1) {
					square.setPosition(Vector2f(j * blockSize, i * blockSize));
					window.draw(square);
				}
			}
		}

		window.display();

		// Wolfram Logic
		vector<int> newRow;
		for (int i = 0; i < width / blockSize; i++) {
			newRow.push_back(0);
		}

		int lastRow = grid.size() - 1;
		for (int i = 0; i < grid[lastRow].size() - 2; i++) {
			vector<int> triplet = {
				grid[lastRow][i],
				grid[lastRow][i + 1],
				grid[lastRow][i + 2]
			};

			for (int j = 0; j < patterns.size(); j++) {
				if (patterns[j] == triplet) {
					newRow.at(i + 1) =  ruleset[j];
				}
			}
		}

		grid.push_back(newRow);

		if (grid.size() > 720 / 5) grid.erase(grid.begin());

	}
}
