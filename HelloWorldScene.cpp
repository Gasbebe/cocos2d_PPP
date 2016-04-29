#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);

	return scene;
}

bool HelloWorld::init()
{

	if (!Layer::init())
	{
		return false;
	}

	winSize = Director::getInstance()->getWinSize();
	texture = Director::getInstance()->
		getTextureCache()->
		addImage("blocks.png");
	
	//button
	/*
	atkBtn = new Button();
	atkBtn->setTexture("button/button2_100px.png");
	atkBtn->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(atkBtn);

	shelidBtn = new Button();
	shelidBtn->setTexture("button/button1_100px.png");
	shelidBtn->setPosition(Vec2(winSize.width / 2 - 200, winSize.height / 2));
	this->addChild(shelidBtn);
	*/

	setCharectorAnimations();
	
	//command 
	command = new Command();
	command->setPosition(Vec2(winSize.width / 2, (winSize.height / 8) * 7));
	this->addChild(command);
	//

	//menuItem  atkBtn  SheildBtn 
	auto pMenuItem = MenuItemImage::create(
		"button/atk_btn.png",
		"button/atk_btn_press.png"
		,CC_CALLBACK_1(HelloWorld::Test, this));
	pMenuItem->setPosition(Vec2(winSize.width / 8, winSize.height / 8));

	
	auto pMenuItem2 = MenuItemImage::create(
		"button/shield_btn.png",
		"button/shield_btn_press.png"
		,CC_CALLBACK_1(HelloWorld::Test2, this));
	pMenuItem2->setPosition(Vec2((winSize.width / 8) * 7, winSize.height / 8));
	
	auto menu = Menu::create(pMenuItem, pMenuItem2, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	if (createBox2dWorld(true)) {
		this->schedule(schedule_selector(HelloWorld::tick));
	}

	//backgrond
	
	bg = Sprite::create("UI/bg.png");
	bg->setPosition(Vec2(winSize.width/2, winSize.height/2));
	bg->setZOrder(-1);
	this->addChild(bg);
	

	//sprite add body 
	playerBody = addNewSprite(player1->getPosition(), Size(50, 50), b2_dynamicBody, player1, 0);
	this->addNewSprite(monster->getPosition(), Size(80, 150), b2_dynamicBody, monster, 0);
	
	return true;
}

bool HelloWorld::createBox2dWorld(bool debug) {
	b2Vec2 gravity = b2Vec2(0.0f, -30.0f);

	_world = new b2World(gravity);
	_world->SetAllowSleeping(true);
	_world->SetContinuousPhysics(true);

	if (debug) {
		m_debugDraw = new GLESDebugDraw(PTM_RATIO);
		_world->SetDebugDraw(m_debugDraw);

		uint32 flags = 0;
		flags += b2Draw::e_shapeBit;
		flags += b2Draw::e_jointBit;

		m_debugDraw->SetFlags(flags);
	}

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);

	b2Body *groundBody = _world->CreateBody(&groundBodyDef);

	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;

	groundEdge.Set(b2Vec2(0, ((winSize.height/2) - (winSize.height / 4)) / PTM_RATIO), b2Vec2(winSize.width / PTM_RATIO, ((winSize.height / 2) - (winSize.height / 4)) / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	groundEdge.Set(b2Vec2(0, 0), b2Vec2(0, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	groundEdge.Set(b2Vec2(0, winSize.height / PTM_RATIO),
		b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	groundEdge.Set(b2Vec2(winSize.width / PTM_RATIO, 0),
		b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	return true;
}

HelloWorld::~HelloWorld() {
	delete _world;
	_world = nullptr;
}

void HelloWorld::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	Layer::draw(renderer, transform, flags);

	_customCmd.init(_globalZOrder, transform, flags);
	_customCmd.func = CC_CALLBACK_0(HelloWorld::onDraw, this, transform, flags);
	renderer->addCommand(&_customCmd);
}

void HelloWorld::onDraw(const Mat4 &transform, uint32_t flags)
{
	Director* director = Director::getInstance();
	CCASSERT(nullptr != director, "Director is null when seting matrix stack");
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

	GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION);
	_world->DrawDebugData();
	CHECK_GL_ERROR_DEBUG();

	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void HelloWorld::onEnter() {
	Layer::onEnter();

	Device::setAccelerometerEnabled(true);
	auto listener = EventListenerTouchOneByOne::create();
	auto listener2 = EventListenerAcceleration::create(CC_CALLBACK_2(HelloWorld::onAcceleration, this));

	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);

}

void HelloWorld::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
	//Device::setAccelerometerEnabled(false);

	Layer::onExit();
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *event) {
	return true;
}

void HelloWorld::onTouchMoved(Touch *touch, Event *event) {

}

void HelloWorld::onTouchEnded(Touch *touch, Event *event) {

}

void HelloWorld::tick(float dt) {
	//log("%f", dt);
	int velocityInterations = 8;
	int positionInterations = 3;

	_world->Step(dt, velocityInterations, positionInterations);

	for (b2Body *b = _world->GetBodyList(); b; b = b->GetNext()) {
		if (b->GetUserData() != nullptr) {
			Sprite* spriteData = (Sprite *)b->GetUserData();
			spriteData->setPosition(
				Vec2(b->GetPosition().x * PTM_RATIO,
					b->GetPosition().y * PTM_RATIO));
			spriteData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}
	//player1, 2, ,3 이 다완성 되면 for문으로 묶어 3개를 다돌린다
	if (player1->ps == player1->Run) {
		playerBody->ApplyForceToCenter(b2Vec2(30, 0), true);
	}
	else if (player1->ps == player1->Sheild) {
		playerBody->ApplyForceToCenter(b2Vec2(-30, 0), true);
	}
}

b2Body* HelloWorld::addNewSprite(Vec2 point, Size size, b2BodyType bodytype, Sprite* sprtie, int type) {
	b2BodyDef bodyDef;
	bodyDef.type = bodytype;
	bodyDef.position.Set(point.x / PTM_RATIO, point.y / PTM_RATIO);
	bodyDef.userData = sprtie;


	b2Body *body = _world->CreateBody(&bodyDef);

	b2FixtureDef fixtureDef;
	b2PolygonShape dynamicBox;
	b2CircleShape circle;

	if (type == 0) {
		dynamicBox.SetAsBox(size.width / 2 / PTM_RATIO, size.height / 2 / PTM_RATIO);

		fixtureDef.shape = &dynamicBox;
	}
	else {
		circle.m_radius = (size.width / 2) / PTM_RATIO;

		fixtureDef.shape = &circle;
	}

	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.0f;

	body->CreateFixture(&fixtureDef);

	return body;
}

//atk btn 이름 나중에 바꾸기
void HelloWorld::Test(Ref* pSender) {
	log("test");
	//1 이면 빨강색 버튼 2이면 파랑색버튼
	command->ViewCommand(1); 
	int count;

	//커맨드 3칸이 넘으면 
	count = command->count;
	if (count > 3) {
		onAction();
	}
}

//sheild btn 이름 나중에 바꾸기
void HelloWorld::Test2(Ref* pSender) {
	log("test2");
	command->ViewCommand(2);
	int count;

	count = command->count;
	if (count > 3) {
		onAction();
	}
	//player1->showState();
	//player2->showState();
}

//Commnad클래스에서 트루 값을 받아온다 플레이어 액션 실행하는곳
void HelloWorld::onAction() {
	bool bAction;
	bAction = command->playingAction();

	if (bAction) {
		player1->setAction(command->getActionType(0));
		//player2->setAction(command->getActionType(1));
		//player3->setAction(command->getActionType(2));
	}

}

void HelloWorld::setCharectorAnimations() {

	//player1 애니메이션 정의
	player1 = new Player(10, 20, 30);
	player1->setPosition(Vec2(winSize.width / 2, winSize.height / 2));

	//animation cache 추가
	cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("animations/f5_altgeneral.plist");
	cache->addSpriteFramesWithFile("animations/f1_elyxstormblade.plist");


	//player1 animation idle
	Vector<SpriteFrame*> player1_animFramesIdle;
	char str[100] = { 0 };
	
	for (int i = 1; i < 12; i++) {
		sprintf(str, "f1_elyxstormblade_idle_%003d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		player1_animFramesIdle.pushBack(frame);
	}

	auto p1_idle_animation = Animation::createWithSpriteFrames(player1_animFramesIdle, 0.1f);
	auto p1_idle_animate = Animate::create(p1_idle_animation);
	auto player1_AnimIdle = RepeatForever::create(p1_idle_animate);
	
	//player1 animation atk
	Vector<SpriteFrame*> player1_animFramesAtk;
	
	for (int i = 1; i < 12; i++) {
		sprintf(str, "f1_elyxstormblade_attack_%003d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		player1_animFramesAtk.pushBack(frame);
	}

	auto p1_atk_animation = Animation::createWithSpriteFrames(player1_animFramesAtk, 0.1f);
	auto p1_atk_animate = Animate::create(p1_atk_animation);
	auto player1_AnimAtk = Sequence::create(p1_atk_animate, player1->stopAim, nullptr);

	//player animation shield
	Vector<SpriteFrame*> player1_animFramesShield;

	for (int i = 1; i < 7; i++) {
		sprintf(str, "f1_elyxstormblade_run_007.png");
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		player1_animFramesShield.pushBack(frame);
	}

	auto p1_shield_animation = Animation::createWithSpriteFrames(player1_animFramesShield, 0.1f);
	auto p1_shield_animate = Animate::create(p1_shield_animation);
	auto player1_AnimShield = Sequence::create(p1_shield_animate, player1->stopAim, nullptr);

	//player animation run
	Vector<SpriteFrame*> player1_animFramesRun;

	for (int i = 1; i < 8; i++) {
		sprintf(str, "f1_elyxstormblade_run_%003d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		player1_animFramesRun.pushBack(frame);
	}

	auto p1_run_animation = Animation::createWithSpriteFrames(player1_animFramesRun, 0.1f);
	auto p1_run_animate = Animate::create(p1_run_animation);
	auto player1_AnimRun = RepeatForever::create(p1_run_animate);

	//검사 액션
	auto act = Spawn::create(player1_AnimRun, MoveBy::create(2, Vec2(200,0)),nullptr);
	//auto seq = Sequence::create(act, p1_atk_animate, nullptr);


	//player animation die
	Vector<SpriteFrame*> player1_animFramesDie;

	for (int i = 1; i < 11; i++) {
		sprintf(str, "f1_elyxstormblade_death_%003d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		player1_animFramesDie.pushBack(frame);
	}

	auto p1_die_animation = Animation::createWithSpriteFrames(player1_animFramesDie, 0.1f);
	auto p1_die_animate = Animate::create(p1_die_animation);
	auto player1_AnimDie = Sequence::create(p1_die_animate, player1->stopAim, nullptr);


	//player1  idle 스프라이트
	player1->setSpriteFrame("f1_elyxstormblade_idle_001.png"); //vector의 처음으로 들어간 데이터
	this->addChild(player1);

	player1->animAtk = player1_AnimAtk;
	player1->animAtk->retain();

	player1->animSheild = player1_AnimShield;
	player1->animSheild->retain();

	player1->animIdle = player1_AnimIdle;
	player1->animIdle->retain();

	player1->animRun = player1_AnimRun;
	player1->animRun->retain();

	player1->EndAnimation();
	player1->setUI(Vec2(winSize.width / 4, winSize.height / 8), this);

	player2 = new Player(10, 10, 10);
	player3 = new Player(20, 20, 20);


	//////////////////////////////
	//       monster            //
	/////////////////////////////

	monster = new Monster(1000);

	//monster animation idle
	Vector<SpriteFrame*> monster_animFramesIdle;

	for (int i = 1; i < 14; i++) {
		sprintf(str, "f5_altgeneral_idle_%003d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		monster_animFramesIdle.pushBack(frame);
	}

	auto m_idle_animation = Animation::createWithSpriteFrames(monster_animFramesIdle, 0.1f);
	auto m_idle_animate = Animate::create(m_idle_animation);
	auto m_AnimIdle = RepeatForever::create(m_idle_animate);

	//monster animation atk
	Vector<SpriteFrame*> monster_animFramesAtk;

	for (int i = 1; i < 19; i++) {
		sprintf(str, "f5_altgeneral_attack_%003d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		monster_animFramesAtk.pushBack(frame);
	}

	auto m_atk_animation = Animation::createWithSpriteFrames(player1_animFramesAtk, 0.1f);
	auto m_atk_animate = Animate::create(p1_atk_animation);
	auto m_AnimAtk = Sequence::create(m_atk_animate, nullptr);

	//monster animation shield
	Vector<SpriteFrame*> monster_animFramesShield;

	for (int i = 1; i < 7; i++) {
		sprintf(str, "f5_altgeneral_run_007.png");
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		monster_animFramesShield.pushBack(frame);
	}

	auto m_shield_animation = Animation::createWithSpriteFrames(monster_animFramesShield, 0.1f);
	auto m_shield_animate = Animate::create(m_shield_animation);
	auto monster_AnimShield = Sequence::create(m_shield_animate, nullptr);

	//monster animation run
	Vector<SpriteFrame*> monster_animFramesRun;

	for (int i = 1; i < 8; i++) {
		sprintf(str, "f5_altgeneral_run_%003d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		monster_animFramesRun.pushBack(frame);
	}

	auto m_run_animation = Animation::createWithSpriteFrames(monster_animFramesRun, 0.1f);
	auto m_run_animate = Animate::create(m_run_animation);
	auto m_AnimRun = Sequence::create(m_run_animate, nullptr);

	//monster animation die
	Vector<SpriteFrame*> monster_animFramesDie;

	for (int i = 1; i < 14; i++) {
		sprintf(str, "f5_altgeneral_death_%003d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		monster_animFramesDie.pushBack(frame);
	}

	auto m_die_animation = Animation::createWithSpriteFrames(monster_animFramesDie, 0.1f);
	auto m_die_animate = Animate::create(m_die_animation);
	auto m_AnimDie = Sequence::create(m_die_animate, nullptr);

	monster->setSpriteFrame("f5_altgeneral_idle_000.png");
	monster->setPosition(Vec2((winSize.width / 8) * 7, winSize.height / 2));
	monster->setFlipX(true);
	monster->setScale(1.5f);
	monster->runAction(m_AnimIdle);
	this->addChild(monster);
	
}
