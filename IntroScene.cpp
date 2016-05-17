#include "IntroScene.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

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
	flag = true;
	winSize = Director::getInstance()->getWinSize();


	//인트로 오디오
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sound/music_battlemap01.ogg");
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/music_battlemap01.ogg", true);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0f);


	///////////////
	//backgrond ///
	///////////////

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

	//rock
	//auto rock3 = Sprite::create("background/rock3.png");
	//rock3->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	//this->addChild(rock3);
	//
	//auto act_rock3 = MoveBy::create(2.0f, Vec2(0, 30));
	//auto seq2 = Sequence::create(act_rock3, act_rock3->reverse(), nullptr);
	//auto rep2 = RepeatForever::create(seq2);

	//rock3->runAction(rep2);

	auto rock4 = Sprite::create("background/rock4.png");
	rock4->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(rock4);

	auto act_rock4 = MoveBy::create(1.0f, Vec2(0, 10));
	auto seq3 = Sequence::create(act_rock4, act_rock4->reverse(), nullptr);
	auto rep3 = RepeatForever::create(seq3);

	rock4->runAction(rep3);

	auto rock = Sprite::create("background/rock.png");
	rock->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(rock);

	//auto rock2 = Sprite::create("background/rock2.png");
	//rock2->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	//this->addChild(rock2);

	auto logo = Sprite::create("background/logo.png");
	logo->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(logo);

	auto startBtn = MenuItemImage::create("UI/touch_Screen.png",
										 "UI/touch_Screen.png",
										  CC_CALLBACK_1(IntroScene::startGame, this));
	startBtn->setPosition(Vec2(0, 0));

	auto menu = Menu::create(startBtn, nullptr);
	menu->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(menu);
	
	return true;
}

void IntroScene::startGame(Ref* pSender) {
	if (flag) {
		auto pScene = MainScene::createScene();
		Director::getInstance()->replaceScene(pScene);
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		flag = false;
	}
}