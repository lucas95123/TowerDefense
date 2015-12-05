#include "BattleScene.h"
#include "cocostudio/CocoStudio.h"

using namespace cocostudio::timeline;

Scene* BattleScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = BattleScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool BattleScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("BattleScene//BattleScene.csb");

	//Add touch listener to the scene
	auto listenerTouch = EventListenerTouchOneByOne::create();
	listenerTouch->setSwallowTouches(false);
	listenerTouch->onTouchBegan = CC_CALLBACK_2(BattleScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerTouch, this);

	//Obtain map layer from cocos studio design file
	mapLayer = static_cast<ui::ScrollView *>(rootNode->getChildByName("Layer_Map")->getChildByName("ScrollView_3"));
	//Map is not touch enabled
	mapLayer->setTouchEnabled(false);

	//Obtain function layer from cocos studio design file
	functionLayer = static_cast<Layer *>(rootNode->getChildByName("Layer_Funct"));

	//Obtain left scroll button in function layer
	buttonLeft = static_cast<ui::Button *>(functionLayer->getChildByName("Button_Left"));
	buttonLeft->setVisible(false);
	buttonLeft->addClickEventListener(CC_CALLBACK_1(BattleScene::buttonLeftClickCallBack, this));

	//Obtain right scroll button in function layer
	buttonRight = static_cast<ui::Button *>(functionLayer->getChildByName("Button_Right"));
	buttonRight->addClickEventListener(CC_CALLBACK_1(BattleScene::buttonRightClickCallBack, this));

	addChild(rootNode);

	return true;
}

void BattleScene::buttonRightClickCallBack(cocos2d::Ref *pSender)
{
	log("Battle Scene Right Button Clicked");
	if (mapScrollPercentage == 100.0f)
		return;
	mapScrollPercentage += 100.0f;
	buttonLeft->setVisible(true);
	mapLayer->scrollToPercentHorizontal(mapScrollPercentage, 1.0f, false);
	if (mapScrollPercentage == 100.0f)
		buttonRight->setVisible(false);
}

void BattleScene::buttonLeftClickCallBack(cocos2d::Ref *pSender)
{
	log("Battle Scene Left Button Clicked");
	if (mapScrollPercentage == 0.0f)
		return;
	mapScrollPercentage -= 100.0f;
	buttonRight->setVisible(true);
	mapLayer->scrollToPercentHorizontal(mapScrollPercentage, 1.0f, false);
	if (mapScrollPercentage == 0.0f)
		buttonLeft->setVisible(false);
}

bool BattleScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	log("Battle Scene Touch Began");
	return true;
}
