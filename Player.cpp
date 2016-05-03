#include "Player.h"

USING_NS_CC;
//생성될때 초기화
Player::Player(double hp, double maxhp, double def){
	playerHp = hp;
	playerMaxhp = maxhp;
	playerDef = def;

	bool bOk = initWithTexture(nullptr, Rect::ZERO);
	if (bOk) {
		this->autorelease();
	}
	ps = Idle;

	//애니이션 멈춤 상태 확인
	stopAim = CallFunc::create(CC_CALLBACK_0(Player::EndAnimation,this));

//	bodyColl = Sprite::create("collisionBox/collisionBox.png");
//	bodyColl->setPosition(Vec2(50,40));
//	bodyColl->setZOrder(-1);
//	this->addChild(bodyColl);
}

bool Player::init() {
	return true;
}

void Player::setAction(bool type) {
	if (ps == Idle  || ps == Run || ps == Atk) {
		if (type) {
			runAction2();
			//atkAction();
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
void Player::atkAction() {
	//runAction
	if (ps == Idle) {
		this->stopAction(animIdle);
	}
	else if (ps == Run) {
		this->stopAction(animRun);
	}
	else if (ps == Atk) {
		this->stopAction(animAtk);
	}
	else if (ps == Sheild) {
		this->stopAction(animSheild);
	}

	ps = Atk;
	this->runAction(animAtk);
	log("공격");
}

void Player::sheildAction() {
	//runAction

	if (ps == Idle) {
		this->stopAction(animIdle);
	}
	else if (ps == Run) {
		this->stopAction(animRun);
	}
	else if (ps == Atk) {
		this->stopAction(animAtk);
	}
	else if (ps == Sheild) {
		this->stopAction(animSheild);
	}

	//this->stopAction(animIdle);
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
	
	idleAction();
}

void Player::StartAnimation() {
	idleAction();
}

void Player::idleAction() {
	ps = Idle;
	this->runAction(animIdle);
}

void Player::runAction2() {
	if (ps == Idle) {
		this->stopAction(animIdle);
	}
	else if (ps == Run) {
		this->stopAction(animRun);
	}
	else if (ps == Atk) {
		this->stopAction(animAtk);
	}
	else if (ps == Sheild) {
		this->stopAction(animSheild);
	}
	ps = Run;
	this->runAction(animRun);
}

void Player::dieAction() {
	this->runAction(animDie);
}

void Player::setUI(Vec2 pos, Layer* uiLayer) {

	uiWindow = Sprite::create("UI/player_ui.png");
	uiWindow->setPosition(pos);
	uiWindow->setScale(0.8);
	uiLayer->addChild(uiWindow);
	//cocos2d::Sprite* pace;

	Size ui_winSize = uiWindow->getContentSize();
	hpBar = Sprite::create("UI/hp_bar.png");
	hpBar->setAnchorPoint(Vec2(0, 0));
	hpBar->setPosition(Vec2(ui_winSize.width /2 - 10, ui_winSize.height /4  * 3));
	uiWindow->addChild(hpBar);

}