#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "cocos2d.h"
#include "Player.h"

using namespace cocos2d;


class Command : public cocos2d::Sprite {
public:
	Command();
	int count;
	bool bOnActive;

	//true¸é  atk  false¸é  sheild
	bool bAction[3];

	cocos2d::Size commandSize;
	cocos2d::Sprite *atk;
	cocos2d::Sprite *sheild;

	cocos2d::Sprite *sprite1;
	cocos2d::Sprite *sprite2;
	cocos2d::Sprite *sprite3;

	Player* p1;
	Player* p2;
	Player* p3;

	void Test();
	void ViewCommand(int number);
	void setOnActive();
	void hideCommand();
	bool getActionType(int num);
	bool playingAction();
	void setBtnUI(cocos2d::Vec2 pos, cocos2d::Layer* layer);
	void pressAtkBtn(Ref* pSender);
	void pressShieldBtn(Ref* pSender);
	void setPlayerAction(Player *_p1, Player *_p2, Player *_p3);
	void playerAction();
};

#endif
