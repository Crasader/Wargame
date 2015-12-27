#include "MapScene.h"
#include "HUDScene.h"
#include "RandomMapModel.h"

USING_NS_CC;

Scene* MapScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MapScene::create();
	auto hud = HUDScene::create();

	// add layer as a child to scene
	scene->addChild(layer, 0);
	scene->addChild(hud, 1);

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

	this->mapModel = new TMXMapModel("base100x60.tmx");
	this->mapView = this->mapModel->getView();

	this->mapView->setScale(0.30);
	this->mapView->setAnchorPoint(Vec2(0.5, 0.5));
	this->mapView->setPosition(Vec2(visibleSize.width / 2 + origin.x - this->mapView->getPositionX(), visibleSize.height / 2 + origin.y - this->mapView->getPositionY()));

	this->addChild(this->mapView, 0, "map");

	auto selectSprite = Sprite::create("select.png");
	selectSprite->setAnchorPoint(Vec2(0, 0));
	selectSprite->setOpacity(0);
	this->mapView->addChild(selectSprite, 10, "select");

	auto tmxGround = ((TMXTiledMap *)(this->mapView))->getLayer("Layer0");

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);

	touchListener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		auto tgt = (TMXTiledMap *)(event->getCurrentTarget());
		auto ground = tgt->getLayer("Layer0");
		auto mapDim = ground->getLayerSize();
		auto mapBox = ground->getBoundingBox();
		auto location = tgt->convertTouchToNodeSpace(touch);
		auto selectSprite = tgt->getChildByName("select");

		if (mapBox.containsPoint(location))
		{
			float width = mapBox.getMaxX() - mapBox.getMinX();
			float height = mapBox.getMaxY() - mapBox.getMinY();

			float relX = location.x - mapBox.getMinX();
			float relY = location.y - mapBox.getMinY();

			int tileX = relX * (mapDim.width / width);
			int tileY = mapDim.height - (relY * (mapDim.height / height));

			auto tile = ground->getTileAt(Vec2(tileX, tileY));
			selectSprite->setPosition(tile->getPosition());
			selectSprite->setOpacity(0xff);
		}
		else
		{
			selectSprite->setOpacity(0);
		}

		return true;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this->mapView);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(MapScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(MapScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	this->scheduleUpdate();
	playerModule = new PlayerModule(3);

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
		case EventKeyboard::KeyCode::KEY_T:
			(*playerModule).nextTurn();
			CCLog("switching player");
			break;
	}
}

void MapScene::update(float delta)
{
	float dX = (dDown * -1.0) + (aDown * 1.0);
	float dY = (wDown * -1.0) + (sDown * 1.0);
	float dScale = (qDown * -0.005) + (eDown * 0.005);

	Vec2 newPos(this->mapView->getPositionX() + dX, this->mapView->getPositionY() + dY);

	this->mapView->setScale(mapView->getScale() + dScale);
	this->mapView->setPosition(newPos);
}


