#ifndef __MONSTER_H__
#define __MONSTER_H__

#define ROWHEIGHT 140
#define DOWNROWY 200
#define MIDDLEROWY DOWNROWY+ROWHEIGHT
#define UPROWY MIDDLEROWY+ROWHEIGHT
#define LIMITY UPROWY+ROWHEIGHT
#define STARTX 20
#define UPROW 2
#define MIDDLEROW 1
#define DOWNROW 0
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#define Rec_pic "BattleScene/TonyMini.png"
#define Tri_pic "BattleScene/JerryMini.png"
#define Cir_pic "BattleScene/CeaserMini.png"
#define Rec_Hit_back_anim "Rec_Cry"
#define Tri_Hit_back_anim "Tri_Cry"
#define Cir_Hit_back_anim "Cir_Cry"
#define Rec_Moving_forward_anim "Rec_attack"
#define Tri_Moving_forward_anim "Tri_attack"
#define Cir_Moving_forward_anim "Cir_attack"
#define Rec_Hit_back_pic ""
#define Cir_Hit_back_pic ""
#define Tri_Hit_back_pic ""
#define Stay_in_queue 1
#define Hit_back 2
#define Move_foward 3
#define DEAD 4
#define Dying 5
#define origin_life 30.0
#define Rect_attack 8
#define Cir_attack 12
#define Tri_attack 10
#define Rect_defence 10
#define Tri_defence 5
#define Cir_defence 0
#define Remove_seconds(x) isEnemy?(x)*15/1800:(1-(x)/1800.0)*15 
#define Move_to_line (Line==(UPROW))?UPROWY:(Line==(MIDDLEROW))?MIDDLEROWY:DOWNROWY
#define Map_width 1800
USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;
using namespace cocostudio;
class Monster:public Ref
{
private:
	
	int state=Stay_in_queue;
public:
	int Line;
	int attack, life_point, max_life,defense,isEnemy;
	Sprite *anim_body;
	Monster(int _attack,int _defense,int _max_life,int _isEnemy) :attack(_attack), max_life(_max_life),defense(_defense),isEnemy(_isEnemy){
		life_point = max_life;
		
	}
	~Monster(){}
	void setState(int _state){ state = _state; }
	int getState(){ return state; }
	//void retain(){}
	static void BattleEach(AnimationCache* cache,Monster *a, Monster *b)
	{
		if (a->getState() != Move_foward || b->getState() != Move_foward) return;
		//log("Hit Back");
		a->anim_body->stopAllActions();
		b->anim_body->stopAllActions();
		int damage_A = b->attack - a->defense;
		int damage_B= a->attack - b->defense;
		if (damage_A <= 0) damage_A = 1;
		if (damage_B <= 0) damage_B = 1;
		a->life_point -= damage_A;
		b->life_point -= damage_B;
		if (a->life_point <= 0) a->setState(Dying);
		if (b->life_point <= 0) b->setState(Dying);
		if (a->life_point > 0)a->BeHitback(cache, damage_A); else a->ChooseDeath(cache);
		if (b->life_point > 0)b->BeHitback(cache, damage_B); else b->ChooseDeath(cache);
	}
	virtual void BeHitback(AnimationCache*,int damage) = 0;//needed three Animation
	virtual void MovingForward(AnimationCache*) = 0;
	virtual void ChooseDeath(AnimationCache*) = 0;
};

class RectMonster:public Monster
{
private:
	int back_x = -1;//store the x value the monster move back to 
public:
	RectMonster(int _attack,int _defense,int _max_life,int _isEnemy):Monster(_attack,_defense,_max_life,_isEnemy){
		anim_body = Sprite::create(Rec_pic);
		anim_body->setScaleX(_max_life / origin_life);
		anim_body->setScaleY(_max_life / origin_life);//change the size of the monster
		//anim_body->setFlippedY(true);
		if (isEnemy) anim_body->setFlippedX(true);
	}
	~RectMonster(){}
	virtual void BeHitback(AnimationCache* cache,int damage)
	{
		//log("BeHitback");
		auto animate = Animate::create(cache->getAnimation(Rec_Hit_back_anim));
		this->anim_body->runAction(RepeatForever::create(Sequence::create(animate, animate->reverse(), NULL)));
		int Delta = isEnemy ? damage * 10 : -damage * 10;
		int change_Y = (Move_to_line) - this->anim_body->getPositionY();

		auto action = Sequence::create(JumpBy::create(0.2, Point(Delta,change_Y), 50, 1),CCCallFunc::create(CC_CALLBACK_0(Monster::MovingForward,this,cache)), NULL);
		action->setTag(Hit_back);
		this->setState(Hit_back);
		this->anim_body->runAction(action);
	}
	virtual void MovingForward(AnimationCache* cache)
	{
		//log("MovingForward");
		auto animate = Animate::create(cache->getAnimation(Rec_Moving_forward_anim));
		if (!isEnemy)this->anim_body->runAction(RepeatForever::create(Sequence::create(animate, animate->reverse(), NULL)));
		else this->anim_body->runAction(RepeatForever::create(Sequence::create(animate, NULL)));
		this->setState(Move_foward);
		int x = this->anim_body->getPositionX();
		int TargetPoint;
		TargetPoint = isEnemy ? 80 : Map_width;
		auto action = Sequence::create(JumpTo::create(Remove_seconds(x), Point(TargetPoint, Move_to_line),20,2*Remove_seconds(x)), NULL);
		action->setTag(Move_foward);
		this->anim_body->runAction(action);
	}
	virtual void ChooseDeath(AnimationCache* cache)
	{
		this->anim_body->stopAllActions();
		this->setState(DEAD);
		//this->anim_body->removeFromParent();
	}
};

