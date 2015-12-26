#include "HUDScene.h"
HUDScene::HUDScene() {}

HUDScene::~HUDScene() {}

cocos2d::Layer* HUDScene::createLayer()
{
	const std::string _message = "The enemy is approaching!";
	HUDScene* a = new HUDScene();
	a->create();
	a->setColor(cocos2d::Color3B(0, 0, 0));

	a->setContentSize(cocos2d::Size::Size(1, 1));
	a->setAnchorPoint(cocos2d::Vec2(0, 0));

	a->initOptions(_message);

	return a;
}

void HUDScene::initOptions(const std::string& _message)
{
	_messageLabel = cocos2d::CCLabelTTF::create(_message.c_str(), "Marker Felt", 12,
		cocos2d::CCSizeMake(245, 32), cocos2d::kCCTextAlignmentCenter);
	_messageLabel->setColor(cocos2d::Color3B(255, 215, 0));

	addChild(_messageLabel, 1);

	_messageLabel->setPosition(cocos2d::Vec2(cocos2d::Director::getInstance()->getVisibleSize().width,
		cocos2d::Director::getInstance()->getVisibleSize().height));


}

void HUDScene::draw(cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform,
	bool transformUpdated) {}