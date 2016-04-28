#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "cocos2d.h"

using namespace cocos2d;

class Monster : public cocos2d::Sprite {
public:
	Monster(double hp, double maxhp, double def);
	double playerHp, playerMaxhp, playerDef;
	void atkAction();
	void sheildAction();

};

#endif // __HELLOWORLD_SCENE_H__

