#ifndef __EFFECT_H__
#define __EFFECT_H__

#include "cocos2d.h"

using namespace cocos2d;


class Effect : public cocos2d::Sprite {
public:
	Effect();
	
	bool b_effect[30];
	cocos2d::Action* act;
	cocos2d::SpriteFrameCache *effec_cache;
	cocos2d::Sprite* sprite;
	cocos2d::Sprite* effect[30];
	//cocos2d::Vector<SpriteFrame*> effect_frame[10];
	cocos2d::SpriteFrame* frame;
	void getTypeEffect(int numbers, cocos2d::Vec2 pos, cocos2d::Layer *layer);
};

#endif
