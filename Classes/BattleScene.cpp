#include "BattleScene.h"
#include "SimpleAudioEngine.h"

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

	//Play battle background music
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("battleBGM.mp3", true);

	auto rootNode = CSLoader::createNode("BattleScene/BattleScene.csb");
	//Default scheduler
	scheduleUpdate();
	schedule(schedule_selector(BattleScene::ifwin), 2.0f);
	schedule(schedule_selector(BattleScene::triangleAI), 8.0f);
	schedule(schedule_selector(BattleScene::circleAI), 23.0f);
	schedule(schedule_selector(BattleScene::rectAI), 15.0f);

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
	auto checkBoxSound = static_cast<ui::CheckBox *>(pauseLayer->getChildByName("Panel_1")->getChildByName("CheckBox_Sound"));

	checkBoxSound->addClickEventListener(CC_CALLBACK_1(BattleScene::buttonSoundClickCallBack, this));
	
	//Obtain life bar from cocos studio design file
	lifeBar = static_cast<Sprite *>(functionLayer->getChildByName("life_bar"));
	magicBar = static_cast<Sprite *>(functionLayer->getChildByName("magic_bar"));

	buttonPause = static_cast<ui::Button*>(functionLayer->getChildByName("Button_Pause"));
	buttonPause->addClickEventListener(CC_CALLBACK_1(BattleScene::buttonPauseClickCallBack, this));
	//skill buttons
	auto button_SKILL1 = static_cast<ui::Button*>(functionLayer->getChildByName("Button_114"));
	button_SKILL1->addClickEventListener(CC_CALLBACK_0(BattleScene::skill1, this));
	auto button_SKILL2 = static_cast<ui::Button*>(functionLayer->getChildByName("Button_115"));
	button_SKILL2->addClickEventListener(CC_CALLBACK_0(BattleScene::skill2, this));
	auto button_SKILL3 = static_cast<ui::Button*>(functionLayer->getChildByName("Button_116"));
	button_SKILL3->addClickEventListener(CC_CALLBACK_0(BattleScene::skill3, this));

	//Obtain left scroll button in function layer
	buttonLeft = static_cast<ui::Button *>(functionLayer->getChildByName("Button_Left"));
	buttonLeft->setVisible(false);
	buttonLeft->addClickEventListener(CC_CALLBACK_1(BattleScene::buttonLeftClickCallBack, this));

	//Obtain right scroll button in function layer
	buttonRight = static_cast<ui::Button *>(functionLayer->getChildByName("Button_Right"));
	buttonRight->addClickEventListener(CC_CALLBACK_1(BattleScene::buttonRightClickCallBack, this));

	jerryHealth = 20;
	tonyHealth = 40;
	ceaserHealth = 60;

	//Initial Monsters
	triangleAI(0);

	rootNode->addChild(gestureLayer);
	addChild(rootNode);

	return true;
}
void BattleScene::skill1()
{
	log("skill 1");
	if (cd_skill1 == 0){
		this->use_skill1 = 1;
		cd_skill1 = SKILL_CD1;
		auto button_SKILL1 = static_cast<ui::Button*>(functionLayer->getChildByName("Button_114"));
		auto ban = Sprite::create("BattleScene/Banpng.png");
		ban->setPosition(Point(64,64));
		button_SKILL1->addChild(ban);
	}
}
void BattleScene::skill2()
{
	log("skill 2");
	if (cd_skill2 == 0){ this->use_skill2 = 1; 
	cd_skill2 = SKILL_CD2;
	auto button_SKILL2 = static_cast<ui::Button*>(functionLayer->getChildByName("Button_115"));
	auto ban = Sprite::create("BattleScene/Banpng.png");
	ban->setPosition(Point(64, 64));
	button_SKILL2->addChild(ban);
	}
}
void BattleScene::skill3()
{
	log("skill 3");
	if (cd_skill3 == 0)  { this->use_skill3 = 1; 
	cd_skill3 = SKILL_CD3;
	auto button_SKILL3 = static_cast<ui::Button*>(functionLayer->getChildByName("Button_116"));
	auto ban = Sprite::create("BattleScene/Banpng.png");
	ban->setPosition(Point(64, 64));
	button_SKILL3->addChild(ban);
	}
}

