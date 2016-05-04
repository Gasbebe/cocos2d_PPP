#ifndef __EFFECT_H__
#define __EFFECT_H__

#include "cocos2d.h"

using namespace cocos2d;


class Effect : public cocos2d::Sprite {
public:
	Effect();
	//~Effect();

	cocos2d::Action* act;
	cocos2d::SpriteFrameCache *cache;
	cocos2d::Sprite* sprite;
	void getTypeEffect(int numbers, cocos2d::Vec2 pos, cocos2d::Layer *layer);
};

#endif
