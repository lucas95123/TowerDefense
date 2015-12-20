#include "LoseScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* LoseScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LoseScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool LoseScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("EndScene/LoseScene.csb");

	//Listener of btn continue
	auto btnContinue = static_cast<ui::Button *>(rootNode->getChildByName("LoseLayer")->getChildByName("Button_Continue"));
	btnContinue->addClickEventListener(CC_CALLBACK_1(LoseScene::buttonContClickCallBack, this));
	addChild(rootNode);

	return true;
}

void LoseScene::buttonContClickCallBack(cocos2d::Ref* pSender)
{
	log("Lose Scene Button Continue clicked");
	Director::getInstance()->popScene();
	//Director::getInstance()->popSceneWithTransition<TransitionFade>(1.0f);
}
