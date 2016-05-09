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
	this->schedule(schedule_selector(Monster::monsterAI), 3.0f);
	stopAim = CallFunc::create(CC_CALLBACK_0(Monster::EndAnimation, this));
	//delayHit = CallFunc::create(CC_CALLBACK_0(Monster::Hit, this));

}

Monster::~Monster() {
	delete effect;
}

//Repeatforever �ִϸ��̼��� ����ó��
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
	log("����");
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
	log("���");
	this->runAction(animSheild);
}


//���º���
void Monster::showState() {
	log("%f", monsterHp);
	log("%f", monsterMaxhp);
}

//�⺻���·� ���ư��� ���� �Լ�
void Monster::EndAnimation() {
	idleAction();
}
//ó�� ���� �ɋ� ������ �ִϸ��̼� �Լ�
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
	if (ms != Die) {
		monsterHp = monsterHp - _damage;

		if (monsterHp < 0) {

			if (ms == Die) {
				return;
			}

			dieAction();
			monsterHp = 0;
		}

		//ü�¹� �پ��� �׼�
		auto act = ScaleTo::create(0.1f, monsterHp / monsterMaxhp, 1);

		//��Ƣ��� ����Ʈ
		effect->getTypePlayerEffect(10, Vec2(70, 50), this);
		effect->getTypePlayerEffect(11, Vec2(70, 70), this);

		hpGauge->runAction(act);
	}
	else {
		return;
	}
	log("monster hp : %f", monsterHp);
}

void Monster::monsterAI(float dt) {
	int atk_number = rand() % 3 + 1;
	log("����  :  %d" , atk_number);
	switch (atk_number) {
	case 1:
		atkAction();
		break;
	case 2:
		castingAction();
		break;
	case 3:
		castLoopAction();
		break;
	default:
		break;
	}
}