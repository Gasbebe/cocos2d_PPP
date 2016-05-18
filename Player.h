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

	//플레이어 인포
	double playerHp, playerMaxhp, playerDef;
	double hpPer;
	int    atk_stack;
	int    shield_stack;
	cocos2d::LabelAtlas* atkLabel;
	cocos2d::LabelAtlas* shieldLabel;

	//이펙트
	Effect* effect;
	int effectType;

	//애니메이션
	cocos2d::Action* animAtk;
	cocos2d::Action* animSheild;
	cocos2d::Action* animIdle;
	cocos2d::Action* animRun;
	cocos2d::Action* animDie;
	cocos2d::Action* stopAim;
	cocos2d::Action* delayHit;
	
	//player state ui
	//cocos2d::Sprite* bodyColl;
	cocos2d::Sprite* hpBar;
	cocos2d::Sprite* hpGauge;
	cocos2d::Sprite* uiWindow;
	cocos2d::Sprite* pace;
	virtual bool init();

	//어떤레이어 에다가 플레이어 상태창 올릴지
	void setUI(cocos2d::Vec2 pos, cocos2d::Layer* uiLayer);

	//애니메이셔 실행함수
	void atkAction();
	void sheildAction();
	void idleAction();
	void runAction2();
	void dieAction();
	void EndAnimation();
	void StartAnimation();

	//액션실행
	void setAction(bool type);

	//타입에 맞는 이펙트 및 사운드
	void setEffect(int number);

	//로그 찍는거
	void showState();
	void UpdateState();
	void Hit(double damage);
	void Heal();

	//스택 추가함수
	void AddAtkStack();
	void AddShieldStack();

	//라벨 숫자 바꾸는 함수
	void setAtkLabel();
	void setShieldLabel();

};

#endif // __HELLOWORLD_SCENE_H__

