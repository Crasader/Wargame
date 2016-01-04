#include "HUDScene.h"
USING_NS_CC;

Scene* HUDScene::createScene()
{
	Scene* a = new Scene();
	
	auto hud = HUDScene::create();

	a->addChild(hud);

	return a;
}

bool HUDScene::init()
{
	//call superconstructor
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//creating a simple message label to be positioned at the center
	_messageLabel = CCLabelTTF::create("Hello World", "Marker Felt", 12,
		CCSizeMake(245, 32), kCCTextAlignmentCenter);
	_messageLabel->setColor(Color3B(255, 215, 0));

	_messageLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 30));

	addChild(_messageLabel, 1);

	return true;

}

void HUDScene::changeLabel(std::string m)
{
	_messageLabel->setString(m);
}