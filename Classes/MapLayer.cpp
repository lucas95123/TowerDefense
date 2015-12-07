#include "MapLayer.h"
#include <iostream>

void MapLayer::create(ui::ScrollView * map)
{
	mapContainer = map;
	mapContainer->setTouchEnabled(false);

	//Initialize animations 
	auto cache = AnimationCache::getInstance();
	auto animation = Animation::create();
	for (int i = 1; i<4; i++)
	{
		char szName[100] = { 0 };
		sprintf(szName, "tony_%02d.png", i);
		animation->addSpriteFrameWithFile(szName);
	}
	animation->setDelayPerUnit(0.3f / 3.0f);
	animation->setRestoreOriginalFrame(true);
	cache->addAnimation(animation, "attack");
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

void MapLayer::addMonster(Sprite *monster,int row)
{
	switch (row)
	{
	case UP:
		monster->setPosition(Point(STARTX,UPROWY));
		myMonsterVec[UP].pushBack(monster);
		break;
	case MIDDLE:
		monster->setPosition(Point(STARTX,MIDDLEROWY));
		myMonsterVec[MIDDLE].pushBack(monster);
		break;
	case DOWN:
		monster->setPosition(Point(STARTX, DOWNROWY));
		myMonsterVec[DOWN].pushBack(monster);
		break;
	default:
		break;
	}
	auto cache = AnimationCache::getInstance();
	//auto animate = Animate::create(cache->getAnimation("attack"));
	//monster->runAction(RepeatForever::create(Sequence::create(animate, animate->reverse(), NULL)));
	auto moveTo = JumpBy::create(5, Point(900, 0), 20, 8);
	auto action = Sequence::create(moveTo, NULL);
	monster->runAction(action);
	mapContainer->addChild(monster);
}

void MapLayer::addEnemy(Sprite *monster, int row)
{
	switch (row)
	{
	case UP:
		monster->setPosition(Point(STARTX+960+940, UPROWY));
		enemyMonsterVec[UP].pushBack(monster);
		break;
	case MIDDLE:
		monster->setPosition(Point(STARTX + 960 + 940, MIDDLEROWY));
		enemyMonsterVec[MIDDLE].pushBack(monster);
		break;
	case DOWN:
		monster->setPosition(Point(STARTX + 960 + 940, DOWNROWY));
		enemyMonsterVec[DOWN].pushBack(monster);
		break;
	default:
		break;
	}
	auto cache = AnimationCache::getInstance();
	auto animate = Animate::create(cache->getAnimation("attack"));
	monster->runAction(RepeatForever::create(Sequence::create(animate, animate->reverse(), NULL)));
	auto moveTo = JumpBy::create(5, Point(-2000, 0), 20, 8);
	auto flipX = FlipX::create(true);
	auto action = Sequence::create(flipX,moveTo, NULL);
	monster->runAction(action);
	mapContainer->addChild(monster);
}

void MapLayer::checkCollision()
{
	for (int i = 0; i < 3; i++)
	{
		for (auto monster : myMonsterVec[i])
		{
			auto x=monster->getPosition().x;
			for (auto enemy : enemyMonsterVec[i])
			{
				if (abs(x - enemy->getPosition().x) <= 80)
				{
					monster->stopAllActions();
					enemy->stopAllActions();
				}
			}
		}
	}
}