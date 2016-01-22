#include "TMXMapModel.h"

TMXMapModel::TMXMapModel(std::string fname)
{
	auto tmx = cocos2d::TMXTiledMap::create(fname);
	this->tmxView = tmx;
	auto ground = tmx->getLayer("Layer0");
	auto dim = ground->getLayerSize();
	this->init(dim.width, dim.height);

	for (int x = 0; x < dim.width; x++)
	{
		for (int y = 0; y < dim.height; y++)
		{
			if (ground->getTileGIDAt(cocos2d::Vec2(x, y)) != 11)
			{
				this->cells[y][x] = CellType::LAND;
			}
		}
	}
}