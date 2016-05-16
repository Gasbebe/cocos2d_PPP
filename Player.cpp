#include "Player.h"

USING_NS_CC;
//생성될때 초기화
Player::Player(double hp, double maxhp, double def, int type){
	hpPer = 1.0f;
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
	setEffect(effectType);
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
	
	ps = Sheild;
	log("방어");
	this->runAction(animSheild);
	setEffect(effectType);
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
	//uiWindow->setScale(0.9);
	uiLayer->addChild(uiWindow);

	//cocos2d::Sprite* pace;

	Size ui_winSize = uiWindow->getContentSize();
	hpBar = Sprite::create("UI/hp_bar.png");
	hpBar->setAnchorPoint(Vec2(0, 0.5));
	hpBar->setPosition(Vec2(ui_winSize.width / 2 - 4, ui_winSize.height / 4 * 3));
	hpBar->setScaleX(0.35f);
	uiWindow->addChild(hpBar);

	Size hp_bar_size = hpBar->getContentSize();
	hpGauge = Sprite::create("UI/hp_gauge.png");
	hpGauge->setAnchorPoint(Vec2(0, 0.5));
	hpGauge->setPosition(Vec2(8, hp_bar_size.height / 2));

	hpBar->addChild(hpGauge);

}

//체력 게이지
void Player::UpdateState() {
	double scale = (playerHp / playerMaxhp);
	//log("scale %f", scale);

}

void Player::Hit(double damage) {

	auto act_hit = TintBy::create(0.2f, 0, 255, 255);
	auto act_hit2 = TintTo::create(0.2f, 255, 255, 255);
	auto seq = Sequence::create(act_hit, act_hit2, nullptr);
	this->runAction(seq);

	int pos = rand() % 20 + -10;

	if (ps != Die) {
		playerHp = playerHp - damage;

		//플레이어 체력이 0이하면 죽음 액션을 취하고 상태를 다이로 바꿈
		//이미 죽어 있는 상태이면 리턴
		if (playerHp <= 0) {
			if (ps == Die) {
				return;
			}
			dieAction();
			playerHp = 0;
		}

		auto act = ScaleTo::create(0.1f, playerHp / playerMaxhp, 1);
		hpPer = playerHp / playerMaxhp;
		hpGauge->runAction(act);
		effect->getTypePlayerEffect(10, Vec2(40 + pos, 40 + pos), this);
		effect->getTypePlayerEffect(11, Vec2(40 + pos, 40 + pos), this);
	}
	else {
		return;
	}
}

void Player::Heal() {
	effect->getTypePlayerEffect(3, Vec2(40, 40), this);

	if (ps != Die) {
		playerHp = playerHp + 20;

		if (playerMaxhp < playerHp) {
			playerHp = playerMaxhp;
		}
		auto act = ScaleTo::create(0.1f, playerHp / playerMaxhp, 1);
		hpPer = playerHp / playerMaxhp;
		hpGauge->runAction(act);
	}
	else {
		return;
	}
}


void Player::setEffect(int number) {
	if (number == 1) {
		//플레이어가 성직자 일때 이펙트
		//힐러
		if (ps == Atk) {
			//effect->getTypePlayerEffect(3, Vec2(40, 40), this);
		}
		else if (ps == Sheild) {
			effect->getTypePlayerEffect(1, Vec2(50, 27), this);
			//힐 이펙트
			effect->getTypePlayerEffect(3, Vec2(40, 40), this);
		}
	
	}
	else if (number == 2) {
		//플레이어가 궁수 일때 이펙트
		//방패
		if (ps == Atk) {
			
		}
		else if (ps == Sheild) {
			
		}
	}
	else if (number == 3) {
		//플레이어가 검사 일떄 이펙트
		if (ps == Atk) {
			
		}
		else if (ps == Sheild) {
			effect->getTypePlayerEffect(2, Vec2(50, 30), this);
			effect->getTypePlayerEffect(1, Vec2(50, 27), this);
		}
	}
}