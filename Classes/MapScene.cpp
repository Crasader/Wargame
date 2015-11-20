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
	this->qDown = 0;  this->wDown = 0; this->eDown = 0; 
	this->aDown = 0;  this->sDown = 0; this->dDown = 0;

	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto map_view = TMXTiledMap::create("sea.tmx");
	this->mapRef = map_view;

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
	
	this->scheduleUpdate();
	return true;
}

void MapScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_W:
			wDown = 0;
			break;
		case EventKeyboard::KeyCode::KEY_S:
			sDown = 0;
			break;
		case EventKeyboard::KeyCode::KEY_A:
			aDown = 0;
			break;
		case EventKeyboard::KeyCode::KEY_D:
			dDown = 0;
			break;
		case EventKeyboard::KeyCode::KEY_Q:
			qDown = 0;
			break;
		case EventKeyboard::KeyCode::KEY_E:
			eDown = 0;
			break;
	}
}

void MapScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_W:
			wDown = 1;
			break;
		case EventKeyboard::KeyCode::KEY_S:
			sDown = 1;
			break;
		case EventKeyboard::KeyCode::KEY_A:
			aDown = 1;
			break;
		case EventKeyboard::KeyCode::KEY_D:
			dDown = 1;
			break;
		case EventKeyboard::KeyCode::KEY_Q:
			qDown = 1;
			break;
		case EventKeyboard::KeyCode::KEY_E:
			eDown = 1;
			break;
	}
}

void MapScene::update(float delta)
{
	float dX = (dDown * -1.0) + (aDown * 1.0);
	float dY = (wDown * -1.0) + (sDown * 1.0);
	float dScale = (qDown * -0.005) + (eDown * 0.005);

	Vec2 newPos(mapRef->getPositionX() + dX, mapRef->getPositionY() + dY);

	this->mapRef->setScale(mapRef->getScale() + dScale);
	this->mapRef->setPosition(newPos);
}


