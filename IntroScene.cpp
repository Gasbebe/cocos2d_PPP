#include "IntroScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* IntroScene::createScene(){
	auto scene = Scene::create();
	auto layer = IntroScene::create();
	scene->addChild(layer);

	return scene;
}

bool IntroScene::init(){
	if (!Layer::init())
	{
		return false;
	}
	winSize = Director::getInstance()->getWinSize();

	///////////////
	//backgrond ///
	///////////////

	//auto batch = SpriteBatchNode::create("background/16.png", 10);
	//auto texture = batch->getTexture();

	//auto animation = Animation::create();
	//animation->setDelayPerUnit(0.1f);

	//for (int i = 0; i < 18; i++) {
	//	int colum = i % 5;
	//	int row = i / 4; 
	//					 
	//	animation->addSpriteFrameWithTexture(texture, Rect(colum * 200, row * 100, 200, 100));
	//}

	//auto bg = Sprite::create("background/16.png", Rect(0, 0, 200, 100));

	//bg->setScale(3.8f);
	//bg->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	//bg->setZOrder(-3);
	//this->addChild(bg);

	//auto animate = Animate::create(animation);
	//auto rep = RepeatForever::create(animate);
	//bg->runAction(rep);

	//auto rock = Sprite::create("background/rock.png");
	//rock->setPosition(Vec2(winSize.width/2, winSize.height/2));
	//this->addChild(rock);

	auto rock2 = Sprite::create("background/rock2.png");
	rock2->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(rock2);

	//auto rock3 = Sprite::create("background/rock3.png");
	//rock2->setPosition(Vec2(winSize.width / 2 - 200, winSize.height / 2));
	//this->addChild(rock3);

	auto logo = Sprite::create("background/logo.png");
	logo->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(logo);

	auto startBtn = MenuItemImage::create("button/shield_btn_press.png",
										 "button/shield_btn_press.png",
										  CC_CALLBACK_1(IntroScene::startGame, this));
	startBtn->setPosition(Vec2(0, 0));

	auto menu = Menu::create(startBtn, nullptr);
	menu->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(menu);
	
	return true;
}

void IntroScene::startGame(Ref* pSender) {

	auto pScene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(pScene);
}