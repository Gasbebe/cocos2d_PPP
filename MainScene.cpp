#include "MainScene.h"
#include "HelloWorldScene.h"


USING_NS_CC;

Scene* MainScene::createScene() {
	auto scene = Scene::create();
	auto layer = MainScene::create();
	scene->addChild(layer);

	return scene;
}

bool MainScene::init() {
	if (!Layer::init())
	{
		return false;
	}
	winSize = Director::getInstance()->getWinSize();
	

	//background 천둥치는 하늘
	auto batch = SpriteBatchNode::create("background/16.png", 10);
	auto texture = batch->getTexture();

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);

	for (int i = 0; i < 18; i++) {
		int colum = i % 5;
		int row = i / 4;

		animation->addSpriteFrameWithTexture(texture, Rect(colum * 200, row * 100, 200, 100));
	}

	auto bg = Sprite::create("background/16.png", Rect(0, 0, 200, 100));

	bg->setScale(3.8f);
	bg->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	bg->setZOrder(-3);
	this->addChild(bg);

	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	bg->runAction(rep);


	//bg2 돌기둥 3개
	auto bg2 = Sprite::create("background/main_background.png");
	bg2->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(bg2);

	//스테이지 고르는 번호 
	stageNum = 1;
	flag = true;

	//케릭터 얼굴 창 이미지
	auto player_achor = Sprite::create("UI/player_achor.png");
	player_achor->setPosition(Vec2(winSize.width/2 - 80, winSize.height/2 + 50));
	addChild(player_achor);

	auto player_sword = Sprite::create("UI/player_sword.png");
	player_sword->setPosition(Vec2(winSize.width / 2 + 90, winSize.height / 2 + 50));
	addChild(player_sword);

	auto player_healer = Sprite::create("UI/player_healer.png");
	player_healer->setPosition(Vec2(winSize.width / 2 - 240, winSize.height / 2 + 50));
	addChild(player_healer);

	auto menuItem = MenuItemImage::create("button/button2_100px.png",
										  "button/button2_100px.png",
									      CC_CALLBACK_1(MainScene::moveScene, this));
	menuItem->setPosition(Vec2::ZERO);
	
	auto menu = Menu::create(menuItem, nullptr);
	menu->setPosition(Vec2(winSize.width/2 + 200, winSize.height/2));
	this->addChild(menu);
	
	

	return true;
}

void MainScene::selcetStage(int num) {

}

void MainScene::moveScene(Ref* pSender) {
	if (stageNum == 1) {
		if (flag) {
			auto pScene = HelloWorld::createScene();
			Director::getInstance()->replaceScene(pScene);
			flag = false;
		}
	}
	else {
		log("없는 스테이지 입니다");
	}
}