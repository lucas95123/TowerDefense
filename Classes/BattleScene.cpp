#include "BattleScene.h"

int jerryHealth = 20;
int tonyHealth = 40;
int ceaserHealth = 60;

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

	auto rootNode = CSLoader::createNode("BattleScene/BattleScene.csb");
	//Default scheduler
	scheduleUpdate();
	schedule(schedule_selector(BattleScene::ifwin), 2.0f);
	schedule(schedule_selector(BattleScene::triangleAI), 5.0f);
	schedule(schedule_selector(BattleScene::circleAI), 10.0f);
	schedule(schedule_selector(BattleScene::rectAI), 20.0f);

	//Obtain map layer from cocos studio design file
	mapLayer = new MapLayer();
	mapLayer->create(static_cast<ui::ScrollView *>(rootNode->getChildByName("ScrollView_1")), player_castle_life, enemy_castle_life);

	//Obtain pause layer from cocos studio design file and hide it
	pauseLayer = static_cast<Layer *>(rootNode->getChildByName("Layer_Pause"));
	pauseLayer->setVisible(false);
	pauseLayer->setZOrder(5);

	//create the gesture Layer
	gestureLayer = new GestureLayer();
	gestureLayer->init(mapLayer);
	gestureLayer->setZOrder(3);

	//Obtain function layer from cocos studio design file
	functionLayer = static_cast<Layer *>(rootNode->getChildByName("Layer_Funct"));
	functionLayer->setZOrder(1);

	//Obtain buttons in pause layer
	auto buttonResume = static_cast<ui::Button *>(pauseLayer->getChildByName("Panel_1")->getChildByName("Button_Resume"));
	buttonResume->addClickEventListener(CC_CALLBACK_1(BattleScene::buttonResumeClickCallBack, this));

	auto buttonBack = static_cast<ui::Button *>(pauseLayer->getChildByName("Panel_1")->getChildByName("Button_Back"));
	buttonBack->addClickEventListener(CC_CALLBACK_1(BattleScene::buttonBackClickCallBack, this));

	auto buttonSound = static_cast<ui::Button *>(pauseLayer->getChildByName("Panel_1")->getChildByName("Button_Sound"));
	buttonSound->addClickEventListener(CC_CALLBACK_1(BattleScene::buttonSoundClickCallBack, this));
	
	//Obtain life bar from cocos studio design file
	lifeBar = static_cast<Sprite *>(functionLayer->getChildByName("life_bar"));
	magicBar = static_cast<Sprite *>(functionLayer->getChildByName("magic_bar"));

	buttonPause = static_cast<ui::Button*>(functionLayer->getChildByName("Button_Pause"));
	buttonPause->addClickEventListener(CC_CALLBACK_1(BattleScene::buttonPauseClickCallBack, this));

	//Obtain left scroll button in function layer
	buttonLeft = static_cast<ui::Button *>(functionLayer->getChildByName("Button_Left"));
	buttonLeft->setVisible(false);
	buttonLeft->addClickEventListener(CC_CALLBACK_1(BattleScene::buttonLeftClickCallBack, this));

	//Obtain right scroll button in function layer
	buttonRight = static_cast<ui::Button *>(functionLayer->getChildByName("Button_Right"));
	buttonRight->addClickEventListener(CC_CALLBACK_1(BattleScene::buttonRightClickCallBack, this));

	//Initial Monsters
	triangleAI(0);

	rootNode->addChild(gestureLayer);
	addChild(rootNode);

	return true;
}

void BattleScene::buttonResumeClickCallBack(cocos2d::Ref *pSender)
{
	log("Battle Scene Resume Button Clicked");
	Director::getInstance()->resume();
	pauseLayer->setVisible(false);
}

void BattleScene::buttonBackClickCallBack(cocos2d::Ref *pSender)
{
	log("Battle Scene Back Button Clicked");
	Director::getInstance()->resume();
	Director::getInstance()->popSceneWithTransition<TransitionFade>(1.0f);
}

void BattleScene::buttonSoundClickCallBack(cocos2d::Ref *pSender)
{
	log("Battle Scene Sound Button Clicked");
	auto buttonSound = static_cast<ui::Button *>(pauseLayer->getChildByName("Panel_1")->getChildByName("Button_Sound"));
	pauseLayer->setVisible(false);
}

void BattleScene::buttonPauseClickCallBack(cocos2d::Ref *pSender)
{
	log("Battle Scene Pause Button Clicked");
	Director::getInstance()->pause();
	pauseLayer->setVisible(true);
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
	return true;
}

void BattleScene::update(float dt)
{
	//log("Battle Scene update");
	mapLayer->checkCollision();
	if (gestureLayer->energe > 200)
		gestureLayer->energe = 200;

	if (mapLayer->Enemy_Castle_life_point < 200)
		jerryHealth = 40;

	lifeBar->setScaleX(mapLayer->Player_Castle_life_point/500.0*0.74);
	magicBar->setScaleX(gestureLayer->energe / 200.0*1.09);
}

void BattleScene::triangleAI(float dt)
{
	log("Triangle AI");
	int row = random<int>(0, 6);
	if (row < 3)
	{
		int delayDist = random<int>(0, 80);
		Monster* sprite1 = new TriMonster(10, 5, jerryHealth, true);
		mapLayer->addEnemy(sprite1, row, delayDist);
	}
	row = random<int>(0, 6);
	if (row < 3)
	{
		int delayDist = random<int>(0, 80);
		Monster* sprite2 = new TriMonster(10, 5, jerryHealth, true);
		mapLayer->addEnemy(sprite2, row, delayDist);
	}
	row = random<int>(0, 6);
	if (row < 3)
	{
		int delayDist = random<int>(0, 80);
		Monster* sprite3 = new TriMonster(10, 5, jerryHealth, true);
		mapLayer->addEnemy(sprite3, row,delayDist);
	}
}

void BattleScene::rectAI(float dt)
{
	log("RectAI");
}

void BattleScene::circleAI(float dt)
{
	log("CircleAI");
}

void BattleScene::ifwin(float dt)
{
	//log("ifwin");
	int flag = mapLayer->Castle_damage();
	if (flag != Nothing)
	{
		auto winScene = WinScene::createScene();
		auto winTransition = TransitionFade::create(1.0f, winScene);

		auto loseScene = LoseScene::createScene();
		auto loseTransition = TransitionFade::create(1.0f, loseScene);

		switch (flag)
		{
		case Win:
			Director::getInstance()->pushScene(Director::getInstance()->getRunningScene());
			Director::getInstance()->replaceScene(winTransition);
			break;
		case Lose:
			Director::getInstance()->pushScene(Director::getInstance()->getRunningScene());
			Director::getInstance()->replaceScene(loseTransition);
			break;
		}
	}
}
