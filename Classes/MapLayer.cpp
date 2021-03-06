#include "MapLayer.h"
#include <iostream>

void MapLayer::create(ui::ScrollView * map,int _Enemy_life_point,int _Player_life_point)
{
	mapContainer = map;
	mapContainer->setTouchEnabled(false);
	mapContainer->setZOrder(2);
	this->Enemy_Castle_life_point = _Enemy_life_point;
	this->Player_Castle_life_point = _Player_life_point;
	//Initialize animations 
	auto cache = AnimationCache::getInstance();
	{
		auto animation = Animation::create();
		for (int i = 1; i < 9; i++)
		{
			char szName[100] = { 0 };
			sprintf(szName, "tony_%02d.png", i);
			animation->addSpriteFrameWithFile(szName);
		}
		animation->setDelayPerUnit(0.9f / 18.0f);
		animation->setRestoreOriginalFrame(true);//read rectangle monster
		cache->addAnimation(animation, Rec_Moving_forward_anim);
	}
	//read Jerry attack
	{
		auto animation = Animation::create();
		for (int i = 0; i < 3; i++)
		{
			char szName[100] = { 0 };
			sprintf(szName, "BattleScene/JerryAnim/jerry_%02d.png", i);
			animation->addSpriteFrameWithFile(szName);
		}
		animation->setDelayPerUnit(0.3f);
		animation->setRestoreOriginalFrame(true);
		cache->addAnimation(animation, Tri_Moving_forward_anim);
	}
	//read Ceaser attack
	{
		auto animation = Animation::create();
		for (int i = 0; i < 4; i++)
		{
			char szName[100] = { 0 };
			sprintf(szName, "BattleScene/CeaserAnim/Ceaser_%02d.png", i);
			animation->addSpriteFrameWithFile(szName);
		}
		animation->setDelayPerUnit(0.4f);
		animation->setRestoreOriginalFrame(true);
		cache->addAnimation(animation, Cir_Moving_forward_anim);
	}
	{//read tony dead
		auto animation = Animation::create();
		for (int i = 0; i < 4; i++)
		{
			char szName[100] = { 0 };
			sprintf(szName, "tony_die_%02d.png", i);
			animation->addSpriteFrameWithFile(szName);
		}
		animation->setDelayPerUnit(0.2f);
		animation->setRestoreOriginalFrame(true);
		cache->addAnimation(animation, Rec_Die_anim);
	}//read Jerry dead
	{
		auto animation = Animation::create();
		for (int i = 0; i < 4; i++)
		{
			char szName[100] = { 0 };
			sprintf(szName, "BattleScene/JerryAnim/jerry_die_%02d.png", i);
			animation->addSpriteFrameWithFile(szName);
		}
		animation->setDelayPerUnit(0.2f);
		animation->setRestoreOriginalFrame(true);
		cache->addAnimation(animation, Tri_Die_anim);
	}
	{//read Ceaser dead
		auto animation = Animation::create();
		for (int i = 0; i < 4; i++)
		{
			char szName[100] = { 0 };
			sprintf(szName, "BattleScene/CeaserAnim/Ceaser_die_%02d.png", i);
			animation->addSpriteFrameWithFile(szName);
		}
		animation->setDelayPerUnit(0.2f);
		animation->setRestoreOriginalFrame(true);
		cache->addAnimation(animation, Cir_Die_anim);
	}
	{//tony hit back
		auto animation = Animation::create();
		animation->addSpriteFrameWithFile("tony_cry.png");
		animation->setDelayPerUnit(3.0f);
		animation->setRestoreOriginalFrame(false);
		cache->addAnimation(animation, Rec_Hit_back_anim);
	}
	{//jerry hit back
		auto animation = Animation::create();
		animation->addSpriteFrameWithFile("jerry_cry.png");
		animation->setDelayPerUnit(3.0f);
		animation->setRestoreOriginalFrame(false);
		cache->addAnimation(animation, Tri_Hit_back_anim);
	}
	{//Ceaser hit back
		auto animation = Animation::create();
		animation->addSpriteFrameWithFile("Ceaser_cry.png");
		animation->setDelayPerUnit(3.0f);
		animation->setRestoreOriginalFrame(false);
		cache->addAnimation(animation, Cir_Hit_back_anim);
	}
	{
		auto animation = Animation::create();
		animation->addSpriteFrameWithFile("Trees.png");
		animation->addSpriteFrameWithFile("tree2Color.png");
		animation->setDelayPerUnit(1.0f);
		animation->setRestoreOriginalFrame(true);
		cache->addAnimation(animation, "castle_enemy_damaged.png");
	}
	Enemy_Castle = Sprite::create("tree2Color.png");
	Enemy_Castle->setPositionX(1750);
	Enemy_Castle->setPositionY(370);
	Enemy_Castle->setScaleX(0.6);
	Enemy_Castle->setScaleY(0.6);
	mapContainer->addChild(Enemy_Castle);
	mapContainer->setZOrder(0);
}
void MapLayer::HolyWrath()
{
	for (int i = 0; i < 3; i++){
		for (auto monster : myMonsterVec[i])
		{
			monster->defense += 4;
			auto DefenseUp = Sprite::create("BattleScene/DefenseUp.png");
			if (monster->type == Rect)
			{
				DefenseUp->setAnchorPoint(Point(0, 0));
				DefenseUp->setPosition(Point(240, 360));
			}
			else if (monster->type==Tri)
			{
				DefenseUp->setAnchorPoint(Point(0.5, 0.5));
				DefenseUp->setPosition(Point(130, 290));
			}
			else
			{
				DefenseUp->setAnchorPoint(Point(0.5, 0.5));
				DefenseUp->setPosition(Point(130, 240));
			}
			monster->anim_body->addChild(DefenseUp);
		}
	}
}
void MapLayer::EvilFurious()
{
	for (int i = 0; i < 3; i++){
		for (auto monster : myMonsterVec[i])
		{
			monster->attack += 4;
			auto AttUp = Sprite::create("BattleScene/AttackUp.png");
			if (monster->type == Rect)
			{
				AttUp->setAnchorPoint(Point(0, 0));
				AttUp->setPosition(Point(250, 360));
			}
			else if (monster->type==Tri)
			{
				AttUp->setAnchorPoint(Point(0.5, 0.5));
				AttUp->setPosition(Point(140, 290));
			}
			else
			{
				AttUp->setAnchorPoint(Point(0.5, 0.5));
				AttUp->setPosition(Point(140, 240));
			}
			monster->anim_body->addChild(AttUp);
		}
	}
}
void MapLayer::JudgementMeteorolite()
{
	auto particle = ParticleSystemQuad::create("BattleScene/judgement.plist");
	particle->setPosition(Point(480,320));
	particle->setScaleX(2.0f);
	particle->setScaleY(2.0f);
	this->mapContainer->addChild(particle,5);
	auto particle1 = ParticleSystemQuad::create("BattleScene/judgement.plist");
	particle1->setScaleX(2.0f);
	particle1->setScaleY(2.0f);
	particle1->setPosition(Point(480+960, 320));
	this->mapContainer->addChild(particle1, 5);
	auto cache = AnimationCache::getInstance();
	auto God = new CircleMonster(15,30,10000,0);
	for (int i = 0; i < 3; i++){
		for (auto monster : enemyMonsterVec[i])
		{
			if (monster->getState()!=DEAD)Monster::BattleEach(cache, God, monster,1);
		}
	}
}
void MapLayer::scrollMapLeft()
{
	if (mapContainer == NULL)
	{
		//std::exception ex("map Containner not initialized, please use create() first");
		//throw ex;
	}
	else
	{
		if (mapScrollPercentage == 0.0f)
			return;
		mapScrollPercentage -= 100.0f;
		mapContainer->scrollToPercentHorizontal(mapScrollPercentage, 1.0f, true);
	}
}

