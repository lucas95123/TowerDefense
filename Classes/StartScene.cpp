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
    
    auto rootNode = CSLoader::createNode("StartScene/StartScene.csb");

    addChild(rootNode);

	//Add button_Start listener
	Button *buttonStart = static_cast<Button*>(rootNode->getChildByName("Button_Start"));
	buttonStart->addClickEventListener(CC_CALLBACK_1(StartScene::buttonStartClickCallBack, this));

	//Add touch listener
	auto listenerTouch = EventListenerTouchOneByOne::create();
	listenerTouch->setSwallowTouches(false);
	listenerTouch->onTouchBegan = CC_CALLBACK_2(StartScene::onTouchBegan, this);
	listenerTouch->onTouchEnded = CC_CALLBACK_2(StartScene::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerTouch, this);

    return true;
}

bool StartScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	log("StartScene Touched");
	/*create Vector<Sprite*>*/
	auto sp = Sprite::create("StartScene//tony.png");
	sp->setPosition(Point(touch->getLocation().x, touch->getLocation().y));
	this->addChild(sp);
	return true;
}

void StartScene::onTouchEnded(Touch *touch, Event *unused_event)
{
	log("StartScene Ended");
}

void StartScene::buttonStartClickCallBack(cocos2d::Ref* pSender)
{
	log("StartScene Start Button Clicked");
	auto menuScene = MenuScene::createScene();
	auto transition = TransitionFade::create(1.0f, menuScene);
	Director::getInstance()->pushScene(Director::getInstance()->getRunningScene());
	Director::getInstance()->replaceScene(transition);
}
