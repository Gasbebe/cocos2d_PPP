#include "Effect.h"

Effect::Effect() {
	bool bOk = initWithTexture(nullptr, Rect::ZERO);
	if (bOk) {
		this->autorelease();
	}
}

//number 1~ 10 : fire type   number 2 : explo  type number3 : smoke type
void Effect::getTypeEffect(int number, Vec2 pos, Layer *layer) {
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
}