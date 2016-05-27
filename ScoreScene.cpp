#include "ScoreScene.h"

USING_NS_CC;


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"

void callJavaMethod(std::string func, std::string arg0)
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

Scene* ScoreScene::createScene()
{
	auto scene = Scene::create();
	auto layer = ScoreScene::create();
	scene->addChild(layer);

	return scene;
}

bool ScoreScene::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}

	/////////////////////////////

	// 메뉴 아이템 생성 및 초기화

	MenuItemFont::setFontName("fonts/Marker Felt.ttf");
	MenuItemFont::setFontSize(20);

	auto pMenuItem1 = MenuItemFont::create(
		" 최고점수 ",
		CC_CALLBACK_1(ScoreScene::doSendScore, this));
	pMenuItem1->setColor(Color3B(0, 0, 0));
	pMenuItem1->setPosition(Vec2(180, 180));

	auto pMenuItem2 = MenuItemFont::create(
		" 소요시간 ",
		CC_CALLBACK_1(ScoreScene::doSendTime, this));
	pMenuItem2->setColor(Color3B(0, 0, 0));
	pMenuItem2->setPosition(Vec2(300, 180));

	auto pMenuItem3 = MenuItemFont::create(
		" 일회성 업적 ",
		CC_CALLBACK_1(ScoreScene::doSendOne, this));
	pMenuItem3->setColor(Color3B(0, 0, 0));
	pMenuItem3->setPosition(Vec2(180, 130));

	auto pMenuItem4 = MenuItemFont::create(
		" 단계별 업적 ",
		CC_CALLBACK_1(ScoreScene::doSendMulti, this));
	pMenuItem4->setColor(Color3B(0, 0, 0));
	pMenuItem4->setPosition(Vec2(300, 130));

	auto pMenuItem5 = MenuItemFont::create(
		" 리더보드 ",
		CC_CALLBACK_1(ScoreScene::doShowLeaderBoard, this));
	pMenuItem5->setColor(Color3B(0, 0, 0));
	pMenuItem5->setPosition(Vec2(180, 80));

	auto pMenuItem6 = MenuItemFont::create(
		" 업적보기 ",
		CC_CALLBACK_1(ScoreScene::doShowAchivement, this));
	pMenuItem6->setColor(Color3B(0, 0, 0));
	pMenuItem6->setPosition(Vec2(300, 80));

	auto pMenu = Menu::create(
		pMenuItem1, pMenuItem2, pMenuItem3, pMenuItem4,
		pMenuItem5, pMenuItem6,
		nullptr);

	pMenu->setPosition(Vec2(0, 0));

	this->addChild(pMenu);

	txtNum = 10;
	//--------------------------------------------------------------
	return true;
}


void ScoreScene::doSendScore(Ref* pSender)
{
	log("%s", txtNum.c_str());
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	callJavaMethod("SendScore", txtNum);
#endif
}

void ScoreScene::doSendTime(Ref* pSender)
{
	log("%s", txtNum.c_str());
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	callJavaMethod("SendTime", txtNum);
#endif
}

void ScoreScene::doSendOne(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	callJavaMethod("SendOne", "");
#endif
}

void ScoreScene::doSendMulti(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	callJavaMethod("SendMulti", "");
#endif
}

void ScoreScene::doShowLeaderBoard(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	callJavaMethod("ShowLeaderBoard", "");
#endif
}

void ScoreScene::doShowAchivement(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	callJavaMethod("ShowAchivement", "");
#endif
}

void ScoreScene::setScore(std::string score) {
	txtNum = score;
}