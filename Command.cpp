#include "Command.h"
#include "HelloWorldScene.h"

Command::Command() {
	count = 1;

	bool bOk = initWithTexture(nullptr, Rect::ZERO);
	if (bOk) {
		this->autorelease();
	}
	this->setTexture("UI/command2.png");

	commandSize = this->getTextureRect().size;

	
	atk = Sprite::create("button/button2_100px.png");
	sheild = Sprite::create("button/button1_100px.png");

	//�̹��� ���߿� �ٲٱ�
	sprite1 = Sprite::create("button/button2_100px.png");
	sprite1->setPosition(Vec2(commandSize.width/2 - 100, commandSize.height / 2));
	sprite1->setScale(0.5f);
	sprite1->setOpacity(0.0f);
	this->addChild(sprite1);

	sprite2 = Sprite::create("button/button2_100px.png");
	sprite2->setPosition(Vec2(commandSize.width / 2, commandSize.height / 2));
	sprite2->setScale(0.5f);
	sprite2->setOpacity(0.0f);
	this->addChild(sprite2);

	sprite3 = Sprite::create("button/button2_100px.png");
	sprite3->setPosition(Vec2(commandSize.width / 2 + 100 , commandSize.height / 2));
	sprite3->setScale(0.5f);
	sprite3->setOpacity(0.0f);
	this->addChild(sprite3);

}

void Command::Test() {
	log("command Test");
}


void Command::ViewCommand(int number) {
	//����ó��  bOnActive ȭ�鿡 ������������ �����°� �����ϴ�
	//count 1 2 3 �� ���� ��ư�� ��ġ
	if (bOnActive) {
		if (count == 1) {
			if (number == 1) {
				sprite1->setTexture("button/button2_100px.png");
				sprite1->setOpacity(250.0f);
				bAction[0] = true;
			}
			else {
				sprite1->setTexture("button/button1_100px.png");
				sprite1->setOpacity(250.0f);
				bAction[0] = false;
			}
		}
		else if (count == 2) {
			if (number == 1) {
				sprite2->setTexture("button/button2_100px.png");
				sprite2->setOpacity(250.0f);
				bAction[1] = true;
			}
			else {
				sprite2->setTexture("button/button1_100px.png");
				sprite2->setOpacity(250.0f);
				bAction[1] = false;
			}
		}
		else if (count == 3) {
			if (number == 1) {
				sprite3->setTexture("button/button2_100px.png");
				sprite3->setOpacity(250.0f);
				bAction[2] = true;
			}
			else {
				sprite3->setTexture("button/button1_100px.png");
				sprite3->setOpacity(250.0f);
				bAction[2] = false;
			}
			
			//atk  shield action Ȯ���ϴ� �α�  true�� atk  false�� shield
			for (int i = 0; i < 3; i++) {
				if (bAction[i]) {
					log("true");
				}
				else {
					log("false");
				}
			}
			//�÷��̾� �׼ǽ���
			playerAction();

			auto seq = Sequence::create(CallFunc::create(CC_CALLBACK_0(Command::setOnActive, this)), 
										DelayTime::create(1.2f), CallFunc::create(CC_CALLBACK_0(Command::setOnActive, this)), nullptr);
			this->runAction(seq);
		}
		count++;
	}
	else {
		count = 1;
		log("�ȴ���");
	}
	log("count = %d ", count);
}

//��ư ������ ���� ���ϴ°�
void Command::setOnActive() {

	if (bOnActive) {
		bOnActive = false;
		auto act = Sequence::create(DelayTime::create(0.2f), CallFunc::create(CC_CALLBACK_0(Command::hideCommand, this)), nullptr);
		this->runAction(act);

		count = 1;
	}
	else {
		bOnActive = true;
		this->setOpacity(250.0f);
	}

}

//��ư �ʰ� ������� ���°�
void Command::hideCommand() {

	sprite1->setOpacity(0.0f);
	sprite2->setOpacity(0.0f);
	sprite3->setOpacity(0.0f);
	this->setOpacity(0.0f);

}

//�÷��̾� �ɸ��͵鿡�� �׼� Ÿ�� �Ѱ���
bool Command::getActionType(int num) {
	return bAction[num];
}

//helloWorld�� �ִ� onAction�����Ű�� ���ؼ� ���
bool Command::playingAction() {
	return true;
}
void Command::pressAtkBtn(Ref* pSender) {
	ViewCommand(1);
	p3->Hit();
}
void Command::pressShieldBtn(Ref* pSender) {
	ViewCommand(2);
}

void Command::setBtnUI(Vec2 pos, Layer* layer) {

	auto pMenuItem = MenuItemImage::create(
		"button/atk_btn.png",
		"button/atk_btn_press.png"
		, CC_CALLBACK_1(Command::pressAtkBtn, this));
	pMenuItem->setPosition(Vec2(commandSize.width/ 2 - 270, commandSize.height / 8 - 230));

	auto pMenuItem2 = MenuItemImage::create(
		"button/shield_btn.png",
		"button/shield_btn_press.png"
		, CC_CALLBACK_1(Command::pressShieldBtn, this));
	pMenuItem2->setPosition(Vec2(commandSize.width /2 + 270, commandSize.height /8 - 230));

	auto menu = Menu::create(pMenuItem, pMenuItem2, nullptr);
	menu->setPosition(pos);
	this->addChild(menu);
}

void Command::setPlayerAction(Player *_p1, Player *_p2, Player *_p3) {

	p1 = _p1;
	p2 = _p2;
	p3 = _p3;
}

void Command::playerAction() {
	p1->setAction(getActionType(0));
	p2->setAction(getActionType(1));
	p3->setAction(getActionType(2));
}