#include "TMXMapModel.h"

TMXMapModel::TMXMapModel(std::string fname)
{
	auto tmx = cocos2d::TMXTiledMap::create(fname);
	this->view = tmx;
	this->init(100, 60);
}