#ifndef __BATTLE_SCENE_H__
#define __BATTLE_SCENE_H__
#include "ui/CocosGUI.h"
#include "MapLayer.h"
#include "Monster.h"
#include "GestureLayer.h"
#include "WinScene.h"
#include "LoseScene.h"
#include "GestureLayer.h"
#include "cocostudio/CocoStudio.h"
using namespace cocostudio::timeline;
USING_NS_CC;

#include "cocos2d.h"

class BattleScene : public cocos2d::Layer
{
private: 
	MapLayer *mapLayer;//ZOrder 0
	GestureLayer *gestureLayer;//ZOrder
	Layer *functionLayer;//ZOrder
	Layer *pauseLayer;//ZOrder
	Sprite *lifeBar;
	Sprite *magicBar;
	ui::Button *buttonPause;
	ui::Button *buttonLeft;
	ui::Button *buttonRight;
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	//overriding default scheduler
	void update(float dt) override;

	//custom AI scheduler of triangle
	void triangleAI(float dt);

	//custom AI scheduler of circle
	void circleAI(float dt);

	//custom AI scheduler of rec
	void rectAI(float dt);

	//Wining condition
	void ifwin(float dt);
	//Touch began function
	bool onTouchBegan(Touch *touch, Event *unused_event);

	//Pressed Button_Resume function
	void buttonResumeClickCallBack(cocos2d::Ref* pSender);

	//Pressed Button_Back function
	void buttonBackClickCallBack(cocos2d::Ref* pSender);

	//Pressed Button_Sound function
	void buttonSoundClickCallBack(cocos2d::Ref* pSender);

	//Pressed Button_Pause function
	void buttonPauseClickCallBack(cocos2d::Ref* pSender);

	//Pressed Button_Left function
	void buttonLeftClickCallBack(cocos2d::Ref* pSender);

	//Pressed Button_Rigjt function
	void buttonRightClickCallBack(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(BattleScene);
};

#endif // __BATTLE_SCENE_H__