#include "Command.h"
#include "HelloWorldScene.h"

Command::Command() {

	count = COMMAND_INIT_NUMBER;
	bOnActive = true;

	bool bOk = initWithTexture(nullptr, Rect::ZERO);
	if (bOk) {
		this->autorelease();
	}
	this->setTexture("UI/command2.png");

	commandSize = this->getTextureRect().size;

	
	//atk = Sprite::create("button/button2_100px.png");
	//sheild = Sprite::create("button/button1_100px.png");

	//이미지 수정 완료
	sprite1 = Sprite::create("UI/state_ui.png");
	sprite1->setPosition(Vec2(commandSize.width/2 - 120, commandSize.height / 4));
	sprite1->setScale(0.5f);
	this->addChild(sprite1);

	sprite2 = Sprite::create("UI/state_ui.png");
	sprite2->setPosition(Vec2(commandSize.width / 2 + 30, commandSize.height / 4));
	sprite2->setScale(0.5f);
	this->addChild(sprite2);

	sprite3 = Sprite::create("UI/state_ui.png");
	sprite3->setPosition(Vec2(commandSize.width / 2 + 180 , commandSize.height / 4));
	sprite3->setScale(0.5f);
	this->addChild(sprite3);

	//label = LabelTTF::create("ooooo", "Arial", 34,
	//	Size(300, 200), TextHAlignment::CENTER,
	//	TextVAlignment::CENTER);
	//label->setColor(Color3B::WHITE);// 255,0,0
	//								 //pLabel->setAnchorPoint(Vec2(0, 0.5));

	//								 //레이블의 위치 지정
	//label->setPosition(Vec2(commandSize.width/2, commandSize.height/2 + 200));

	////레이블의 투명도 지정  0~255
	//label->setOpacity(100.0);

	////레이블에 레이블 객체 추가
	//this->addChild(label);

}

void Command::Test() {
	log("command Test");
}


void Command::ViewCommand(int number) {
	//예외처리  bOnActive 화면에 나와있을때만 누르는게 가능하다
	//count 1 2 3 은 각각 버튼의 위치
	if (bOnActive) {
		if (count == 1) {
			if (number == 1) {
				sprite1->setTexture("UI/atk_state_ui.png");
				sprite1->setOpacity(250.0f);
				bAction[0] = true;
			}
			else {
				sprite1->setTexture("UI/shield_state_ui.png");
				sprite1->setOpacity(250.0f);
				bAction[0] = false;
			}
		}
		else if (count == 2) {
			if (number == 1) {
				sprite2->setTexture("UI/atk_state_ui.png");
				sprite2->setOpacity(250.0f);
				bAction[1] = true;
			}
			else {
				sprite2->setTexture("UI/shield_state_ui.png");
				sprite2->setOpacity(250.0f);
				bAction[1] = false;
			}
		}
		else if (count == 3) {
			if (number == 1) {
				sprite3->setTexture("UI/atk_state_ui.png");
				sprite3->setOpacity(250.0f);
				bAction[2] = true;
			}
			else {
				sprite3->setTexture("UI/shield_state_ui.png");
				sprite3->setOpacity(250.0f);
				bAction[2] = false;
			}
			
			//atk  shield action 확인하는 로그  true면 atk  false면 shield
			for (int i = 0; i < 3; i++) {
				if (bAction[i]) {
					log("true");
				}
				else {
					log("false");
				}
			}
			//플레이어 액션실행
			playerAction();

			auto seq = Sequence::create(CallFunc::create(CC_CALLBACK_0(Command::setOnActive, this)), 
										DelayTime::create(1.2f), CallFunc::create(CC_CALLBACK_0(Command::setOnActive, this)), nullptr);
			this->runAction(seq);
		}
		count++;
	}
	else {
		log("안눌림");
		//label->setString("안눌림");
	}
	log("count = %d ", count);
}

//버튼 눌릴지 말지 정하는곳
void Command::setOnActive() {

	if (bOnActive) {
		bOnActive = false;
		auto act = Sequence::create(DelayTime::create(0.2f), CallFunc::create(CC_CALLBACK_0(Command::hideCommand, this)), nullptr);
		this->runAction(act);

		count = COMMAND_INIT_NUMBER;
	}
	else {
		bOnActive = true;
		this->setOpacity(250.0f);
		
		//초기상태 이미지로 되돌린다
		sprite1->setOpacity(250.0f);
		sprite1->setTexture("UI/state_ui.png");

		sprite2->setOpacity(250.0f);
		sprite2->setTexture("UI/state_ui.png");

		sprite3->setOpacity(250.0f);
		sprite3->setTexture("UI/state_ui.png");
		//label->setString("커맨드 생성");
	}

}

//버튼 늦게 숨길려고 쓰는거
void Command::hideCommand() {

	sprite1->setOpacity(0.0f);
	sprite2->setOpacity(0.0f);
	sprite3->setOpacity(0.0f);

	this->setOpacity(0.0f);

}

//플레이어 케릭터들에게 액션 타입 넘겨줌
bool Command::getActionType(int num) {
	return bAction[num];
}

//helloWorld에 있는 onAction실행시키기 위해서 사용
bool Command::playingAction() {
	return true;
}
void Command::pressAtkBtn(Ref* pSender) {
	ViewCommand(1);
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