#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"

#define MAINMUSIC "Sound/music_challengemode.ogg"

USING_NS_CC;

using namespace CocosDenshion;
using namespace cocos2d::extension;

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
	
	flag = true;

	//시작 오디오
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MAINMUSIC);
	SimpleAudioEngine::getInstance()->playBackgroundMusic(MAINMUSIC, true);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0f);

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

	//케릭터 얼굴 창 이미지 아처
	auto player_achor = Sprite::create("UI/player_achor.png");
	player_achor->setPosition(Vec2(winSize.width/2 - 80, winSize.height/2 + 50));
	addChild(player_achor);

	//소드맨 이미지
	auto player_sword = Sprite::create("UI/player_sword.png");
	player_sword->setPosition(Vec2(winSize.width / 2 + 90, winSize.height / 2 + 50));
	addChild(player_sword);

	//힐러 이미지
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
	
	
	//테이블 생성
	TableView* tableView1 = TableView::create(this, Size(300, 100));
	tableView1->setDirection(ScrollView::Direction::HORIZONTAL);
	tableView1->setPosition(Vec2(50, 50));
	tableView1->setDelegate(this);
	tableView1->setTag(100);
	this->addChild(tableView1);
	tableView1->reloadData();

	//TableView* tableView2 = TableView::create(this, Size(60, 250));
	//tableView2->setDirection(ScrollView::Direction::VERTICAL);
	//tableView2->setPosition(Vec2(330, 40));
	//tableView2->setDelegate(this);
	//tableView2->setTag(200);
	//tableView2->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	//this->addChild(tableView2);
	//tableView2->reloadData();

	return true;
}

void MainScene::selcetStage(int num) {
	stageNum = num;
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

Size MainScene::tableCellSizeForIndex(TableView* table, ssize_t idx) {
	if (idx == 2) {
		return Size(100, 100);
	}
	return Size(60, 60);
}

TableViewCell* MainScene::tableCellAtIndex(TableView *table, ssize_t idx) {
	auto string = String::createWithFormat("%ld", idx);
	TableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new CustomTableViewCell();
		cell->autorelease();

		auto sprite = Sprite::create("Images/boss1.png");
		sprite->setAnchorPoint(Vec2::ZERO);
		sprite->setPosition(Vec2(0, 0));
		cell->addChild(sprite);

		auto label = LabelTTF::create(string->getCString(), "Helvetica", 20.0);
		label->setPosition(Vec2::ZERO);
		label->setAnchorPoint(Vec2::ZERO);
		label->setTag(123);
		cell->addChild(label);
	}
	else {
		auto label = (LabelTTF*)cell->getChildByTag(123);
		label->setString(string->getCString());
	}
	return cell;
}

ssize_t MainScene::numberOfCellsInTableView(TableView* table) {
	return 10;
}

void MainScene::tableCellTouched(TableView* table, TableViewCell* cell) {
	log("Tag : %d\nCell touched at index : %ld",
		table->getTag(),
		cell->getIdx());
}