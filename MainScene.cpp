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

	//스테이지 고르는 번호 
	stageNum = 1;
	flag = true;

	//케릭터 얼굴 창 이미지
	auto player_achor = Sprite::create("UI/player_achor.png");
	player_achor->setPosition(Vec2(winSize.width/2, winSize.height/2));
	addChild(player_achor);

	auto player_sword = Sprite::create("UI/player_sword.png");
	player_sword->setPosition(Vec2(winSize.width / 2 + 100, winSize.height / 2));
	addChild(player_sword);

	auto player_healer = Sprite::create("UI/player_healer.png");
	player_healer->setPosition(Vec2(winSize.width / 2 - 100, winSize.height / 2));
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