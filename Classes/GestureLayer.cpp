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
#define queue_width 55
#define queue_Height 60
#define monster_width 120
#define monster_height 100
int most_left = 0, most_right = 0, bottom = 0, up = 0;
bool in_gesture = 0;
Monster *choose_monster = NULL;
DollarRecognizer::Path2D path;
bool GestureLayer::init(MapLayer * map)
{
	mapLayer = map;
	//this->setContentSize(CCSizeMake(WIDTH,640));
	Recog = new DollarRecognizer::GeometricRecognizer;
	Recog->loadTemplates();
	this->setTouchEnabled(true);
	log("geture init");
	auto listenerTouch = EventListenerTouchOneByOne::create();
	listenerTouch->setSwallowTouches(false);
	listenerTouch->onTouchBegan = CC_CALLBACK_2(GestureLayer::onTouchBegan, this);
	listenerTouch->onTouchMoved = CC_CALLBACK_2(GestureLayer::onTouchMoved, this);
	listenerTouch->onTouchEnded = CC_CALLBACK_2(GestureLayer::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerTouch, this);

	scheduleUpdate();
	schedule(schedule_selector(GestureLayer::OneSecondUpdate), 1.0f);
	return true;
}
bool GestureLayer::onTouchBegan(Touch *touch,Event *unused_event)
{
	log("Gst touch began");
	log(3.7);
	path.clear();
	most_left = WIDTH, most_right = 0, up = HEIGHT, bottom = 0;
	auto point = touch->getLocation();
	if (point.x >= Gesture_left&&point.x <= Gesture_right&&point.y >= Gesture_bottom&&point.y <= Gesture_up)
	{
		//log("in_gesture");
		in_gesture = 1;
		choose_monster = NULL;
	}
	else
	{
		log("choose monster");
		in_gesture = 0;
		choose_monster = NULL;
		int i = 0;
		for (auto monster : monster_queue)
		{
			auto mon_position = monster->anim_body->getPosition();
			log(mon_position.x);
			log(mon_position.y);
			if (abs(point.x - mon_position.x) <= monster_width / 2 && abs(point.y - mon_position.y) <= monster_height / 2)
			{//this monster is chosen
				choose_monster = monster;
				break;
			}
			i++;
			if (i > 5) break;
		}
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
	if (in_gesture){//it's a gesture which can make a monster
		auto point = touch->getLocation();
		if (point.x < most_left) most_left = point.x;
		if (point.x > most_right) most_right = point.x;
		if (point.y > bottom) bottom = point.y;
		if (point.y < up) up = point.y;
		DollarRecognizer::Point2D pot;
		pot.x = point.x;
		pot.y = -point.y;
		path.push_back(pot);
		/*Partical*/
		auto particle = ParticleSystemQuad::create("touchBlue.plist");
		particle->setPosition(Point(touch->getLocation().x, touch->getLocation().y));
		this->addChild(particle);
		touchTrace_queue.pushBack(particle);

	} else
	if (choose_monster != NULL)
	{//there is a monster being chosen
	//bind this monster with the finger moves
		choose_monster->anim_body->setPosition(touch->getLocation());
	}
}
void GestureLayer::onTouchEnded(Touch *touch, Event *unused_event)
{ 
	for (auto part : touchTrace_queue)
	{
		part->removeFromParentAndCleanup(true);
	}
	if (in_gesture){ 
		log("build moster");
		DollarRecognizer::RecognitionResult result = Recog->recognize(path);
		Monster *newMonster=NULL;
		//log(result.name.c_str());
		if (result.name == "Rectangle")
		{ 
			double area = (most_right - most_left)*(up - bottom);
			if (area<0) area = -area;
			area = area*2 / (Whole_area);
			if (area > 1.5) area = 1.5;
			if (area < 0.5) area = 0.5;
			if (energe >= area*origin_life * 2)
			{//enough  energy
				//smaller than bigger, bigger than smaller
				newMonster = new RectMonster(Rect_attack, Rect_defence, area*origin_life * 2, false);
				energe -= area * origin_life * 2;
				newMonster->type = Rect;
			}
			else
			{//not enough, test if can draw a 0.5 scales monster
				if (energe >= 0.5*origin_life * 2)
				{
					newMonster = new RectMonster(Rect_attack, Rect_defence, 0.5*origin_life * 2, false);
					energe -= 0.5*origin_life * 2;
					newMonster->type = Rect;
				}
			}
		} else
		if (result.name == "Triangle")
		{
			double area = (most_right - most_left)*(up - bottom);
			if (area<0) area = -area;
			area = area*2 / (Whole_area);
			if (area > 1.5) area = 1.5;
			if (area < 0.5) area = 0.5;
			//smaller than bigger, bigger than smaller
			if (energe >= area*origin_life * 2.5)
			{//enough energy
				//smaller than bigger, bigger than smaller
				newMonster = new TriMonster(Tri_attack, Tri_defence, area*origin_life * 1, false);
				energe -= area * origin_life * 2.5;
				newMonster->type = Tri;
			}
			else
			{//not enough, test if can draw a 0.5 scales monster
				if (energe >= 0.5*origin_life * 2.5)
				{
					newMonster = new TriMonster(Tri_attack, Tri_defence, 0.5*origin_life * 1, false);
					energe -= 0.5*origin_life * 2.5;
					newMonster->type = Tri;
				}
			}
		} else 
		if (result.name=="Circle")
		{
			double area = (most_right - most_left)*(up - bottom)*0.9;
			if (area<0) area = -area;
			area = area*2 / (Whole_area);
			if (area > 1.5) area = 1.5;
			if (area < 0.5) area = 0.5;
			//smaller than bigger, bigger than smaller
			if (energe >= area*origin_life * 2.6)
			{//enough energy
				//smaller than bigger, bigger than smaller
				newMonster = new CircleMonster(Cir_attack, Cir_defence, area*origin_life * 1.5, false);
				energe -= area * origin_life * 2.6;
				newMonster->type = Cir;
			}
			else
			{//not enough, test if can draw a 0.5 scales monster
				if (energe >= 0.5*origin_life * 2.6)
				{
					newMonster = new CircleMonster(Cir_attack, Cir_defence, 0.5*origin_life * 1.5, false);
					energe -= 0.5*origin_life * 2.6;
					newMonster->type = Cir;
				}
			}
		} 
		if (newMonster){
			log(energe);
			newMonster->anim_body->setPosition(Point(-1000, -1000));
			//mapLayer->addMonster(newMonster, UP);
			monster_queue.pushBack(newMonster);
			updateQueue();
			this->addChild(newMonster->anim_body);
		}
	}else
	if (choose_monster)
	{
		Monster *tmp;
		switch (choose_monster->type){
		case Cir: 
			tmp = new CircleMonster(choose_monster->attack, choose_monster->defense, choose_monster->max_life, false);
			break;
			case Tri:
				tmp = new TriMonster(choose_monster->attack, choose_monster->defense, choose_monster->max_life, false);
				break;
			case Rect:
				tmp = new RectMonster(choose_monster->attack, choose_monster->defense, choose_monster->max_life, false);
				break;

		}
		auto drop_position = touch->getLocation();
		if (drop_position.y >= DOWNROWY&&drop_position.y <= LIMITY){
			//this->removeChild(choose_monster->anim_body);
			int pointY = drop_position.y;
			if (pointY >= DOWNROWY&&pointY <= MIDDLEROWY)
				mapLayer->addMonster(tmp, DOWNROW);
			else if (pointY > MIDDLEROWY&&pointY <= UPROWY)
				mapLayer->addMonster(tmp, MIDDLEROW);
			else if (pointY > UPROWY&&pointY <= LIMITY)
				mapLayer->addMonster(tmp, UPROW);
			//choose_monster->anim_body->removeFromParent();
			this->removeChild(choose_monster->anim_body);
			monster_queue.eraseObject(choose_monster,false);
		}
		updateQueue();
	}
}
void GestureLayer::update(float dt)
{
	//log("update");
	
}
void GestureLayer::updateQueue()
{
	int i = 0;
	log("updateQueue");
	for (auto monster : monster_queue)
	{
		monster->anim_body->setPositionY(queue_Height);
		monster->anim_body->setPositionX(queue_width + monster_width*i);
		i++;
		if (i >= 5) break;
	}
}
void GestureLayer::OneSecondUpdate(float dt)
{
	energe += 5;
}
