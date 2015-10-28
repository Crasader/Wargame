#include "MapScene.h"
#include "MapGenerator.h"

USING_NS_CC;

Scene* MapScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MapScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool MapScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto map = TMXTiledMap::create("sea.tmx");

	MapGenerator mg(20, 20);
	auto layer = map->getLayer("Layer0");

	for (int y = 0; y < 60; y++)
	{
		for (int x = 0; x < 100; x++)
		{
			int gid = (int)mg.map[y][x];
			layer->setTileGID(gid, Vec2(x, y));
		}
	}


	map->setScale(0.25);
	map->setAnchorPoint(Vec2(0.5, 0.5));
	map->setPosition(Vec2(visibleSize.width / 2 + origin.x - map->getPositionX(), visibleSize.height / 2 + origin.y - map->getPositionY()));

	this->addChild(map, 0);

	return true;
}
