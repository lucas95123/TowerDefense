#ifndef __MAP_LAYER_H__
#define __MAP_LAYER_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Monster.h"
#include <cmath>

USING_NS_CC;
#define Win 1
#define Lose 2
#define Nothing 0
#define enemy_castle_life 500
#define player_castle_life 500
class MapLayer
{
public:
	void create(ui::ScrollView * map,int _Player_castle_life,int _Enemy_life_point);
	void scrollMapRight();
	void scrollMapLeft();
	void addMonster(Monster *monster, int row);
	void addEnemy(Monster *monster, int row);//just for test
	void checkCollision();
	int Castle_damage();
	int Enemy_Castle_life_point;
	int Player_Castle_life_point;
private: 
	Sprite* Enemy_Castle, Player_Castle;
	ui::ScrollView *mapContainer;//The Map
	float mapScrollPercentage = 0;//Scroll map indicator
	Vector<Monster *> myMonsterVec[3];//Vec that stores my monster
	Vector<Monster *> enemyMonsterVec[3];//Vec that stores the enemy 
};

#endif //__MAP_LAYER_H__