void BattleScene::buttonResumeClickCallBack(cocos2d::Ref *pSender)
{
	log("Battle Scene Resume Button Clicked");
	auto checkBoxSound = static_cast<ui::CheckBox *>(pauseLayer->getChildByName("Panel_1")->getChildByName("CheckBox_Sound"));
	if (checkBoxSound->isSelected())
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	else
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
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
}

void BattleScene::buttonPauseClickCallBack(cocos2d::Ref *pSender)
{
	log("Battle Scene Pause Button Clicked");
	//Pause back ground music
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
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
	if (use_skill1)
	{
		mapLayer->JudgementMeteorolite();
		 use_skill1= 0;
	}
	if (use_skill2)
	{
		mapLayer->HolyWrath(); use_skill2 = 0;
	}
	if (use_skill3)
	{
		mapLayer->EvilFurious(); use_skill3 = 0;
	}
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
		int delayDist = random<int>(20, 100);
		Monster* sprite1 = new TriMonster(Tri_attack, Tri_defence, jerryHealth, true);
		mapLayer->addEnemy(sprite1, row, delayDist);
	}
	row = random<int>(0, 6);
	if (row < 3)
	{
		int delayDist = random<int>(20, 100);
		Monster* sprite2 = new TriMonster(Tri_attack, Tri_defence, jerryHealth, true);
		mapLayer->addEnemy(sprite2, row, delayDist);
	}
	row = random<int>(0, 6);
	if (row < 3)
	{
		int delayDist = random<int>(20, 80);
		Monster* sprite3 = new TriMonster(Tri_attack, Tri_defence, jerryHealth, true);
		mapLayer->addEnemy(sprite3, row,delayDist);
	}
}

void BattleScene::rectAI(float dt)
{
	log("RectAI");
	int row = random<int>(0, 6);
	if (row < 3)
	{
		int delayDist = random<int>(20, 160);
		Monster* sprite1 = new RectMonster(Rect_attack, Rect_defence, tonyHealth, true);
		mapLayer->addEnemy(sprite1, row, delayDist);
	}
	row = random<int>(0, 6);
	if (row < 3)
	{
		int delayDist = random<int>(20, 160);
		Monster* sprite2 = new RectMonster(Rect_attack, Rect_defence, tonyHealth, true);
		mapLayer->addEnemy(sprite2, row, delayDist);
	}
	row = random<int>(0, 6);
	if (row < 3)
	{
		int delayDist = random<int>(2, 160);
		Monster* sprite3 = new RectMonster(Rect_attack, Rect_defence, tonyHealth, true);
		mapLayer->addEnemy(sprite3, row, delayDist);
	}
}

void BattleScene::circleAI(float dt)
{
	log("CircAI");
	int row = random<int>(0, 6);
	if (row < 3)
	{
		int delayDist = random<int>(20, 160);
		Monster* sprite1 = new CircleMonster(Cir_attack, Cir_defence, ceaserHealth, true);
		mapLayer->addEnemy(sprite1, row, delayDist);
	}
	row = random<int>(0, 6);
	if (row < 3)
	{
		int delayDist = random<int>(20, 160);
		Monster* sprite2 = new CircleMonster(Cir_attack, Cir_defence, ceaserHealth, true);
		mapLayer->addEnemy(sprite2, row, delayDist);
	}
	row = random<int>(0, 6);
	if (row < 3)
	{
		int delayDist = random<int>(20, 160);
		Monster* sprite3 = new CircleMonster(Cir_attack, Cir_defence, ceaserHealth, true);
		mapLayer->addEnemy(sprite3, row, delayDist);
	}
}

void BattleScene::ifwin(float dt)
{
	//log("ifwin");
	if (cd_skill1 > 0){ cd_skill1--; 
	if (cd_skill1 == 0) static_cast<ui::Button*>(functionLayer->getChildByName("Button_114"))->removeAllChildren();
	}
	if (cd_skill2 > 0) { cd_skill2--; 
	if (cd_skill2 == 0) static_cast<ui::Button*>(functionLayer->getChildByName("Button_115"))->removeAllChildren();
	}
	if (cd_skill3 > 0){ cd_skill3--; 
	if (cd_skill3 == 0) static_cast<ui::Button*>(functionLayer->getChildByName("Button_116"))->removeAllChildren();
	}
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
