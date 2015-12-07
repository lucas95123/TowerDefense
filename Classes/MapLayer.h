#ifndef __MAP_LAYER_H__
#define __MAP_LAYER_H_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Monster.h"
#include <iostream>
#include <cmath>

USING_NS_CC;

class MapLayer
{
public:
	void create(ui::ScrollView * map);
	void scrollMapRight();
	void scrollMapLeft();
	void addMonster(Sprite *monster, int row);
	void addEnemy(Sprite *monster, int row);//just for test
	void checkCollision();

private: 
	ui::ScrollView *mapContainer;//The Map
	float mapScrollPercentage = 0;//Scroll map indicator
	Vector<Sprite *> myMonsterVec[3];//Vec that stores my monster
	Vector<Sprite *> enemyMonsterVec[3];//Vec that stores the enemy 
};

#endif //__MAP_LAYER_H__