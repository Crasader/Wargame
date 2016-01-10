#include "MapScene.h"
#include "HUDScene.h"
#include "RandomMapModel.h"

USING_NS_CC;

Scene* MapScene::createScene(int numplayers)
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MapScene::create();
	//create PlayerModule after init()
	layer->playerModule = new PlayerModule(numplayers);

	// add layer as a child to scene
	scene->addChild(layer, 0);


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
	movementSpeed = 1;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//TODO: we are using this in all the Scenes, so make this into some sort of inline, DRY principle

	this->mapModel = new TMXMapModel("base100x60.tmx");
	this->_mapView = this->mapModel->getView();

	this->_mapView->setScale(0.30f);
	this->_mapView->setAnchorPoint(Vec2(0.5, 0.5));
	this->_mapView->setPosition(Vec2(visibleSize.width / 2 + origin.x - this->_mapView->getPositionX(), visibleSize.height / 2 + origin.y - this->_mapView->getPositionY()));

	this->addChild(this->_mapView, 0, "map");

	auto selectSprite = Sprite::create("select.png");
	selectSprite->setAnchorPoint(Vec2(0, 0));
	selectSprite->setOpacity(0);
	this->_mapView->addChild(selectSprite, 10, "select");

	auto tmxGround = ((TMXTiledMap *)(this->_mapView))->getLayer("Layer0");

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
			std::stringstream ss;
			ss << tile->getPositionX() << "," << tile->getPositionY() << "]";
			_hud->setLabel(ss.str());
		}
		else
		{
			selectSprite->setOpacity(0);
		}

		return true;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this->_mapView);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(MapScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(MapScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	_hud = HUDScene::create();
	this->addChild(_hud, 1, "hud");
	
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
			wDown = movementSpeed;
			break;
		case EventKeyboard::KeyCode::KEY_S:
			sDown = movementSpeed;
			break;
		case EventKeyboard::KeyCode::KEY_A:
			aDown = movementSpeed;
			break;
		case EventKeyboard::KeyCode::KEY_D:
			dDown = movementSpeed;
			break;
		case EventKeyboard::KeyCode::KEY_Q:
			qDown = movementSpeed;
			break;
		case EventKeyboard::KeyCode::KEY_E:
			eDown = movementSpeed;
			break;
		case EventKeyboard::KeyCode::KEY_T:
			nextTurn();
			break;
	}
}

void MapScene::update(float delta)
{
	float dX = (dDown * -1.0) + (aDown * 1.0);
	float dY = (wDown * -1.0) + (sDown * 1.0);
	float dScale = (qDown * -0.005) + (eDown * 0.005);
	//TODO:prevent user from zooming out at a range slightly larger than the size of the map
	Vec2 newPos(this->_mapView->getPositionX() + dX, this->_mapView->getPositionY() + dY);

	this->_mapView->setScale(_mapView->getScale() + dScale);
	this->_mapView->setPosition(newPos);
}

void MapScene::nextTurn()
{
	playerModule->nextTurn();
	const char * id = playerModule->getCurrentPlayerID();
	//with some math, pray that a player doesn't name himself with more than 78 characters (I hate constants)
	//we should make a limit on the size of character names when asked, something reasonable
	std::stringstream ss;
	ss << id << "is now current player.";
	CCLog(ss.str().c_str());
	_hud->setLabel(ss.str());
}


