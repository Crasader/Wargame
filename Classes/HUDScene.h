#pragma once

#include "cocos2d.h"

class HUDScene : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene();
	virtual bool init();
	void setLabel(std::string m);

	CREATE_FUNC(HUDScene);

	inline cocos2d::CCLabelTTF* getMessageLabel() { return _messageLabel; };

private:
	cocos2d::CCLabelTTF* _messageLabel;
	cocos2d::ui::EditBox * _editSpeed;
}; 
