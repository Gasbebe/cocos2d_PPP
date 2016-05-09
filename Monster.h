#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Effect.h"

using namespace cocos2d;

class Monster : public cocos2d::Sprite {
public:
	Monster(double maxhp);
	~Monster();
	enum monsterState { Idle, Atk, Sheild, Die, Run, Cast, CastLoop };
	monsterState ms;
	double monsterHp, monsterMaxhp;

	//애니메이션
	cocos2d::Action* animAtk;
	cocos2d::Action* animSheild;
	cocos2d::Action* animIdle;
	cocos2d::Action* animRun;
	cocos2d::Action* animDie;
	cocos2d::Action* animCastLoop;
	cocos2d::Action* animCasting;
	cocos2d::Action* stopAim;
	cocos2d::Action* delayHit;

	//monster state
	cocos2d::Sprite* bodyColl;
	cocos2d::Sprite* hpBar;
	cocos2d::Sprite* hpGauge;
	cocos2d::Sprite* uiWindow;
	cocos2d::Sprite* pace;

	//effect
	Effect* effect;

	void setUI(cocos2d::Vec2 pos, cocos2d::Layer* uiLayer);
	void atkAction();
	void sheildAction();
	void idleAction();
	void runAction2();
	void dieAction();
	void EndAnimation();
	void StartAnimation();
	void castingAction();
	void castLoopAction();
	
	//monster AI
	void monsterAI(float dt);
	//void setAction(bool type);
	void showState();
	void Hit(double _damage);

	//Skill

};
#endif // __HELLOWORLD_SCENE_H__

