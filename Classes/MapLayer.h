#ifndef __MAP_LAYER_H__
#define __MAP_LAYER_H_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Monster.h"
#include <iostream>

USING_NS_CC;

class MapLayer
{
public:
	void create(ui::ScrollView * map);
	void scrollMapRight();
	void scrollMapLeft();
	void addMonster(Sprite *monster, int row);
	void checkCollision();

private: 
	ui::ScrollView *mapContainer;
	float mapScrollPercentage = 0;
	Vector<Sprite *> myMonsterVec[3];
	Vector<Sprite *> enemyMonsterVec[3];
};

#endif //__MAP_LAYER_H__