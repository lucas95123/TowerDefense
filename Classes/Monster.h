#ifndef __MONSTER_H__
#define __MONSTER_H__

#define ROWHEIGHT 120
#define DOWNROWY 200
#define MIDDLEROWY DOWNROWY+ROWHEIGHT
#define UPROWY MIDDLEROWY+ROWHEIGHT
#define LIMITY UPROWY+ROWHEIGHT
#define STARTX 20
#define UP 2
#define MIDDLE 1
#define DOWN 0
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#define Rec_pic "StartScene//tony.png"
#define Tri_pic "BattleScene//test1.jpg"
#define Cir_pic "BattleScene//test2.jpg"
#define Stay_in_queue 1
#define Hit_back 2
#define Move_foward 3
#define origin_life 50.0
USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;
using namespace cocostudio;
class Monster:public Node
{
private:
	int state=Stay_in_queue;
public:
	int attack, life_point, max_life;
	Sprite *anim_body;
	Monster(int _attack,int _max_life) :attack(_attack), max_life(_max_life){
		
	}
	~Monster(){}
	void setState(int _state){ state = _state; }
	int getState(){ return state; }
};

class RectMonster:public Monster
{
private:

public:
	RectMonster(int _attack,int _max_life):Monster(_attack,_max_life){
		anim_body = Sprite::create(Rec_pic);
		anim_body->setScaleX(_max_life / origin_life);
		anim_body->setScaleY(_max_life / origin_life);//change the size of the monster
	}
	~RectMonster(){}
};

class TriMonster:public Monster
{
private:

public:
	TriMonster(int _attack, int _max_life) :Monster(_attack, _max_life)
	{
		anim_body = Sprite::create(Tri_pic);
		anim_body->setScaleX(_max_life / origin_life);
		anim_body->setScaleY(_max_life / origin_life);
	}
	~TriMonster(){}
};

class CircleMonster:public Monster
{
public:
	CircleMonster(int _attack,int _max_life) :Monster(_attack,_max_life){
		anim_body = Sprite::create(Cir_pic);
		anim_body->setScaleX(_max_life / origin_life);
		anim_body->setScaleY(_max_life / origin_life);
	}
	~CircleMonster(){}

private:

};
#endif // __MONSTER_H__
