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
	log("����");
}

void Player::sheildAction() {
	//runAction
	//auto act = animsheild;
	this->stopAction(animIdle);
	ps = Sheild;
	log("���");
	this->runAction(animSheild);
}


//���º���
void Player::showState() {
	log("%f",playerHp);
	log("%f", playerMaxhp);
	log("%f", playerDef);
}

//�⺻���·� ���ư��� ���� �Լ�
void Player::EndAnimation() {
	ps = Idle;
	this->runAction(animIdle);
}

void Player::StartAnimation() {
	this->runAction(animIdle);
}