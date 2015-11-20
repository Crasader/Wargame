#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "PlayerModule.h"

class HelloWorld : public cocos2d::Layer
{
public:
	PlayerModule playermodule;
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    //CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
