#include "Monster.h"

Monster::Monster(double maxhp) {
	effect = new Effect;
	effect->retain();

	monsterHp = maxhp;
	monsterMaxhp = maxhp;
	bool bOk = initWithTexture(nullptr, Rect::ZERO);
	if (bOk) {
		this->autorelease();
	}
	this->schedule(schedule_selector(Monster::monsterAI), 4.5f);
	stopAim = CallFunc::create(CC_CALLBACK_0(Monster::EndAnimation, this));

}

Monster::~Monster() {
	delete effect;
}

//Repeatforever 애니메이션은 예외처리
void Monster::atkAction() {

	if (ms == Idle) {
		this->stopAction(animIdle);
	}
	else if (ms == Run) {
		this->stopAction(animRun);
	}
	else if (ms == Atk) {
		this->stopAction(animAtk);
	}
	else if (ms == Sheild) {
		this->stopAction(animSheild);
	}
	else if (ms == Cast) {
		this->stopAction(animCasting);
	}
	else if (ms == CastLoop) {
		this->stopAction(animCastLoop);
	}
	else if (ms == Die) {
		return;
	}

	ms = Atk;
	this->runAction(animAtk);
	log("공격");
}

void Monster::sheildAction() {

	if (ms == Idle) {
		this->stopAction(animIdle);
	}
	else if (ms == Run) {
		this->stopAction(animRun);
	}
	else if (ms == Atk) {
		this->stopAction(animAtk);
	}
	else if (ms == Sheild) {
		this->stopAction(animSheild);
	}
	else if (ms == Cast) {
		this->stopAction(animCasting);
	}
	else if (ms == CastLoop) {
		this->stopAction(animCastLoop);
	}
	else if (ms == Die) {
		return;
	}

	this->stopAction(animIdle);
	ms = Sheild;
	log("방어");
	this->runAction(animSheild);
}


//상태보기
void Monster::showState() {
	log("%f", monsterHp);
	log("%f", monsterMaxhp);
}

//기본상태로 돌아가기 위한 함수
void Monster::EndAnimation() {
	idleAction();
}
//처음 시작 될떄 실행할 애니메이션 함수
void Monster::StartAnimation() {
	idleAction();
}

void Monster::idleAction() {
	if (ms == Idle) {
		this->stopAction(animIdle);
	}
	else if (ms == Run) {
		this->stopAction(animRun);
	}
	else if (ms == Atk) {
		this->stopAction(animAtk);
	}
	else if (ms == Sheild) {
		this->stopAction(animSheild);
	}
	else if (ms == Cast) {
		this->stopAction(animCasting);
	}
	else if (ms == CastLoop) {
		this->stopAction(animCastLoop);
	}
	else if (ms == Die) {
		return;
	}
	ms = Idle;
	this->runAction(animIdle);
}

void Monster::runAction2() {
	if (ms == Idle) {
		this->stopAction(animIdle);
	}
	else if (ms == Run) {
		this->stopAction(animRun);
	}
	else if (ms == Atk) {
		this->stopAction(animAtk);
	}
	else if (ms == Sheild) {
		this->stopAction(animSheild);
	}
	else if (ms == Cast) {
		this->stopAction(animCasting);
	}
	else if (ms == CastLoop) {
		this->stopAction(animCastLoop);
	}
	else if (ms == Die) {
		return;
	}
	ms = Run;
	this->runAction(animRun);
}

void Monster::castingAction() {
	if (ms == Idle) {
		this->stopAction(animIdle);
	}
	else if (ms == Run) {
		this->stopAction(animRun);
	}
	else if (ms == Atk) {
		this->stopAction(animAtk);
	}
	else if (ms == Sheild) {
		this->stopAction(animSheild);
	}
	else if (ms == Cast) {
		this->stopAction(animCasting);
	}
	else if (ms == CastLoop) {
		this->stopAction(animCastLoop);
	}
	else if (ms == Die) {
		return;
	}
	ms = Cast;
	this->runAction(animCasting);
}

void Monster::castLoopAction() {
	if (ms == Idle) {
		this->stopAction(animIdle);
	}
	else if (ms == Run) {
		this->stopAction(animRun);
	}
	else if (ms == Atk) {
		this->stopAction(animAtk);
	}
	else if (ms == Sheild) {
		this->stopAction(animSheild);
	}
	else if (ms == Cast) {
		this->stopAction(animCasting);
	}
	else if (ms == CastLoop) {
		this->stopAction(animCastLoop);
	}
	else if (ms == Die) {
		return;
	}
	ms = CastLoop;
	this->runAction(animCastLoop);
}

