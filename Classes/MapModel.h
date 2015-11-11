#pragma once

#include "cocos2d.h"

class MapModel
{
public:
	static const int width = 100;
	static const int height = 60;

	enum cell_type { LAND, COAST, SEA };
	
	MapModel();
	~MapModel();

	cell_type getCellTypeAt(int x, int y);
	
protected:
	static const int cell_adj[][2];

	cell_type ** map;
	bool inBounds(int x, int y);
};
