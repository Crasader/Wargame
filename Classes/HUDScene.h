#pragma once

#include "cocos2d.h"

class HUDScene : public cocos2d::Layer
{
public:
	HUDScene();
	~HUDScene();

	static cocos2d::Layer* createLayer();
	void initOptions(const std::string& _message);

	virtual void draw(cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform,
		bool transformUpdated);

	inline virtual cocos2d::CCLabelTTF* getMessageLabel() { return _messageLabel; };

private:
	cocos2d::CCLabelTTF* _messageLabel;
}; 
