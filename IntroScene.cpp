#include "IntroScene.h"

#include "MainScene.h"
#include "SimpleAudioEngine.h"

#define INTROMUSIC "Sound/music_battlemap01.ogg"

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
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(INTROMUSIC);
	SimpleAudioEngine::getInstance()->playBackgroundMusic(INTROMUSIC, true);
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


	//공중 돌 이미지 및 움직임
	auto rock4 = Sprite::create("background/rock4.png");
	rock4->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(rock4);

	auto act_rock4 = MoveBy::create(1.0f, Vec2(0, 10));
	auto seq3 = Sequence::create(act_rock4, act_rock4->reverse(), nullptr);
	auto rep3 = RepeatForever::create(seq3);

	rock4->runAction(rep3);


	//땅 바닥 돌
	auto rock = Sprite::create("background/rock.png");
	rock->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(rock);


	//픽셀 파타퐁 로고 
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
		//SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		//TransitionCrossFade::create(t, s);
		//Director::getInstance()->pushScene(createTransition(num1++, 1, pScene));
		//auto tran = TransitionCrossFade::create(pScene, 0.5);
		Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, pScene));
		flag = false;
	}
}