#pragma once

#include "MapModel.h"

class RandomMapModel : public MapModel
{
public:
	RandomMapModel(int n_islands, int area_min, int area_max);

private:
	void growIsland(int x, int y, int backdir);
	bool deburr();
};