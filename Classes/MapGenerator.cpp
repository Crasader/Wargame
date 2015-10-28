#include "MapGenerator.h"

static const int cell_adj[][2] = {
	{ 0, -1 },
	{ 1, -1 },
	{ 1, 0 },
	{ 1, 1 },
	{ 0, 1 },
	{ -1, 1 },
	{ -1, 0 },
	{ -1, -1 }
};

MapGenerator::MapGenerator(int n_islands, int passes)
{
	std::srand(time(NULL));

	map = new cell_type*[height];

	for (int y = 0; y < height; y++)
	{
		map[y] = new cell_type[width];

		for (int x = 0; x < width; x++)
		{
			map[y][x] = cell_type::SEA;
		}
	}

	generateMap(n_islands, passes);
}


MapGenerator::~MapGenerator()
{
}

bool MapGenerator::inBounds(int x, int y)
{
	return (x >= 0 && x < width && y >= 0 && y < height);
}

void MapGenerator::generateMap(int num_islands, int growth_passes)
{
	for (int i = 0; i < num_islands; i++)
	{
		int x = CCRANDOM_0_1() * width;
		int y = CCRANDOM_0_1() * height;

		growIsland(x, y, growth_passes);
	}

	forestify();
}

void MapGenerator::makeIslet(int x, int y)
{
	map[y][x] = cell_type::LAND;

	for (int i = 0; i < 8; i++)
	{
		int xn = x + cell_adj[i][0];
		int yn = y + cell_adj[i][1];

		if (inBounds(xn, yn) && map[yn][xn] == cell_type::SEA)
		{
			map[yn][xn] = cell_type::BEACH;
		}
	}
}

void MapGenerator::growIsland(int x, int y, int passes)
{
	if (passes <= 1 || !inBounds(x, y) || map[y][x] == cell_type::LAND) return;

	makeIslet(x, y);

	int i = CCRANDOM_0_1() * 8;
	int x_adj = cell_adj[i][0];
	int y_adj = cell_adj[i][1];

	growIsland(x + x_adj, y + y_adj, passes - 2);
	growIsland(x - x_adj, y - y_adj, passes - 2);
}

void MapGenerator::forestify()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (map[y][x] == cell_type::BEACH)
			{
				bool landlocked = true;

				for (int i = 0; i < 8; i++)
				{
					int xn = x + cell_adj[i][0];
					int yn = y + cell_adj[i][1];

					if (inBounds(xn, yn) && map[yn][xn] == cell_type::SEA)
					{
						landlocked = false;
						break;
					}
				}

				if (landlocked)
				{
					map[y][x] = cell_type::FOREST;
				}
			}
		}
	}
}
