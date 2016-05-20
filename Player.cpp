#include "Player.h"
#include "SimpleAudioEngine.h"

#define SWORD_ATK_SOUND "Sound/sfx_f1_elyxstormblade_attack_impact.ogg"
#define HEALER_ATK_SOUND "Sound/sfx_unit_run_magical_4.ogg"
#define ARCHER_ATK_SOUND "Sound/sfx_neutral_makantorwarbeast_attack_impact.ogg"


USING_NS_CC;
using namespace CocosDenshion;

//생성될때 초기화
Player::Player(double hp, double maxhp, double def, int type){
	hpPer = 1.0f;
	effect = new Effect();
	effect->retain();
	playerHp = hp;
	playerMaxhp = maxhp;
	playerDef = def;
	effectType = type;

	atk_stack = 0;
	shield_stack = 0;

	bool bOk = initWithTexture(nullptr, Rect::ZERO);
	if (bOk) {
		this->autorelease();
	}
	ps = Idle;


	//캐릭터맵 폰트 파일 사용법
	//itemWidth , itemHeight는 같은 크기의 이미지로 된 스프라이트시트를 이용해
	//스프라이트 시트를 만들떄와 마찬가지로 글자 하나에 해당하는 크기를 나타낸다

	atkLabel = LabelAtlas::create("0", "number/numbers.png", 60, 86, '.');  //12 ,32 픽셀로 자름    '.'아스키코드값부터 시작 9까지
	atkLabel->setPosition(Vec2(30, 70));
	atkLabel->setScale(0.5f);
	atkLabel->setColor(Color3B::RED);
	this->addChild(atkLabel);

	shieldLabel = LabelAtlas::create("0", "number/numbers.png", 60, 86, '.');  //12 ,32 픽셀로 자름    '.'아스키코드값부터 시작 9까지
	shieldLabel->setPosition(Vec2(30, 70));
	shieldLabel->setScale(0.5f);
	shieldLabel->setColor(Color3B::BLUE);
	this->addChild(shieldLabel);


	//type 1 힐러  2 활  3검  
	//활은 공격스킬을 가지고 있어서 실드스택은  레이블 투명지정하는곳
	if (type == 2) {
		shieldLabel->setVisible(false);
	}
	else {
		atkLabel->setVisible(false);
	}


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

	AddAtkStack();
	setAtkLabel();

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

	AddShieldStack();
	setShieldLabel();

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

//이펙트랑 사운드 설정하는곳
void Player::setEffect(int number) {
	if (number == 1) {

		//플레이어가 성직자 일때 이펙트
		//힐러
		if (ps == Atk) {
			//effect->getTypePlayerEffect(3, Vec2(40, 40), this);
			
		}
		else if (ps == Sheild) {
			SimpleAudioEngine::getInstance()->playEffect(HEALER_ATK_SOUND);
			//방패 이펙트
			effect->getTypePlayerEffect(1, Vec2(50, 27), this);
			//힐 이펙트
			effect->getTypePlayerEffect(3, Vec2(40, 40), this);
		}
	
	}
	else if (number == 2) {

		//플레이어가 궁수 일때 이펙트
		if (ps == Atk) {
			SimpleAudioEngine::getInstance()->playEffect(ARCHER_ATK_SOUND);
		}
		else if (ps == Sheild) {
			
		}
	}
	else if (number == 3) {

		//플레이어가 검사 일떄 이펙트
		if (ps == Atk) {
			SimpleAudioEngine::getInstance()->playEffect(SWORD_ATK_SOUND);
		}
		else if (ps == Sheild) {
			effect->getTypePlayerEffect(2, Vec2(50, 40), this);
			effect->getTypePlayerEffect(1, Vec2(50, 27), this);
		}
	}
}

//공방 스택 제어
void Player::AddAtkStack() {
	atk_stack = atk_stack + 1;
	
	log("atk stack : %d", atk_stack);
	if (atk_stack > 3) {
		atk_stack = 0;
		setAtkLabel();
	}
}
void Player::AddShieldStack() {

	shield_stack = shield_stack + 1;

	log("shield stack : %d", shield_stack);
	if (shield_stack > 3) {
		shield_stack = 0;
		setShieldLabel();
	}
}

void Player::setAtkLabel() {

	char number[2];
	sprintf(number, "%d", atk_stack);
	atkLabel->setString(number);

}
void Player::setShieldLabel() {

	char number[2];
	sprintf(number, "%d", shield_stack);
	shieldLabel->setString(number);

}