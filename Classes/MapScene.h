#pragma once

#include "cocos2d.h"
#include "TMXMapModel.h"
#include "PlayerModule.h"

class MapScene : public cocos2d::Layer 
{
	private:

		void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event);
		void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event);
		void update(float delta);

		int wDown, sDown, aDown, dDown, qDown, eDown;
		cocos2d::Node * mapView;
		TMXMapModel * mapModel;
		PlayerModule * playerModule;

	public:

		// there's no 'id' in cpp, so we recommend returning the class instance pointer
		static cocos2d::Scene* createScene();

		// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
		virtual bool init();

		// implement the "static create()" method manually
		CREATE_FUNC(MapScene);
};
