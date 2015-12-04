#ifndef __START_SCENE_H__
#define __START_SCENE_H__
#include "ui/CocosGUI.h"

USING_NS_CC;

#include "cocos2d.h"

class StartScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	//Touch began function
	bool onTouchBegan(Touch *touch, Event *unused_event);

	//Touch end function
	void onTouchEnded(Touch *touch, Event *unused_event);

	//Pressed button_Start function
	void buttonStartClickCallBack(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(StartScene);
};

#endif // __START_SCENE_H__
