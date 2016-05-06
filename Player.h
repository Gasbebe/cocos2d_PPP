#ifndef __GAME_PLAYER_H__
#define __GAME_PLAYER_H__

#include "cocos2d.h"
#include "Effect.h"

using namespace cocos2d;

class Player : public cocos2d::Sprite{
public:

	enum playerState{Idle, Atk, Sheild, Die, Run};
	playerState ps;

	Player(double hp, double maxhp, double def, int type);
	~Player();
	double playerHp, playerMaxhp, playerDef;

	//����Ʈ
	Effect* effect;
	int effectType;

	//�ִϸ��̼�
	cocos2d::Action* animAtk;
	cocos2d::Action* animSheild;
	cocos2d::Action* animIdle;
	cocos2d::Action* animRun;
	cocos2d::Action* animDie;
	cocos2d::Action* stopAim;
	
	//player state ui
	//cocos2d::Sprite* bodyColl;
	cocos2d::Sprite* hpBar;
	cocos2d::Sprite* uiWindow;
	cocos2d::Sprite* pace;
	virtual bool init();

	//�ִϸ��̼� �����Լ�
	void setUI(cocos2d::Vec2 pos, cocos2d::Layer* uiLayer);
	void atkAction();
	void sheildAction();
	void idleAction();
	void runAction2();
	void dieAction();
	void EndAnimation();
	void StartAnimation();

	void setAction(bool type);
	void setEffect(int number);
	void showState();
	void UpdateState();
	void Hit();

};

#endif // __HELLOWORLD_SCENE_H__

