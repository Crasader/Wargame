#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;
using namespace cocos2d::extension;

//regarding using Delegates
//http://techbirds.in/how-to-use-textbox-or-editbox-in-cocos2d-x/
class MainMenuScene : public Layer, public EditBoxDelegate
{
public:
	static Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(Ref* pSender);

	bool setNumPlayers(std::string input);

	virtual void editBoxEditingDidBegin(EditBox* editBox);
	virtual void editBoxEditingDidEnd(EditBox* editBox);
	virtual void editBoxTextChanged(EditBox* editBox, std::string &text);
	virtual void editBoxReturn(EditBox * editBox);

	// implement the "static create()" method manually
	CREATE_FUNC(MainMenuScene);
private:

	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event);
	void startGame(Ref * pSender);
	void setNumPlayersToDefault();



	int numPlayers;
	ui::EditBox * _editPlayers;

};
