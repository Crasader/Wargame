#include "MapModel.h"

const int MapModel::cellAdj[][2] = {
	{ 0, -1 },
	{ 1, -1 },
	{ 1, 0 },
	{ 1, 1 },
	{ 0, 1 },
	{ -1, 1 },
	{ -1, 0 },
	{ -1, -1 }
};

MapModel::MapModel(int width, int height)
{
	this->init(width, height);
}

MapModel::~MapModel()
{
	delete view;
	for (int y = 0; y < this->height; y++)
	{
		delete[] cells[y];
	}
	delete[] cells;
}

cocos2d::Node * MapModel::getView()
{
	return this->view;
}

MapModel::CellType MapModel::getCellTypeAt(int x, int y)
{
	return cells[y][x];
}

void MapModel::init(int width, int height)
{
	this->width = width;
	this->height = height;
	this->cells = new CellType*[this->height];

	for (int y = 0; y < this->height; y++)
	{
		this->cells[y] = new CellType[this->width];

		for (int x = 0; x < width; x++)
		{
			this->cells[y][x] = CellType::SEA;
		}
	}
}

bool MapModel::inBounds(int x, int y)
{
	return (x >= 0 && x < this->width && y >= 0 && y < this->height);
}
