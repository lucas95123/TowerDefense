#ifndef __BATTLE_SCENE_H__
#define __BATTLE_SCENE_H__
#include "ui/CocosGUI.h"

USING_NS_CC;

#include "cocos2d.h"

class BattleScene : public cocos2d::Layer
{
private: 
	ui::ScrollView *mapLayer;
	ui::Button *buttonLeft;
	ui::Button *buttonRight;
	Layer *functionLayer;
	float mapScrollPercentage=0;
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	//Touch began function
	bool onTouchBegan(Touch *touch, Event *unused_event);

	//Pressed Button_Left function
	void buttonLeftClickCallBack(cocos2d::Ref* pSender);

	//Pressed Button_Rigjt function
	void buttonRightClickCallBack(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(BattleScene);
};

#endif // __BATTLE_SCENE_H__