#ifndef __INTRO_SCENE_H__
#define __INTRO_SCENE_H__


#include "cocos2d.h"
#include "extensions/cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;


class ScoreScene : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(ScoreScene);
	cocos2d::Size winSize;

	cocos2d::ui::EditBox* _editNum;
	std::string txtNum;

	void doSendScore(Ref* pSender);
	void doSendTime(Ref* pSender);

	void doSendOne(Ref* pSender);
	void doSendMulti(Ref* pSender);

	void doShowLeaderBoard(Ref* pSender);
	void doShowAchivement(Ref* pSender);

	void setScore(std::string score);
};
#endif