#ifndef _GESTURELAYER_H_
#define _GESTURELAYER_H_
#include "cocos2d.h"
#include"GeometricRecognizer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MapLayer.h"
#include "Monster.h"
#include <iostream>
#include <cmath>
#define max_energe 200
USING_NS_CC;
using namespace cocostudio::timeline;
using namespace cocos2d::ui;
class GestureLayer:public Layer
{
public:
	virtual bool init(MapLayer *);
	void update(float dt) override;
	void OneSecondUpdate(float dt);
	void updateQueue();
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);
	int energe = max_energe;
private:
	
	DollarRecognizer::GeometricRecognizer* Recog;
	MapLayer *mapLayer;
	Vector<Monster *> monster_queue;
	Vector<ParticleSystemQuad *>touchTrace_queue;

};


#endif