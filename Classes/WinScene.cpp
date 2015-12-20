#include "WinScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* WinScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = WinScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool WinScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("EndScene/WinScene.csb");

	auto btnContinue = static_cast<ui::Button *>(rootNode->getChildByName("Button_Continue"));
	btnContinue->addClickEventListener(CC_CALLBACK_1(WinScene::buttonStartClickCallBack, this));

	addChild(rootNode);

	return true;
}

void WinScene::buttonStartClickCallBack(cocos2d::Ref* pSender)
{
	log("WinScene button continue clicked");
	Director::getInstance()->popScene();
	Director::getInstance()->popSceneWithTransition<TransitionFade>(1.0f);
}
