#include "TMXMapModel.h"

TMXMapModel::TMXMapModel(std::string fname)
{
	auto tmx = cocos2d::TMXTiledMap::create(fname);
	this->tmxView = tmx;
	auto dim = tmx->getLayer("Layer0")->getLayerSize();
	this->init(dim.width, dim.height);
}