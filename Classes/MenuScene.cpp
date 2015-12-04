#include "MenuScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;

Scene* MenuScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MenuScene::create();

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

	auto rootNode = CSLoader::createNode("MenuScene//MenuScene.csb");

	//Add button_stage1selected
	Button *buttonStage1 = static_cast<Button*>(rootNode->getChildByName("PageView_2")->getChildByName("Panel_1")->getChildByName("button_stage1selected"));
	buttonStage1->addClickEventListener(CC_CALLBACK_1(MenuScene::buttonStage1ClickCallBack, this));

	addChild(rootNode);

	return true;
}

void MenuScene::buttonStage1ClickCallBack(cocos2d::Ref* pSender)
{
	log("MenuScene Stage Button 1 Clicked");
}
