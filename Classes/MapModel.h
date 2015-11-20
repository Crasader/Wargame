#pragma once

#include "cocos2d.h"

class MapModel
{
public:
	enum CellType { LAND, COAST, SEA };
	
	MapModel() : MapModel(100, 60) {}
	MapModel(int width, int height);
	~MapModel();

	cocos2d::Node * getView();
	CellType getCellTypeAt(int x, int y);
	
protected:
	static const int cellAdj[][2];

	cocos2d::Node * view;
	CellType ** cells;
	int width;
	int height;

	void init(int width, int height);
	bool inBounds(int x, int y);
};
