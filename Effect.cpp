#include "Effect.h"

Effect::Effect() {
	b_effect[0] = false;
	bool bOk = initWithTexture(nullptr, Rect::ZERO);
	if (bOk) {
		this->autorelease();
	}
	effec_cache = SpriteFrameCache::getInstance();
	//검사 공격
	effec_cache->addSpriteFramesWithFile("Skill/fx_bladestorm.plist");
	//방어
	effec_cache->addSpriteFramesWithFile("Skill/fx_defense.plist");
	//화살 터질때
	effec_cache->addSpriteFramesWithFile("Skill/fx_blood_explosion.plist");
	//힐러
	effec_cache->addSpriteFramesWithFile("Skill/fx_teleportrecall2.plist");
	//
	effec_cache->addSpriteFramesWithFile("Skill/fx_whiteexplosion.plist");
}

//number 1~ 5 : fire type   number 6, 7, 8  : shield  type number3 : smoke type
//background용 이펙트
void Effect::getTypeEffect(int number, Vec2 pos, Layer *layer) {
	char str[100] = { 0 };
	if (number == 1) {
		auto sprite = Sprite::create("Skill/fire1.png");
		auto texture = sprite->getTexture();
		auto animation = Animation::create();
		animation->setDelayPerUnit(0.1f);

		for (int i = 0; i < 4; i++) {
			int colum = i % 4; // 0,1,2,3,4
			int row = i / 4; //0,1,2
							 // x,y 좌표 x로 얼마만큼  y로 얼마만큼
			animation->addSpriteFrameWithTexture(texture, Rect(colum * 11, row * 11, 11, 11));
		}

		auto effect = Sprite::create("Skill/fire1.png", Rect(0, 0, 11, 11));
		effect->setPosition(pos);
		layer->addChild(effect);

		auto animate = Animate::create(animation);
		auto rep = RepeatForever::create(animate);
		effect->runAction(rep);
	}
	else if (number == 2) {

		auto sprite = Sprite::create("Skill/fire1.png");
		auto texture = sprite->getTexture();
		auto animation = Animation::create();
		animation->setDelayPerUnit(0.1f);

		for (int i = 4; i < 8; i++) {
			int colum = i % 4; // 0,1,2,3,4
			int row = i / 4; //0,1,2
							 // x,y 좌표 x로 얼마만큼  y로 얼마만큼
			animation->addSpriteFrameWithTexture(texture, Rect(colum * 11, row * 11, 11, 11));
		}

		auto effect = Sprite::create("Skill/fire1.png", Rect(11, 11, 11, 11));
		effect->setPosition(pos);
		layer->addChild(effect);

		auto animate = Animate::create(animation);
		auto rep = RepeatForever::create(animate);
		effect->runAction(rep);
	}
	else if (number == 3) {

		auto sprite = Sprite::create("Skill/fire2.png");
		auto texture = sprite->getTexture();
		auto animation = Animation::create();
		animation->setDelayPerUnit(0.1f);

		for (int i = 0; i < 8; i++) {
			int colum = i % 8; // 0,1,2,3,4
			int row = i / 8; //0,1,2
							 // x,y 좌표 x로 얼마만큼  y로 얼마만큼
			animation->addSpriteFrameWithTexture(texture, Rect(colum * 22, row * 22, 22, 22));
		}

		auto effect = Sprite::create("Skill/fire2.png", Rect(0, 0, 22, 22));
		effect->setPosition(pos);
		layer->addChild(effect);

		auto animate = Animate::create(animation);
		auto rep = RepeatForever::create(animate);
		effect->runAction(rep);

	}
	else if (number == 4) {

		auto sprite = Sprite::create("Skill/fire2.png");
		auto texture = sprite->getTexture();
		auto animation = Animation::create();
		animation->setDelayPerUnit(0.1f);

		for (int i = 8; i < 16; i++) {
			int colum = i % 8; // 0,1,2,3,4
			int row = i / 8; //0,1,2
							 // x,y 좌표 x로 얼마만큼  y로 얼마만큼
			animation->addSpriteFrameWithTexture(texture, Rect(colum * 22, row * 22, 22, 22));
		}

		auto effect = Sprite::create("Skill/fire2.png", Rect(22, 22, 22, 22));
		effect->setPosition(pos);
		layer->addChild(effect);

		auto animate = Animate::create(animation);
		auto rep = RepeatForever::create(animate);
		effect->runAction(rep);
	}
	else if (number == 5) {

		auto sprite = Sprite::create("Skill/fire2.png");
		auto texture = sprite->getTexture();
		auto animation = Animation::create();
		animation->setDelayPerUnit(0.1f);

		for (int i = 16; i < 24; i++) {
			int colum = i % 8; // 0,1,2,3,4
			int row = i / 8; //0,1,2
							 // x,y 좌표 x로 얼마만큼  y로 얼마만큼
			animation->addSpriteFrameWithTexture(texture, Rect(colum * 22, row * 22, 22, 22));
		}

		auto effect = Sprite::create("Skill/fire2.png", Rect(44, 44, 22, 22));
		effect->setPosition(pos);
		layer->addChild(effect);

		auto animate = Animate::create(animation);
		auto rep = RepeatForever::create(animate);
		effect->runAction(rep);
	}
	else if (number == 6) {

		Vector<SpriteFrame*> effect_frame;

		for (int i = 0; i < 12; i++) {
			sprintf(str, "fx_bladestorm_%003d.png", i);
			SpriteFrame* frame = effec_cache->getSpriteFrameByName(str);
			effect_frame.pushBack(frame);
		}

		auto effect_animation = Animation::createWithSpriteFrames(effect_frame, 0.1f);
		auto effect_animate = Animate::create(effect_animation);
		//auto act = RepeatForever::create(effect_animate);

		auto effect = Sprite::createWithSpriteFrameName("fx_bladestorm_000.png");
		effect->setPosition(pos);
		layer->addChild(effect);
		//effect->runAction(act);

		auto removeAction = CCCallFunc::create(CC_CALLBACK_0(CCNode::removeChild, layer, effect, false));
		auto seq = Sequence::create(effect_animate, removeAction, nullptr);
		effect->runAction(seq);
	}
	else if (number == 7) {
		Vector<SpriteFrame*> effect_frame;

		for (int i = 0; i < 5; i++) {
			sprintf(str, "fx_floatingshield_%003d.png", i);
			SpriteFrame* frame = effec_cache->getSpriteFrameByName(str);
			effect_frame.pushBack(frame);
		}

		auto effect_animation = Animation::createWithSpriteFrames(effect_frame, 0.1f);
		auto effect_animate = Animate::create(effect_animation);
		auto act = RepeatForever::create(effect_animate);

		auto effect = Sprite::createWithSpriteFrameName("fx_floatingshield_000.png");
		effect->setPosition(pos);
		layer->addChild(effect);
		effect->runAction(act);
	}
	else if (number == 8) {

		Vector<SpriteFrame*> effect_frame;

		for (int i = 0; i < 9; i++) {
			sprintf(str, "fx_forcefield_%003d.png", i);
			SpriteFrame* frame = effec_cache->getSpriteFrameByName(str);
			effect_frame.pushBack(frame);
		}

		auto effect_animation = Animation::createWithSpriteFrames(effect_frame, 0.1f);
		auto effect_animate = Animate::create(effect_animation);
		auto act = RepeatForever::create(effect_animate);

		auto effect = Sprite::createWithSpriteFrameName("fx_forcefield_000.png");
		effect->setPosition(pos);
		layer->addChild(effect);
		//effect->runAction(act);

		auto removeAction = CCCallFunc::create(CC_CALLBACK_0(CCNode::removeChild, layer, effect, false));
		auto seq = Sequence::create(effect_animate, removeAction, nullptr);
		effect->runAction(seq);

	}
	else if (number == 9) {

		auto sprite = Sprite::create("Skill/fx_explosionorangesmoke.png");
		auto texture = sprite->getTexture();
		auto animation = Animation::create();
		animation->setDelayPerUnit(0.1f);

		for (int i = 0; i < 6; i++) {
			int colum = i % 2; // 0, 1, 0 , 1, 0, 1
			int row = i / 2; //0,1,2,3,
							 // x,y 좌표 x로 얼마만큼  y로 얼마만큼
			animation->addSpriteFrameWithTexture(texture, Rect(colum * 58, row * 44, 58, 44));
		}

		auto effect = Sprite::create("Skill/fx_explosionorangesmoke.png", Rect(0, 0, 58, 44));
		effect->setPosition(pos);
		effect->setAnchorPoint(Vec2(0, 0.5));
		layer->addChild(effect);


		auto animate = Animate::create(animation);
		auto removeAction = CCCallFunc::create(CC_CALLBACK_0(CCNode::removeChild, layer, effect, false));
		auto seq = Sequence::create(animate, removeAction, nullptr);
		effect->runAction(seq);

	}
	else if (number == 10) {
		Vector<SpriteFrame*> effect_frame;

		for (int i = 0; i < 15; i++) {
			sprintf(str, "fx_bloodbig_%003d.png", i);
			SpriteFrame* frame = effec_cache->getSpriteFrameByName(str);
			effect_frame.pushBack(frame);
		}

		auto effect_animation = Animation::createWithSpriteFrames(effect_frame, 0.05f);
		auto effect_animate = Animate::create(effect_animation);
		auto act = RepeatForever::create(effect_animate);

		auto effect = Sprite::createWithSpriteFrameName("fx_bloodbig_000.png");
		effect->setPosition(pos);
		layer->addChild(effect);
		//effect->runAction(act);

		auto removeAction = CCCallFunc::create(CC_CALLBACK_0(CCNode::removeChild, layer, effect, false));
		auto seq = Sequence::create(effect_animate, removeAction, nullptr);
		effect->runAction(seq);
	}
	else if (number == 11) {
		Vector<SpriteFrame*> effect_frame;

		for (int i = 0; i < 10; i++) {
			sprintf(str, "fx_bloodmedium_%003d.png", i);
			SpriteFrame* frame = effec_cache->getSpriteFrameByName(str);
			effect_frame.pushBack(frame);
		}

		auto effect_animation = Animation::createWithSpriteFrames(effect_frame, 0.05f);
		auto effect_animate = Animate::create(effect_animation);
		auto act = RepeatForever::create(effect_animate);

		auto effect = Sprite::createWithSpriteFrameName("fx_bloodmedium_000.png");
		effect->setPosition(pos);
		layer->addChild(effect);
		//effect->runAction(act);

		auto removeAction = CCCallFunc::create(CC_CALLBACK_0(CCNode::removeChild, layer, effect, false));
		auto seq = Sequence::create(effect_animate, removeAction, nullptr);
		effect->runAction(seq);
	}
}