void Monster::dieAction() {
	if (ms == Idle) {
		this->stopAction(animIdle);
	}
	else if (ms == Run) {
		this->stopAction(animRun);
	}
	else if (ms == Atk) {
		this->stopAction(animAtk);
	}
	else if (ms == Sheild) {
		this->stopAction(animSheild);
	}
	else if (ms == Cast) {
		this->stopAction(animCasting);
	}
	else if (ms == CastLoop) {
		this->stopAction(animCastLoop);
	}
	else if (ms == Die) {
		return;
	}
	ms = Die;
	this->runAction(animDie);
}

void Monster::setUI(Vec2 pos, Layer* uiLayer) {

	uiWindow = Sprite::create("boss/boss.png");
	uiWindow->setPosition(pos);
	uiLayer->addChild(uiWindow);
	
	Size ui_winSize = uiWindow->getContentSize();
	hpBar = Sprite::create("UI/hp_bar.png");
	hpBar->setAnchorPoint(Vec2(0, 0.5));
	hpBar->setPosition(Vec2(-150, ui_winSize.height/2 + 50));
	uiWindow->addChild(hpBar);

	Size hp_bar_size = hpBar->getContentSize();
	hpGauge = Sprite::create("UI/hp_gauge.png");
	hpGauge->setAnchorPoint(Vec2(0, 0.5));
	hpGauge->setPosition(Vec2(8, hp_bar_size.height/2));

	hpBar->addChild(hpGauge);

}

void Monster::Hit(double _damage) {

	//맞을떄 빨강색으로 변함
	auto act_hit = TintBy::create(0.2f, 0, 255, 255);
	auto act_hit2 = TintTo::create(0.2f, 255, 255, 255);
	auto seq = Sequence::create(act_hit, act_hit2, nullptr);
	this->runAction(seq);

	int pos = rand() % 20 + -10;
	if (ms != Die) {

		log("monster hp : %f", monsterHp);
		monsterHp = monsterHp - _damage;

		if (monsterHp < 0) {

			if (ms == Die) {
				return;
			}

			dieAction();
			monsterHp = 0;
		}

		//체력바 줄어드는 액션
		auto act = ScaleTo::create(0.1f, monsterHp / monsterMaxhp, 1);

		//피튀기는 이펙트
		effect->getTypePlayerEffect(10, Vec2(80 + pos, 50 + pos), this);
		effect->getTypePlayerEffect(11, Vec2(70 + pos, 60 + pos), this);

		hpGauge->runAction(act);
	}
	else {
		return;
	}

}

void Monster::monsterAI(float dt) {
	if (ms != Die) {
		//스킬 쓰기전 딜레이 애니메션 만들기
		auto sprite = Sprite::create("Skill/skill_loading.png");
		auto texture = sprite->getTexture();
		auto animation = Animation::create();
		animation->setDelayPerUnit(0.07f);

		for (int i = 0; i < 27; i++) {
			int colum = i % 6; // 0,1,2,3,4
			int row = i / 6; //0,1,2
							 // x,y 좌표 x로 얼마만큼  y로 얼마만큼
			animation->addSpriteFrameWithTexture(texture, Rect(colum * 100, row * 33, 100, 33));
		}

		auto act_loading = Sprite::create("Skill/skill_loading.png", Rect(0, 0, 100, 33));
		auto removeAction = CCCallFunc::create(CC_CALLBACK_0(CCNode::removeChild, this, act_loading, false));
		auto animate = Animate::create(animation);

		act_loading->setScale(0.5f);
		act_loading->setPosition(Vec2(65, 100));

		//랜덤 숫자를 설정해 숫자의 해당하는 공격패턴이 나감
		int atk_number = rand() % 3 + 1;
		log("실행  :  %d", atk_number);

		if (atk_number == 1) {
			auto seq = Sequence::create(animate, removeAction, CCCallFunc::create(CC_CALLBACK_0(Monster::atkAction, this)), nullptr);
			this->addChild(act_loading);
			act_loading->runAction(seq);
			//atkAction();
		}
		else if (atk_number == 2) {
			auto seq = Sequence::create(animate, removeAction, CCCallFunc::create(CC_CALLBACK_0(Monster::castingAction, this)), nullptr);
			this->addChild(act_loading);
			act_loading->runAction(seq);
			//castingAction();
		}
		else if (atk_number == 3) {
			auto seq = Sequence::create(animate, removeAction, CCCallFunc::create(CC_CALLBACK_0(Monster::castLoopAction, this)), nullptr);
			this->addChild(act_loading);
			act_loading->runAction(seq);
			//castLoopAction();
		}
	}
}