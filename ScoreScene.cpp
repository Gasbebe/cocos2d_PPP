#include "SimpleAudioEngine.h"
#include "ScoreScene.h"
#include "MainScene.h"

#define SCOREMUSIC "Sound/music_mainmenu_songhai.ogg"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"

void ScorecallJavaMethod(std::string func, std::string arg0)
{
	JniMethodInfo t;

	/**
	JniHelper를 통해 org/cocos2dx/cpp/에 있는
	AppActivity class의 파라미터로 들어온 스트링 이름의 함수 정보를 가져온다.
	*/
	if (JniHelper::getStaticMethodInfo(t
		, "org/cocos2dx/cpp/AppActivity"
		, func.c_str()
		, "(Ljava/lang/String;)V"))
	{
		jstring stringArg0 = t.env->NewStringUTF(arg0.c_str());
		// 함수 호출
		t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg0);
		// Release
		t.env->DeleteLocalRef(t.classID);
	}
}
#endif

USING_NS_CC;
using namespace CocosDenshion;

Scene* ScoreScene::createScene()
{
	auto scene = Scene::create();
	auto layer = ScoreScene::create();
	scene->addChild(layer);

	return scene;
}

bool ScoreScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	flag = true;
	/////////////////////////////
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(SCOREMUSIC);
	SimpleAudioEngine::getInstance()->playBackgroundMusic(SCOREMUSIC, true);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0f);

	winSize = Director::getInstance()->getWinSize();
	//background
	auto backlight = Sprite::create("background/light.png");
	backlight->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(backlight);

	auto action = FadeIn::create(2.0f);
	auto action2 = FadeOut::create(2.0f);
	auto seq = Sequence::create(action, action2, nullptr);
	auto rep = RepeatForever::create(seq);

	backlight->runAction(rep);

	auto bg = Sprite::create("background/162.png");
	bg->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	//bg->setZOrder(-3);
	this->addChild(bg);

	auto logo = Sprite::create("background/scorelogo.png");
	logo->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	//bg->setZOrder(-3);
	this->addChild(logo);
	

	// 메뉴 아이템 생성 및 초기화
	MenuItemFont::setFontName("fonts/Marker Felt.ttf");
	MenuItemFont::setFontSize(20);

	auto pMenuItem1 = MenuItemImage::create(
		"button/rank_btn.png",
		"button/rank_btn_press.png",
		CC_CALLBACK_1(ScoreScene::doShowLeaderBoard, this));
	pMenuItem1->setPosition(Vec2(winSize.width / 2 - 200, 40));

	auto pMenuItem2 = MenuItemImage::create(
		"button/retry_btn.png",
		"button/retry_btn_press.png",
		CC_CALLBACK_1(ScoreScene::moveScene, this));
	pMenuItem2->setPosition(Vec2(winSize.width / 2, 40));

	auto pMenuItem3 = MenuItemImage::create(
		"button/quit_btn.png",
		"button/quit_btn_press.png",
		CC_CALLBACK_1(ScoreScene::quitGame, this));
	pMenuItem3->setPosition(Vec2(winSize.width / 2 + 200, 40));

	auto pMenu = Menu::create(
		pMenuItem1, pMenuItem2, pMenuItem3,
		nullptr);

	pMenu->setPosition(Vec2(0, 0));

	this->addChild(pMenu);

	scoreLabel = LabelAtlas::create("0", "number/numbers.png", 60, 85, '.');  //12 ,32 픽셀로 자름    '.'아스키코드값부터 시작 9까지
	scoreLabel->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	scoreLabel->setScale(0.5f);
	this->addChild(scoreLabel);
	
	score = UserDefault::getInstance()->getIntegerForKey("int_key");
	setLabelScore(score);
	//--------------------------------------------------------------
	return true;
}


void ScoreScene::doShowLeaderBoard(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	ScorecallJavaMethod("ShowLeaderBoard", "");
#endif
}

void ScoreScene::moveScene(Ref* pSender)
{
	if (flag) {
		auto pScene = MainScene::createScene();
		Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, pScene));
		flag = false;
	}
}

void ScoreScene::quitGame(Ref* pSender) {
	Director::getInstance()->end();
}

void ScoreScene::setLabelScore(int time_score) {

	char num[100];
	sprintf(num, "%d", time_score);

	scoreLabel->setString(num);

}