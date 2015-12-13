#include "StartScene.h"
#include "MenuScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline; 
using namespace ui;

Scene* StartScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = StartScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StartScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	log("begin!");
	log("StartScene Load csb Revised");
    auto rootNode = CSLoader::createNode("StartScene/StartScene.csb");
	log("StartScene Loaded csb Revised");

    addChild(rootNode);

	//Add button_Start listener
	Button *buttonStart = static_cast<Button *>(rootNode->getChildByName("Button_Start"));
	buttonStart->addClickEventListener(CC_CALLBACK_1(StartScene::buttonStartClickCallBack, this));

	//Add Z Order to lable and button and wallpaper
	Sprite *img = static_cast<Sprite *>(rootNode->getChildByName("backgroundStart"));
	img->setGlobalZOrder(0);
	img = static_cast<Sprite *>(rootNode->getChildByName("lblTitle_1"));
	img->setGlobalZOrder(2);
	img = static_cast<Sprite *>(rootNode->getChildByName("lblTitle_2"));
	img->setGlobalZOrder(2);

	//Add touch listener
	auto listenerTouch = EventListenerTouchOneByOne::create();
	listenerTouch->setSwallowTouches(false);
	listenerTouch->onTouchBegan = CC_CALLBACK_2(StartScene::onTouchBegan, this);
	listenerTouch->onTouchEnded = CC_CALLBACK_2(StartScene::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerTouch, this);

	//Add some moving tony
	//addMovingTony(200, 200);
	//addMovingTony(300, 300);
	//addMovingTony(400, 400);
	//addMovingTony(500, 500);

    return true;
}

bool StartScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	log("StartScene Touched");
	return true;
}

void StartScene::onTouchEnded(Touch *touch, Event *unused_event)
{
	log("StartScene Ended");
}

void StartScene::buttonStartClickCallBack(cocos2d::Ref* pSender)
{
	log("StartScene Start Button Clicked");
	log("create scene");
	auto menuScene = MenuScene::createScene();
	log("create transition");
	auto transition = TransitionFade::create(1.0f, menuScene);
	Director::getInstance()->pushScene(Director::getInstance()->getRunningScene());
	Director::getInstance()->replaceScene(transition);
}

void StartScene::addMovingTony(int x, int y)
{
	log("StartScene::addMovingTony 1");
	auto sp = Sprite::create("StartScene/tony.png");
	log("StartScene added MovingTony");
	sp->setGlobalZOrder(1);
	log("StartScene set tony position");
	sp->setPosition(Point(x,y));

	log("StartScene::addMovingTony move To");
	auto moveTo = JumpBy::create(4, Point(300, 0), 20, 8);
	log("StartScene::addMovingTony flip to");
	auto flipTo = FlipX::create(true);
	log("StartScene::addMovingTony create action");
	auto action = RepeatForever::create(Sequence::create(moveTo, flipTo, moveTo->reverse(), flipTo->reverse(), NULL));
	log("StartScene::addMovingTony run action");
	sp->runAction(action);
	log("StartScene::addMovingTony add child");
	this->addChild(sp);
	log("StartScene::addMovingTony complete");
}
