#include "MapModel.h"

const int MapModel::cell_adj[][2] = {
	{ 0, -1 },
	{ 1, -1 },
	{ 1, 0 },
	{ 1, 1 },
	{ 0, 1 },
	{ -1, 1 },
	{ -1, 0 },
	{ -1, -1 }
};

MapModel::MapModel()
{
	map = new cell_type*[height];

	for (int y = 0; y < height; y++)
	{
		map[y] = new cell_type[width];

		for (int x = 0; x < width; x++)
		{
			map[y][x] = cell_type::SEA;
		}
	}
}

MapModel::~MapModel()
{
}

MapModel::cell_type MapModel::getCellTypeAt(int x, int y)
{
	return map[y][x];
}

bool MapModel::inBounds(int x, int y)
{
	return (x >= 0 && x < width && y >= 0 && y < height);
}
