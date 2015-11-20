#include "MapScene.h"
#include "RandomMapModel.h"

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

	auto map_view = TMXTiledMap::create("sea.tmx");

	RandomMapModel map_model(20, 80, 80);
	auto layer = map_view->getLayer("Layer0");

	for (int y = 0; y < 60; y++)
	{
		for (int x = 0; x < 100; x++)
		{
			int gid;

			switch (map_model.getCellTypeAt(x, y))
			{
			case MapModel::cell_type::COAST:
				gid = 1;
				break;
			case MapModel::cell_type::LAND:
				gid = 8;
				break;
			default:
				gid = 11;
				break;
			}

			layer->setTileGID(gid, Vec2(x, y));
		}
	}

	map_view->setScale(0.30);
	map_view->setAnchorPoint(Vec2(0.5, 0.5));
	map_view->setPosition(Vec2(visibleSize.width / 2 + origin.x - map_view->getPositionX(), visibleSize.height / 2 + origin.y - map_view->getPositionY()));

	this->addChild(map_view, 0, "map");

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(MapScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(MapScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	return true;
}

void MapScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	log("Key with keycode %d released", keyCode);

	auto tgt = (MapScene *)(event->getCurrentTarget());
	auto map = (TMXTiledMap *)(tgt->getChildByName("map"));
	auto layer = map->getLayer("Layer0");
	auto tile = layer->getTileAt(Vec2(0, 0));
	tile->setOpacity(0);
}
