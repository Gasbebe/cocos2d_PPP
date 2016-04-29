#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "cocos2d.h"

using namespace cocos2d;

class Monster : public cocos2d::Sprite {
public:
	Monster(double maxhp);

	enum monsterState { Idle, Atk, Sheild, Die, Run };
	monsterState ms;
	double monsterHp, monsterMaxhp;

	//애니메이션
	cocos2d::Action* animAtk;
	cocos2d::Action* animSheild;
	cocos2d::Action* animIdle;
	cocos2d::Action* animRun;
	cocos2d::Action* animDie;
	cocos2d::Action* stopAim;

	//player state ui
	cocos2d::Sprite* hpBar;
	cocos2d::Sprite* uiWindow;
	cocos2d::Sprite* pace;

	void setUI(cocos2d::Vec2 pos, cocos2d::Layer* uiLayer);
	void atkAction();
	void sheildAction();
	void idleAction();
	void runAction2();
	void dieAction();
	void EndAnimation();
	void StartAnimation();

	void setAction(bool type);
	void showState();
	void Hit();

};
#endif // __HELLOWORLD_SCENE_H__

