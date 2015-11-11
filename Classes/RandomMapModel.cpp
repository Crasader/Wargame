#include "RandomMapModel.h"


RandomMapModel::RandomMapModel(int n_islands, int area_min, int area_max) : MapModel()
{
	std::srand(time(NULL));

	while (n_islands-- > 0)
	{
		int x = CCRANDOM_0_1() * width;
		int y = CCRANDOM_0_1() * height;

		int passes = area_min + (int)(CCRANDOM_0_1() * (area_max - area_min));

		while (passes-- > 0)
		{
			growIsland(x, y, (int)(CCRANDOM_0_1() * 8));
		}
	}

	while (deburr()) {}
}

void RandomMapModel::growIsland(int x, int y, int diag)
{
	if (!inBounds(x, y)) return;

	if (map[y][x] == cell_type::LAND)
	{
		int dir = (diag + 6 + (int)(CCRANDOM_0_1() * 5)) % 8;
		int xp = x + cell_adj[dir][0];
		int yp = y + cell_adj[dir][1];
		growIsland(xp, yp, diag);
	}
	else
	{
		map[y][x] = cell_type::LAND;
	}
}

bool RandomMapModel::deburr()
{
	int burrs[width * height][2];
	int num_burrs = 0;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (map[y][x] == cell_type::LAND)
			{
				int num_seas = 0;

				for (int i = 0; i < 8; i++)
				{
					int xp = x + cell_adj[i][0];
					int yp = y + cell_adj[i][1];
					if (!inBounds(xp, yp) || map[yp][xp] == cell_type::SEA)
					{
						num_seas++;
					}
				}

				if (num_seas >= 6)
				{
					burrs[num_burrs][0] = x;
					burrs[num_burrs][1] = y;
					num_burrs++;
				}
			}
		}
	}

	bool burred = (num_burrs > 0);

	while (num_burrs > 0)
	{
		num_burrs--;
		map[burrs[num_burrs][1]][burrs[num_burrs][0]] = cell_type::SEA;
	}

	return burred;
}
