#ifndef __INTRO_SCENE_H__
#define __INTRO_SCENE_H__


#include "cocos2d.h"
using namespace cocos2d;

class IntroScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(IntroScene);
	cocos2d::Size winSize;
	void startGame(cocos2d::Ref* pSender);
	//~IntroScene();
};
#endif