#include"GestureLayer.h"
#include"GeometricRecognizer.h"
#include"GeometricRecognizerTypes.h"
#define WIDTH 2000
#define HEIGHT 1000
#define Gesture_left 200
#define Gesture_right 800
#define Gesture_up 900
#define Gesture_bottom 160
#define Whole_area (Gesture_up-Gesture_bottom)*(Gesture_right-Gesture_left)
#define queue_width 160
#define queue_Height 60
#define monster_width 80
int most_left = 0, most_right = 0, bottom = 0, up = 0;
bool in_gesture = 0;
DollarRecognizer::Path2D path;
bool GestureLayer::init(MapLayer * map)
{
	mapLayer = map;
	Recog = new DollarRecognizer::GeometricRecognizer;
	Recog->loadTemplates();
	this->setTouchEnabled(true);
	log("geture init");
	auto listenerTouch = EventListenerTouchOneByOne::create();
	listenerTouch->setSwallowTouches(false);
	listenerTouch->onTouchBegan = CC_CALLBACK_2(GestureLayer::onTouchBegan, this);
	listenerTouch->onTouchMoved = CC_CALLBACK_2(GestureLayer::onTouchMoved, this);
	listenerTouch->onTouchEnded = CC_CALLBACK_2(GestureLayer::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listenerTouch, 1);
	auto monster_queue_sprite = Sprite::create("BattleScene/monster_queue.png");
	//monster_queue_sprite->setScaleX(2.5);
	monster_queue_sprite->setPosition(Point(queue_width,queue_Height));
	this->addChild(monster_queue_sprite,100);
	scheduleUpdate();
	return true;
}
bool GestureLayer::onTouchBegan(Touch *touch,Event *unused_event)
{
	log("Gst touch began");
	path.clear();
	most_left = WIDTH, most_right = 0, up = HEIGHT, bottom = 0;
	auto point = touch->getLocation();
	if (point.x >= Gesture_left&&point.x <= Gesture_right&&point.y >= Gesture_bottom&&point.y <= Gesture_up)
	{
		log("in_gesture");
		in_gesture = 1;
	}
	else
	{
		in_gesture = 0;
	}
	//test if the touch in the gesture part
	DollarRecognizer::Point2D pot;
	pot.x = point.x;
	pot.y = -point.y;
	path.push_back(pot);
	return true;
}
void GestureLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
	if (in_gesture){
		auto point = touch->getLocation();
		if (point.x < most_left) most_left = point.x;
		if (point.x > most_right) most_right = point.x;
		if (point.y > bottom) bottom = point.y;
		if (point.y < up) up = point.y;
		DollarRecognizer::Point2D pot;
		pot.x = point.x;
		pot.y = -point.y;
		path.push_back(pot);
	}
}
void GestureLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
	if (in_gesture){
		log("build moster");
		DollarRecognizer::RecognitionResult result = Recog->recognize(path);
		Monster *newMonster=NULL;
		log(result.name.c_str());
		if (result.name == "Rectangle")
		{
			double area = (most_right - most_left)*(up - bottom);
			area = area / (Whole_area);
			newMonster = new RectMonster(Rect_attack,Rect_defence,area*origin_life*3,false);
			energe -= area * origin_life * 2;
		} else
		if (result.name == "Triangle")
		{
			double area = (most_right - most_left)*(up - bottom)/2;
			area = area / (Whole_area);
			newMonster = new TriMonster(Tri_attack, Tri_defence, area*origin_life * 3, false);
			energe -= area * origin_life * 2*1.5;
		} else 
		if (result.name=="Circle")
		{
			double area = (most_right - most_left)*(up - bottom)*0.9;
			area = area / (Whole_area);
			newMonster = new CircleMonster(Rect_attack, Rect_defence, area*origin_life * 3, false);
			energe -= area * origin_life * 2;
		} 
		if (newMonster){
			log(energe);
			newMonster->anim_body->setPosition(Point(queue_width, queue_Height));
			//mapLayer->addMonster(newMonster, UP);
			this->addChild(newMonster->anim_body, 100);
			monster_queue.pushBack(newMonster);
		}
	}
}
void GestureLayer::update(float dt)
{
	log("update");
	int i = 0;
	for (auto monster:monster_queue)
	{
		monster->anim_body->setPositionX(queue_width+monster_width*i);
		i++;
	}
}
void GestureLayer::OneSecondUpdate(float dt)
{

}