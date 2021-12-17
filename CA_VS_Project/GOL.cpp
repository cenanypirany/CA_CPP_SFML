#include "GOL.h"

GOL::GOL(int gridSize, int blockSize, int weight)
{
	this->gridSize = gridSize;
	this->blockSize = blockSize;
	this->weight = weight;
	this->side = gridSize / blockSize;
}

vector<vector<int>> GOL::getNewGrid(bool populated)
{
	vector<vector<int>> newGrid;

	for (int i = 0; i < side; i++)
	{
		vector<int> row;

		for (int j = 0; j < side; j++)
		{
			if (populated)	row.push_back(getOneZero());
			else row.push_back(0);
		}

		newGrid.push_back(row);
	}

	return newGrid;
}

int GOL::getOneZero()
{
	if ((rand() % 100) + 1 <= weight) return 1;
	else return 0;
}

void GOL::run()
{
	srand(time(0));

	int groupSum = 0;

	vector<vector<int>> grid = getNewGrid(true);
	vector<vector<int>> bbGrid;

	RenderWindow window(VideoMode(gridSize, gridSize), "Game of Life", Style::Close);
	window.setFramerateLimit(30);

	RectangleShape square;
	square.setSize(Vector2f(blockSize, blockSize));

	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed) window.close();
		}

		window.clear();

		// Print grid to window as blocks
		for (int x = 0; x < side; x++)
		{
			for (int y = 0; y < side; y++)
			{
				if (grid[x][y] == 1)
				{
					square.setPosition(Vector2f(x * blockSize, y * blockSize));
					window.draw(square);
				}
			}
		}

		window.display();

		bbGrid = grid;
		grid = getNewGrid(false);

		// GOL logic
		for (int x = 0; x < side; x++)
		{
			for (int y = 0; y < side; y++)
			{
				if (y + 1 < side) groupSum += bbGrid[x][y + 1];
				if (x + 1 < side && y + 1 < side) groupSum += bbGrid[x + 1][y + 1];
				if (x + 1 < side) groupSum += bbGrid[x + 1][y];
				if (x + 1 < side && y > 0) groupSum += bbGrid[x + 1][y - 1];
				if (y > 0) groupSum += bbGrid[x][y - 1];
				if (x > 0 && y > 0) groupSum += bbGrid[x - 1][y - 1];
				if (x > 0) groupSum += bbGrid[x - 1][y];
				if (x > 0 && y + 1 < side) groupSum += bbGrid[x - 1][y + 1];

				if (bbGrid[x][y] == 1 && (groupSum == 2 || groupSum == 3)) grid[x][y] = 1;
				else if (bbGrid[x][y] == 0 && groupSum == 3) grid[x][y] = 1;
				else grid[x][y] = 0;

				groupSum = 0;
			}
		}
	}
}
