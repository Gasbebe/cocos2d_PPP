#include "Player.h"

USING_NS_CC;

Player::Player(double hp, double maxhp, double def){
	playerHp = hp;
	playerMaxhp = maxhp;
	playerDef = def;

	bool bOk = initWithTexture(nullptr, Rect::ZERO);
	if (bOk) {
		this->autorelease();
	}
	ps = Idle;
	stopAim = CallFunc::create(CC_CALLBACK_0(Player::EndAnimation,this));
}
bool Player::init() {
	return true;
}

void Player::setAction(bool type) {
	if (ps == Idle) {
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

void Player::atkAction() {
	//runAction
	//animatk;
	this->stopAction(animIdle);
	ps = Atk;
	this->runAction(animAtk);
	log("공격");
}

void Player::sheildAction() {
	//runAction
	//auto act = animsheild;
	this->stopAction(animIdle);
	ps = Sheild;
	log("방어");
	this->runAction(animSheild);
}


//상태보기
void Player::showState() {
	log("%f",playerHp);
	log("%f", playerMaxhp);
	log("%f", playerDef);
}

//기본상태로 돌아가기 위한 함수
void Player::EndAnimation() {
	ps = Idle;
	this->runAction(animIdle);
}

void Player::StartAnimation() {
	this->runAction(animIdle);
}


void Player::setPlayerUI(Vec2 pos, Layer* uiLayer) {

	uiWindow = Sprite::create("UI/ui.png");
	uiWindow->setPosition(pos);
	uiLayer->addChild(uiWindow);
	//cocos2d::Sprite* pace;

	Size ui_winSize = uiWindow->getContentSize();
	hpBar = Sprite::create("UI/hp_bar.png");
	hpBar->setAnchorPoint(Vec2(0, 0));
	hpBar->setPosition(Vec2(ui_winSize.width, ui_winSize.height));
	uiWindow->addChild(hpBar);

}