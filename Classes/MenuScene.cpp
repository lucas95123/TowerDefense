#include "MenuScene.h"
#include "BattleScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;

Scene* MenuScene::createScene()
{
	// 'scene' is an autorelease object
	log("SCENE CREATE");
	auto scene = Scene::create();
	log("SCENE CREATE");
	// 'layer' is an autorelease object
	auto layer = MenuScene::create();
	log("SCENE CREATE");
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	log("MenuScene Read CSB");
	auto rootNode = CSLoader::createNode("MenuScene\\MenuScene.csb");
	log("MenuScene Read Complete");
	ui::PageView *pageView = static_cast<ui::PageView *>(rootNode->getChildByName("PageView_1"));
	//Add button_stageselected
	Button *buttonSelectStage = static_cast<Button*>(pageView->getChildByName("Panel_1")->getChildByName("Button_1"));
	buttonSelectStage->addClickEventListener(CC_CALLBACK_1(MenuScene::buttonStage1ClickCallBack, this));

	//Add touch listener
	auto listenerTouch = EventListenerTouchOneByOne::create();
	listenerTouch->setSwallowTouches(false);
	listenerTouch->onTouchBegan = CC_CALLBACK_2(MenuScene::onTouchBegan, this);
	listenerTouch->onTouchEnded = CC_CALLBACK_2(MenuScene::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerTouch, this);

	addChild(rootNode);

	return true;
}

void MenuScene::buttonStage1ClickCallBack(cocos2d::Ref* pSender)
{
	log("MenuScene Stage Select Button Clicked");
	auto battleScene = BattleScene::createScene();
	auto transition = TransitionFade::create(1.0f, battleScene);
	Director::getInstance()->pushScene(Director::getInstance()->getRunningScene());
	Director::getInstance()->replaceScene(transition);
}

//Touch began function
bool MenuScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}

//Touch end function
void MenuScene::onTouchEnded(Touch *touch, Event *unused_event)
{

}
