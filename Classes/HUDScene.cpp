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
	_messageLabel = CCLabelTTF::create("Game started", "Montserrat-Regular", 12,
		CCSizeMake(100, 64));
	_messageLabel->setColor(Color3B::BLUE);

	_messageLabel->setAnchorPoint(Vec2::ZERO);
	_messageLabel->setPosition(Vec2(visibleSize.width * (1/10), visibleSize.height * (1/10)));

	addChild(_messageLabel, 1);

	auto bg = cocos2d::LayerColor::create(Color4B(255, 255, 255, 255), GLfloat(visibleSize.width), GLfloat(50));
	this->addChild(bg);
	/*
	std::string pNormalSprite = "green_edit.png";
	Size editBoxSize = Size(100, 20);
	this->_editSpeed = ui::EditBox::create(editBoxSize, ui::Scale9Sprite::create(pNormalSprite));
	_editSpeed->setPosition(Vec2(visibleSize.width - _editSpeed->getContentSize().width , 
		_editSpeed->getContentSize().height / 2));
	_editSpeed->setFontName("fonts/arial.ttf");
	_editSpeed->setFontSize(12);
	_editSpeed->setFontColor(Color3B::RED);
	_editSpeed->setText("1");
	_editSpeed->setPlaceholderFontColor(Color3B::WHITE);
	_editSpeed->setMaxLength(3);
	//_editSpeed->setReturnType(ui::EditBox::KeyboardReturnType::DONE); 
	//this was in the example, but I don't think it does anything
	this->addChild(this->_editSpeed);
	*/
	
	return true;

}

void HUDScene::setLabel(std::string m)
{
	_messageLabel->setString(m);
}

