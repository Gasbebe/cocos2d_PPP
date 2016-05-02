#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "cocos2d.h"

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

	void Test();
	void ViewCommand(int number);
	void setOnActive();
	void hideCommand();
	bool getActionType(int num);
	bool playingAction();
};

#endif
