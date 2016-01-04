#pragma once
#include "cocos2d.h"

class MainMenuScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	bool setNumPlayers(std::string input);

	// implement the "static create()" method manually
	CREATE_FUNC(MainMenuScene);
private:

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event);
	void startGame(cocos2d::Ref * pSender);
	void setNumPlayersToDefault();

	int numPlayers;
	cocos2d::ui::EditBox * _editPlayers;
};