void MapLayer::scrollMapRight()
{
	if (mapContainer == NULL)
	{
		//std::exception ex("map Containner not initialized, please use create() first");
		//throw ex;
	}
	else
	{
		if (mapScrollPercentage == 100.0f)
			return;
		mapScrollPercentage += 100.0f;
		mapContainer->scrollToPercentHorizontal(mapScrollPercentage, 1.0f, true);
	}
}

void MapLayer::addMonster(Monster *monster,int row)
{
	monster->Line = row;
	switch (row)
	{
	case UPROW:
		monster->anim_body->setPosition(Point(STARTX,UPROWY));
		myMonsterVec[UPROW].pushBack(monster);
		break;
	case MIDDLEROW:
		monster->anim_body->setPosition(Point(STARTX, MIDDLEROWY));
		myMonsterVec[MIDDLEROW].pushBack(monster);
		break;
	case DOWNROW:
		monster->anim_body->setPosition(Point(STARTX, DOWNROWY));
		myMonsterVec[DOWNROW].pushBack(monster);
		break;
	default:
		break;
	}
	auto cache = AnimationCache::getInstance();
	monster->MovingForward(cache);
	mapContainer->addChild(monster->anim_body);
}


void MapLayer::addEnemy(Monster *monster, int row, int delayDist)
{
	monster->Line = row;
	switch (row)
	{
	case UPROW:
		monster->anim_body->setPosition(Point(STARTX + 960 + 940 + delayDist , UPROWY));
		enemyMonsterVec[UPROW].pushBack(monster);
		break;
	case MIDDLEROW:
		monster->anim_body->setPosition(Point(STARTX + 960 + 940 + delayDist, MIDDLEROWY));
		enemyMonsterVec[MIDDLEROW].pushBack(monster);
		break;
	case DOWNROW:
		monster->anim_body->setPosition(Point(STARTX + 960 + 940 + delayDist, DOWNROWY));
		enemyMonsterVec[DOWNROW].pushBack(monster);
		break;
	default:
		break;
	}
	auto cache = AnimationCache::getInstance();
	monster->MovingForward(cache);
	mapContainer->addChild(monster->anim_body);
}
int MapLayer::Castle_damage()
{
	int flag = 0;
	auto cache = AnimationCache::getInstance();
	for (int i = 0; i < 3; i++)
	{
		for (auto monster : myMonsterVec[i])
		{
			if (monster->getState() == Move_foward)
			{//test if attack the castle
				if (monster->anim_body->getPositionX() >= Map_width)
				{
					flag = 1;
					Enemy_Castle_life_point -= monster->attack;
					log("enemycastle damaged");
					auto animate = Animate::create(cache->getAnimation("castle_enemy_damaged.png"));
					Enemy_Castle->runAction(RepeatForever::create(Sequence::create(animate, animate->reverse(), NULL)));

					if (Enemy_Castle_life_point <= 0) { 
						log("win!"); 
						return Win; }
				}
			}
		}
		for (auto enemy : enemyMonsterVec[i])
		{
			if (enemy->getState() == Move_foward)
			{
				if (enemy->anim_body->getPositionX() <= 80)
				{
					Player_Castle_life_point -= enemy->attack;
					if (Player_Castle_life_point <= 0) { 
						log("lose"); 
						return Lose; }
				}
			}
		}
	}
	if (!flag) Enemy_Castle->stopAllActions();
	return Nothing;
}
void MapLayer::checkCollision()
{
	auto cache = AnimationCache::getInstance();
	
	for (int i = 0; i < 3; i++)
	{
		for (auto monster : myMonsterVec[i])
		{
			
			auto x = monster->anim_body->getPosition().x;
			for (auto enemy : enemyMonsterVec[i])
			{
				if (enemy->getState() == Move_foward||monster->getState() == Move_foward){
					if (abs(x - enemy->anim_body->getPosition().x) <= 80)
					{
						Monster::BattleEach(cache, monster, enemy);
					}
					
				}
				if (enemy->getState() == DEAD)
				{//the monster is dead,release it from the layer
					enemy->anim_body->removeAllChildren();
					//enemy->anim_body->setVisible(false);
					mapContainer->removeChild(enemy->anim_body,true);
					enemyMonsterVec[i].eraseObject(enemy,true);
				}
				if (monster->getState() == DEAD)
				{
					//monster->anim_body->removeAllChildren();
					//monster->anim_body->setVisible(false);
					mapContainer->removeChild(monster->anim_body, true);
					myMonsterVec[i].eraseObject(monster, true);
				}
			}
			
		}
	}
}
