#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "Command.h"
#include "cocos2d.h"

using namespace cocos2d;


class Button : public cocos2d::Sprite {
public:
	Button();
	
	Command* atkCommnad;
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void setCommand(Command* command);

};

#endif
