#pragma once

#include "cocos2d.h"

class MapGenerator
{
public:
	MapGenerator(int n_islands, int passes);
	~MapGenerator();

	static const int width = 100;
	static const int height = 60;

	enum cell_type { LAND = 1, FOREST = 2, BEACH = 3, SEA = 4 };
	cell_type ** map;

private:

	bool inBounds(int x, int y);
	void makeIslet(int x, int y);
	void growIsland(int x, int y, int passes);
	void forestify();

	void generateMap(int num_islands, int growth_passes);
};