//플에이어용 이펙트
void Effect::getTypePlayerEffect(int number, cocos2d::Vec2 pos, cocos2d::Sprite* player) {
		char str[100] = { 0 };
		if (number == 1) {
			Vector<SpriteFrame*> effect_frame;

			for (int i = 0; i < 5; i++) {
				sprintf(str, "fx_floatingshield_%003d.png", i);
				SpriteFrame* frame = effec_cache->getSpriteFrameByName(str);
				effect_frame.pushBack(frame);
			}

			auto effect_animation = Animation::createWithSpriteFrames(effect_frame, 0.1f);
			auto effect_animate = Animate::create(effect_animation);

			auto effect = Sprite::createWithSpriteFrameName("fx_floatingshield_000.png");
			effect->setPosition(pos);
			player->addChild(effect);

			auto removeAction = CCCallFunc::create(CC_CALLBACK_0(CCNode::removeChild, player, effect, false));
			auto seq = Sequence::create(effect_animate, removeAction, nullptr);
			effect->setScale(1.5f);
			effect->runAction(seq);
		}
		else if (number == 2) {

			Vector<SpriteFrame*> effect_frame;

			for (int i = 0; i < 9; i++) {
				sprintf(str, "fx_forcefield_%003d.png", i);
				SpriteFrame* frame = effec_cache->getSpriteFrameByName(str);
				effect_frame.pushBack(frame);
			}

			auto effect_animation = Animation::createWithSpriteFrames(effect_frame, 0.1f);
			auto effect_animate = Animate::create(effect_animation);

			auto effect = Sprite::createWithSpriteFrameName("fx_forcefield_000.png");
			effect->setPosition(pos);
			player->addChild(effect);

			auto removeAction = CCCallFunc::create(CC_CALLBACK_0(CCNode::removeChild, player, effect, false));
			auto seq = Sequence::create(effect_animate, removeAction, nullptr);
	
			effect->runAction(seq);

		}
		else if (number == 3) {
			Vector<SpriteFrame*> effect_frame;

			for (int i = 0; i < 14; i++) {
				sprintf(str, "fx_teleportrecall2_%003d.png", i);
				SpriteFrame* frame = effec_cache->getSpriteFrameByName(str);
				effect_frame.pushBack(frame);
			}

			auto effect_animation = Animation::createWithSpriteFrames(effect_frame, 0.1f);
			auto effect_animate = Animate::create(effect_animation);

			auto effect = Sprite::createWithSpriteFrameName("fx_forcefield_000.png");
			effect->setPosition(pos);
			player->addChild(effect);

			auto removeAction = CCCallFunc::create(CC_CALLBACK_0(CCNode::removeChild, player, effect, false));
			auto seq = Sequence::create(effect_animate, removeAction, nullptr);

			effect->runAction(seq);
		}
		else if (number == 10) {
			Vector<SpriteFrame*> effect_frame;

			for (int i = 0; i < 15; i++) {
				sprintf(str, "fx_bloodbig_%003d.png", i);
				SpriteFrame* frame = effec_cache->getSpriteFrameByName(str);
				effect_frame.pushBack(frame);
			}

			auto effect_animation = Animation::createWithSpriteFrames(effect_frame, 0.05f);
			auto effect_animate = Animate::create(effect_animation);
			auto act = RepeatForever::create(effect_animate);

			auto effect = Sprite::createWithSpriteFrameName("fx_bloodbig_000.png");
			effect->setPosition(pos);
			player->addChild(effect);
			//effect->runAction(act);

			auto removeAction = CCCallFunc::create(CC_CALLBACK_0(CCNode::removeChild, player, effect, false));
			auto seq = Sequence::create(effect_animate, removeAction, nullptr);
			effect->runAction(seq);
		}
		else if (number == 11) {
			Vector<SpriteFrame*> effect_frame;

			for (int i = 0; i < 10; i++) {
				sprintf(str, "fx_bloodmedium_%003d.png", i);
				SpriteFrame* frame = effec_cache->getSpriteFrameByName(str);
				effect_frame.pushBack(frame);
			}

			auto effect_animation = Animation::createWithSpriteFrames(effect_frame, 0.05f);
			auto effect_animate = Animate::create(effect_animation);
			auto act = RepeatForever::create(effect_animate);

			auto effect = Sprite::createWithSpriteFrameName("fx_bloodmedium_000.png");
			effect->setPosition(pos);
			player->addChild(effect);
			//effect->runAction(act);

			auto removeAction = CCCallFunc::create(CC_CALLBACK_0(CCNode::removeChild, player, effect, false));
			auto seq = Sequence::create(effect_animate, removeAction, nullptr);
			effect->runAction(seq);
		}
}