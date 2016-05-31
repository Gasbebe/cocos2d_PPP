#ifndef __INTRO_SCENE_H__
#define __INTRO_SCENE_H__


#include "cocos2d.h"
#include "extensions/cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;


class ScoreScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	bool flag;
	CREATE_FUNC(ScoreScene);
	cocos2d::Size winSize;

	cocos2d::LabelAtlas* scoreLabel;
	int score;
	std::string txtNum;

	void doShowLeaderBoard(Ref* pSender);
	void moveScene(Ref* pSender);
	void quitGame(Ref* pSender);
	void setLabelScore(int num);

};
#endif