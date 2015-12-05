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

	//Default scheduler
	scheduleUpdate();

	//Add touch listener to the scene
	auto listenerTouch = EventListenerTouchOneByOne::create();
	listenerTouch->setSwallowTouches(false);
	listenerTouch->onTouchBegan = CC_CALLBACK_2(BattleScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerTouch, this);

	//Obtain map layer from cocos studio design file
	mapLayer = new MapLayer();
	mapLayer->create(static_cast<ui::ScrollView *>(rootNode->getChildByName("ScrollView_1")));

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
	mapLayer->scrollMapRight();
	buttonLeft->setVisible(true);
	buttonRight->setVisible(false);
}

void BattleScene::buttonLeftClickCallBack(cocos2d::Ref *pSender)
{
	log("Battle Scene Left Button Clicked");
	mapLayer->scrollMapLeft();
	buttonRight->setVisible(true);
	buttonLeft->setVisible(false);
}

bool BattleScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	log("Battle Scene Touch Began");
	auto sprite1 = Sprite::create("StartScene//tony.png");
	int pointY = touch->getLocation().y;
	if (pointY>=DOWNROWY&&pointY<=MIDDLEROWY)
		mapLayer->addMonster(sprite1,DOWN);
	else if (pointY > MIDDLEROWY&&pointY <= UPROWY)
		mapLayer->addMonster(sprite1, MIDDLE);
	else if (pointY > UPROWY&&pointY <= LIMITY)
		mapLayer->addMonster(sprite1, UP);
	return true;
}

void BattleScene::update(float dt)
{
	log("Battle Scene update");
}

void BattleScene::randomEnemy()
{
	mapLayer
}