#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class MainScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	~MainScene();
	virtual bool init();

	int stageNum;
	bool flag;

	CREATE_FUNC(MainScene);
	cocos2d::Size winSize;

	void selcetStage(int num);
	void moveScene(cocos2d::Ref* pSender);
};
#endif