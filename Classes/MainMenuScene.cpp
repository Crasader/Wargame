#include "MainMenuScene.h"
#include "MapScene.h"

USING_NS_CC;

cocos2d::Scene * MainMenuScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainMenuScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool MainMenuScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	Vector<MenuItem*> MenuItems;

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MainMenuScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	//http://www.cocos2d-x.org/programmersguide/6/#menu-and-menu-items
	auto startItem = MenuItemImage::create(
		"startButton.png",
		"startButtonSelected.png",
		CC_CALLBACK_1(MainMenuScene::startGame, this));

	startItem->setPosition(Vec2(startItem->getContentSize().width / 2,startItem->getContentSize().height));

	MenuItems.pushBack(closeItem);
	MenuItems.pushBack(startItem);

	// create menu, it's an autorelease object
	auto menu = Menu::createWithArray(MenuItems);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	std::string pNormalSprite = "green_edit.png";
	Size editBoxSize = Size(100, 20);
	this->_editPlayers = ui::EditBox::create(editBoxSize, ui::Scale9Sprite::create(pNormalSprite));
	_editPlayers->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 3 / 4));
	_editPlayers->setFontName("fonts/arial.ttf");
	_editPlayers->setFontSize(12);
	_editPlayers->setFontColor(Color3B::RED);
	_editPlayers->setPlaceHolder("# of Players");
	_editPlayers->setPlaceholderFontColor(Color3B::WHITE);
	_editPlayers->setMaxLength(8);
	_editPlayers->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	this->addChild(this->_editPlayers);

	setNumPlayersToDefault();

	/////////////////////////////
	// 3. add your codes below...

	// create and initialize a label

	auto label = Label::createWithTTF("Press P or click Go! to begin", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("HelloWorld.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 30));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);

	//creating touch listener to wait for P key to be pressed
	/*
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	*/
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(MainMenuScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void MainMenuScene::menuCloseCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

bool MainMenuScene::setNumPlayers(std::string input)
{
	char* p;
	int converted = strtol(input.c_str(), &p, 10);
	if (*p) {
		// conversion failed because the input wasn't a number
		CCLog("invalid input, please input a number");
		return false;
	}
	else {
		// use converted
		if (converted <= 0)
		{
			CCLog("invalid input, number was less than 0");
			return false;
		}
		else
		{
			this->numPlayers = converted;
			return true;
		}
	}
}

void MainMenuScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_P)
	{
		//identical to calling startGame, but for some reason there is no way to put in the proper parameter at this point
		startGame(nullptr);
	}
}

void MainMenuScene::startGame(cocos2d::Ref * pSender)
{
	if (setNumPlayers(_editPlayers->getText()))
	{
		auto scene = MapScene::createScene(numPlayers);
		Director::getInstance()->replaceScene(scene);
	}
	else
	{
		CCLog("please input a proper value for numPlayers");
	}
}

void MainMenuScene::setNumPlayersToDefault()
{
	numPlayers = 3;
}