class TriMonster:public Monster
{
private:

public:
	TriMonster(int _attack,int _defense, int _max_life,int _isEnemy) :Monster(_attack,_defense, _max_life,_isEnemy)
	{
		anim_body = Sprite::create(Tri_pic);
		anim_body->setScaleX(_max_life / origin_life);
		anim_body->setScaleY(_max_life / origin_life);
		//anim_body->setFlippedY(true);
		if (isEnemy) anim_body->setFlippedX(true);
	}
	~TriMonster(){}
	virtual void BeHitback(AnimationCache* cache,int damage)
	{
		//log("BeHitback");
		auto animate = Animate::create(cache->getAnimation(Tri_Hit_back_anim));
		this->anim_body->runAction(RepeatForever::create(Sequence::create(animate, animate->reverse(), NULL)));
		int Delta = isEnemy ? damage * 10 : -damage * 10;
		int change_Y = (Move_to_line)-this->anim_body->getPositionY();

		auto action = Sequence::create(JumpBy::create(0.2, Point(Delta, change_Y), 20, 1), CCCallFunc::create(CC_CALLBACK_0(Monster::MovingForward, this, cache)), NULL);
		action->setTag(Hit_back);
		this->setState(Hit_back);
		this->anim_body->runAction(action);
	}
	virtual void MovingForward(AnimationCache* cache)
	{
		//log("MovingForward");
		auto animate = Animate::create(cache->getAnimation(Tri_Moving_forward_anim));
		if (!isEnemy)this->anim_body->runAction(RepeatForever::create(Sequence::create(animate, animate->reverse(), NULL)));
		else this->anim_body->runAction(RepeatForever::create(Sequence::create(animate, NULL)));
		this->setState(Move_foward);
		int x = this->anim_body->getPositionX();
		int TargetPoint;
		TargetPoint = isEnemy ? 80 : Map_width;
		auto action = Sequence::create(MoveTo::create(Remove_seconds(x), Point(TargetPoint, Move_to_line)), NULL);
		action->setTag(Move_foward);
		this->anim_body->runAction(action);
	}
	virtual void ChooseDeath(AnimationCache* cache)
	{
		this->anim_body->stopAllActions();
		this->setState(DEAD);
	}
};

class CircleMonster:public Monster
{
public:
	CircleMonster(int _attack,int _defense,int _max_life,int _isEnemy) :Monster(_attack,_defense,_max_life,_isEnemy){
		anim_body = Sprite::create(Cir_pic);
		anim_body->setScaleX(_max_life / origin_life);
		anim_body->setScaleY(_max_life / origin_life);
		//anim_body->setFlippedY(true);
		if (isEnemy) anim_body->setFlippedX(true);
	}
	~CircleMonster(){}
	virtual void BeHitback(AnimationCache* cache,int damage)
	{
		//log("BeHitback");
		auto animate = Animate::create(cache->getAnimation(Cir_Hit_back_anim));
		this->anim_body->runAction(RepeatForever::create(Sequence::create(animate, animate->reverse(), NULL)));
		int Delta = isEnemy ? damage * 10 : -damage * 10;
		int change_Y = (Move_to_line)-this->anim_body->getPositionY();
		auto action = Sequence::create(JumpBy::create(0.2, Point(Delta, change_Y), 20, 1), CCCallFunc::create(CC_CALLBACK_0(Monster::MovingForward, this, cache)), NULL);
		action->setTag(Hit_back);
		this->setState(Hit_back);
		this->anim_body->runAction(action);
	}
	virtual void MovingForward(AnimationCache* cache)
	{
		//log("MovingForward");
		auto animate = Animate::create(cache->getAnimation(Cir_Moving_forward_anim));
		if (!isEnemy)this->anim_body->runAction(RepeatForever::create(Sequence::create(animate, animate->reverse(), NULL)));
		else
		this->anim_body->runAction(RepeatForever::create(Sequence::create(animate->reverse(), NULL)));
		this->setState(Move_foward);
		int x = this->anim_body->getPositionX();
		int TargetPoint;
		TargetPoint = isEnemy ? 80 : Map_width;
		auto action = Sequence::create(MoveTo::create(Remove_seconds(x), Point(TargetPoint, Move_to_line)), NULL);
		action->setTag(Move_foward);
		this->anim_body->runAction(action);
	}
	virtual void ChooseDeath(AnimationCache* cache)
	{
		this->anim_body->stopAllActions();
		this->setState(DEAD);
	}
private:

};
#endif // __MONSTER_H__
