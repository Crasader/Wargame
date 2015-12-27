#include "RandomMapModel.h"


RandomMapModel::RandomMapModel(int n_islands, int area_min, int area_max) : MapModel(100, 60)
{
	std::srand(time(NULL));

	while (n_islands-- > 0)
	{
		int x = CCRANDOM_0_1() * this->width;
		int y = CCRANDOM_0_1() * this->height;

		int passes = area_min + (int)(CCRANDOM_0_1() * (area_max - area_min));

		while (passes-- > 0)
		{
			growIsland(x, y, (int)(CCRANDOM_0_1() * 8));
		}
	}

	while (deburr()) {}

	this->tmxView = cocos2d::TMXTiledMap::create("base100x60.tmx");
	auto layer = ((cocos2d::TMXTiledMap *)(this->tmxView))->getLayer("Layer0");

	for (int y = 0; y < 60; y++)
	{
		for (int x = 0; x < 100; x++)
		{
			int gid;

			switch (this->getCellTypeAt(x, y))
			{
			case MapModel::CellType::COAST:
				gid = 1;
				break;
			case MapModel::CellType::LAND:
				gid = 8;
				break;
			default:
				gid = 11;
				break;
			}

			layer->setTileGID(gid, cocos2d::Vec2(x, y));
		}
	}
}

void RandomMapModel::growIsland(int x, int y, int diag)
{
	if (!inBounds(x, y)) return;

	if (cells[y][x] == CellType::LAND)
	{
		int dir = (diag + 6 + (int)(CCRANDOM_0_1() * 5)) % 8;
		int xp = x + cellAdj[dir][0];
		int yp = y + cellAdj[dir][1];
		growIsland(xp, yp, diag);
	}
	else
	{
		cells[y][x] = CellType::LAND;
	}
}

bool RandomMapModel::deburr()
{
	int burrs[100][2];
	int num_burrs = 0;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (cells[y][x] == CellType::LAND)
			{
				int num_seas = 0;

				for (int i = 0; i < 8; i++)
				{
					int xp = x + cellAdj[i][0];
					int yp = y + cellAdj[i][1];
					if (!inBounds(xp, yp) || cells[yp][xp] == CellType::SEA)
					{
						num_seas++;
					}
				}

				if (num_seas >= 6 && num_burrs < 100)
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
		cells[burrs[num_burrs][1]][burrs[num_burrs][0]] = CellType::SEA;
	}

	return burred;
}
