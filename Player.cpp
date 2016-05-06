#include "Player.h"

USING_NS_CC;
//생성될때 초기화
Player::Player(double hp, double maxhp, double def, int type){
	effect = new Effect();
	effect->retain();
	playerHp = hp;
	playerMaxhp = maxhp;
	playerDef = def;
	effectType = type;

	bool bOk = initWithTexture(nullptr, Rect::ZERO);
	if (bOk) {
		this->autorelease();
	}
	ps = Idle;

	//애니이션 멈춤 상태 확인
	stopAim = CallFunc::create(CC_CALLBACK_0(Player::EndAnimation,this));

	//bodyColl = Sprite::create("collisionBox/collisionBox.png");
	//bodyColl->setPosition(Vec2(50,40));
	//bodyColl->setZOrder(-1);
//	this->addChild(bodyColl);
}
Player::~Player() {
	delete effect;
}

bool Player::init() {
	return true;
}

void Player::setAction(bool type) {
	if (ps != Die) {
		if (ps == Idle || ps == Run || ps == Atk) {
			if (type) {
				runAction2();
				//atkAction();
			}
			else {
				sheildAction();
			}
		}
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
	else if (ps == Die) {
		return;
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
	else if (ps == Die) {
		return;
	}

	//this->stopAction(animIdle);
	setEffect(effectType);
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
	else if (ps == Die) {
		return;
	}
	ps = Run;
	this->runAction(animRun);
}

void Player::dieAction() {
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
	else if (ps == Die) {
		this->stopAction(animDie);
	}

	ps = Die;
	this->runAction(animDie);
}

void Player::setUI(Vec2 pos, Layer* uiLayer) {

	uiWindow = Sprite::create("UI/player_ui.png");
	uiWindow->setPosition(pos);
	uiWindow->setScale(0.9);
	uiLayer->addChild(uiWindow);

	//cocos2d::Sprite* pace;

	Size ui_winSize = uiWindow->getContentSize();
	hpBar = Sprite::create("UI/hp_bar.png");
	hpBar->setAnchorPoint(Vec2(0, 0.5));
	hpBar->setPosition(Vec2(ui_winSize.width /2 - 10, ui_winSize.height /4  * 3));
	uiWindow->addChild(hpBar);

}

//체력 게이지
void Player::UpdateState() {
	double scale = (playerHp / playerMaxhp);
	//log("scale %f", scale);

}

void Player::Hit() {
	if (ps != Die) {
		playerHp = playerHp - 10;

		if (playerHp < 0) {
			if (ps == Die) {
				return;
			}
			dieAction();
			playerHp = 0;
		}

		auto act = ScaleTo::create(0.1f, playerHp / playerMaxhp, 1);
		hpBar->runAction(act);
	}
	else {
		return;
	}
}


void Player::setEffect(int number) {
	if (number == 1) {
		
	}
	else if (number == 2) {

	}
	else if (number == 3) {
		effect->getTypePlayerEffect(1, Vec2(50, 27), this);
		//effect->getTypePlayerEffect(2, Vec2(50, 30), this);
	}
}