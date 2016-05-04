#include "Monster.h"

Monster::Monster(double maxhp) {

	monsterHp = maxhp;
	monsterMaxhp = maxhp;
	bool bOk = initWithTexture(nullptr, Rect::ZERO);
	if (bOk) {
		this->autorelease();
	}
}

void Monster::setAction(bool type) {
	if (ms == Idle) {
		if (type) {
			atkAction();
		}
		else {
			sheildAction();
		}
	}
	else {
		return;
	}
}
//Repeatforever 애니메이션은 예외처리
void Monster::atkAction() {
	//runAction
	if (ms == Idle) {
		this->stopAction(animIdle);
	}
	else if (ms == Run) {
		this->stopAction(animRun);
	}

	ms = Atk;
	this->runAction(animAtk);
	log("공격");
}

void Monster::sheildAction() {
	//runAction
	if (ms == Idle) {
		this->stopAction(animIdle);
	}
	else if (ms == Run) {
		this->stopAction(animRun);
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

void Monster::StartAnimation() {
	idleAction();
}

void Monster::idleAction() {
	ms = Idle;
	this->runAction(animIdle);
}

void Monster::runAction2() {
	ms = Run;
	this->runAction(animRun);
}

void Monster::dieAction() {
	this->runAction(animDie);
}

void Monster::setUI(Vec2 pos, Layer* uiLayer) {

	uiWindow = Sprite::create("UI/player_ui.png");
	uiWindow->setPosition(pos);
	uiLayer->addChild(uiWindow);
	//cocos2d::Sprite* pace;

	Size ui_winSize = uiWindow->getContentSize();
	hpBar = Sprite::create("UI/hp_bar.png");
	hpBar->setAnchorPoint(Vec2(0, 0));
	hpBar->setPosition(Vec2(ui_winSize.width, ui_winSize.height));
	uiWindow->addChild(hpBar);

}

void Monster::Hit(double _damage) {
	monsterHp -= _damage;
}