#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__
#include "ui/CocosGUI.h"

USING_NS_CC;
#include "cocos2d.h"

class MenuScene : public cocos2d::Layer
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

	//Pressed Button_StageSelected function
	void buttonStage1ClickCallBack(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(MenuScene);
};

#endif // __MENU_SCENE_H__