#include "MapLayer.h"
#include <iostream>

void MapLayer::create(ui::ScrollView * map,int _Enemy_life_point,int _Player_life_point)
{
	mapContainer = map;
	mapContainer->setTouchEnabled(false);
	this->Enemy_Castle_life_point = _Enemy_life_point;
	this->Player_Castle_life_point = _Player_life_point;
	//Initialize animations 
	auto cache = AnimationCache::getInstance();
	auto animation = Animation::create();
	for (int i = 1; i<9; i++)
	{
		char szName[100] = { 0 };
		sprintf(szName, "tony_%02d.png", i);
		animation->addSpriteFrameWithFile(szName);
	}
	animation->setDelayPerUnit(0.9f /18.0f);
	animation->setRestoreOriginalFrame(true);
	cache->addAnimation(animation, Rec_Moving_forward_anim);
	{
		auto animation = Animation::create();
		animation->addSpriteFrameWithFile("tony_cry.png");
		animation->setDelayPerUnit(3.0f);
		animation->setRestoreOriginalFrame(false);
		cache->addAnimation(animation, Rec_Hit_back_anim);
	}
	{
		auto animation = Animation::create();
		animation->addSpriteFrameWithFile("castle_enemy.png");
		animation->addSpriteFrameWithFile("castle_enemy_damaged.png");
		animation->setDelayPerUnit(1.0f);
		animation->setRestoreOriginalFrame(true);
		cache->addAnimation(animation, "castle_enemy_damaged.png");
	}
	Enemy_Castle = Sprite::create("castle_enemy.png");
	Enemy_Castle->setPositionX(1800);
	Enemy_Castle->setPositionY(0);
	Enemy_Castle->setScaleY(3);
	mapContainer->addChild(Enemy_Castle);
}

void MapLayer::scrollMapLeft()
{
	if (mapContainer == NULL)
	{
		std::exception ex("map Containner not initialized, please use create() first");
		throw ex;
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
		std::exception ex("map Containner not initialized, please use create() first");
		throw ex;
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


void MapLayer::addEnemy(Monster *monster, int row)
{
	monster->Line = row;
	switch (row)
	{
	case UPROW:
		monster->anim_body->setPosition(Point(STARTX + 960 + 940, UPROWY));
		enemyMonsterVec[UPROW].pushBack(monster);
		break;
	case MIDDLEROW:
		monster->anim_body->setPosition(Point(STARTX + 960 + 940, MIDDLEROWY));
		enemyMonsterVec[MIDDLEROW].pushBack(monster);
		break;
	case DOWNROW:
		monster->anim_body->setPosition(Point(STARTX + 960 + 940, DOWNROWY));
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
	auto cache = AnimationCache::getInstance();
	for (int i = 0; i < 3; i++)
	{
		for (auto monster : myMonsterVec[i])
		{
			if (monster->getState() == Move_foward)
			{//test if attack the castle
				if (monster->anim_body->getPositionX() >= Map_width)
				{
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
	return Nothing;
}
void MapLayer::checkCollision()
{
	auto cache = AnimationCache::getInstance();
	auto animate1 = Animate::create(cache->getAnimation("Cry"));
	auto animate2 = Animate::create(cache->getAnimation("Cry"));
	
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
					mapContainer->removeChild(enemy->anim_body);
					enemyMonsterVec[i].eraseObject(enemy,false);
				}
				if (monster->getState() == DEAD)
				{
					mapContainer->removeChild(monster->anim_body);
					myMonsterVec[i].eraseObject(monster, false);
				}
			}
			
		}
	}
}
