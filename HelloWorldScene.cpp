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

	b_bullet = false;
	flag = true;
	winSize = Director::getInstance()->getWinSize();

	//effect  this부분에 Backgound 레이어 만들어서 넣을것
	effect = new Effect();
	effect->retain();
	effect->getTypeEffect(1, Vec2(winSize.width / 2, winSize.height / 2), this);
	effect->getTypeEffect(2, Vec2(winSize.width / 2 + 20, winSize.height / 2), this);
	effect->getTypeEffect(3, Vec2(winSize.width / 2 + 40, winSize.height / 2), this);
	effect->getTypeEffect(4, Vec2(winSize.width / 2 + 60, winSize.height / 2), this);
	effect->getTypeEffect(5, Vec2(winSize.width / 2 + 80, winSize.height / 2), this);
	effect->getTypeEffect(6, Vec2(winSize.width / 2 + 100, winSize.height / 2), this);
	effect->getTypeEffect(7, Vec2(winSize.width / 2 + 120, winSize.height / 2), this);
	effect->getTypeEffect(8, Vec2(winSize.width / 2 + 140, winSize.height / 2), this);
	effect->getTypeEffect(9, Vec2(winSize.width / 2 + 160, winSize.height / 2), this);
	effect->getTypeEffect(10, Vec2(winSize.width / 2 + 180, winSize.height / 2), this);
	effect->getTypeEffect(11, Vec2(winSize.width / 2 + 200, winSize.height / 2), this);

	//command 
	command = new Command();
	command->setPosition(Vec2(winSize.width / 2, (winSize.height / 8) * 7));

	//btn
	command->setBtnUI(Vec2(0, 0), this);
	this->addChild(command);
	
	setCharectorAnimations();
	
	if (createBox2dWorld(true)) {
		this->schedule(schedule_selector(HelloWorld::tick));
	}
	
	///////////////
	//backgrond ///
	///////////////
	
	//auto batch = SpriteBatchNode::create("background/16.png", 10);
	//auto texture = batch->getTexture();

	//auto animation = Animation::create();
	//animation->setDelayPerUnit(0.1f);

	//for (int i = 0; i < 18; i++) {
	//	int colum = i % 5; // 0,1,2,3,4
	//	int row = i / 4; //0,1,2
	//					 // x,y 좌표 x로 얼마만큼  y로 얼마만큼
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
	
	////////////////////
	//sprite add body //
	////////////////////

	player1Body = addNewSprite(player1Coll->getPosition(), Size(50, 50), b2_dynamicBody, player1Coll, 0);
	player2Body = addNewSprite(player2Coll->getPosition(), Size(50, 50), b2_dynamicBody, player2Coll, 0);
	player3Body = addNewSprite(player3Coll->getPosition(), Size(45, 50), b2_dynamicBody, player3Coll, 0);

	this->addNewSprite(monsterColl->getPosition(), monsterColl->getContentSize(), b2_dynamicBody, monsterColl, 1);
	
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

	delete command;
	delete player1;
	delete player2;
	delete player3;
	delete monster;
	delete effect;

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

	//player2 화살체크
	for (int i = 0; i < _arrow.size(); i++) {
		auto arrows = (Sprite*)_arrow.at(i);
		if (arrow->boundingBox().intersectsRect(monsterColl->boundingBox())){
			effect->getTypeEffect(9, Vec2(arrow->getPosition()), this);
			removeChild(arrow, false);
			_arrow.erase(_arrow.begin()+i);
			monster->Hit(10);
		}
	}

	//player1, 2, ,3 이 다완성 되면 for문으로 묶어 3개를 다돌린다
	//플레이어 이동제어
	for (int i = 1; i < 4; i++) {
		if (i == 1) {
			if (player1->ps == player1->Run) {
				double dis;
				dis = monsterColl->getPosition().x - player1Coll->getPosition().x;
				if (dis > 300) {
					player1Body->ApplyForceToCenter(b2Vec2(35, 0), true);
				}
				else {
					//힐을 할때 뒤로 밀려난다
					player1Body->ApplyForceToCenter(b2Vec2(-400, 0), true);
					player1->atkAction();
				}
			}
			else if (player1->ps == player1->Sheild) {
				player1Body->ApplyForceToCenter(b2Vec2(-27, 0), true);
			}
		}
		else if (i == 2) {
			if (player2->ps == player2->Run) {

				double dis;
				dis = monsterColl->getPosition().x - player2Coll->getPosition().x;

				if (dis > 400) {
					player2Body->ApplyForceToCenter(b2Vec2(35, 0), true);
				}
				else {
					//활을 쏠때 뒤로밀려난다
					player2Body->ApplyForceToCenter(b2Vec2(-550, 0), true);
					player2->atkAction();
					
					//슈팅부분
					auto seq = Sequence::create(DelayTime::create(0.7), CallFunc::create(CC_CALLBACK_0(HelloWorld::shooting, this)), nullptr);
					this->runAction(seq);
				}
			}
			else if (player2->ps == player2->Sheild) {
				player2Body->ApplyForceToCenter(b2Vec2(-35, 0), true);
			}
		}
		else {
			if (player3->ps == player3->Run) {
				double dis;
				dis = monsterColl->getPosition().x - player3Coll->getPosition().x;
				if (dis > 70) {
					player3Body->ApplyForceToCenter(b2Vec2(27, 0), true);
				}
				else {
					effect->getTypeEffect(6, player3Coll->getPosition(), this);
					player3->atkAction();
				}
			}
			else if (player3->ps == player3->Sheild) {
				player3Body->ApplyForceToCenter(b2Vec2(-25, 0), true);
			}
			else if (player3->ps == player3->Atk) {
				if (player3Coll->boundingBox().intersectsRect(monsterColl->boundingBox())) {
					if (flag) {
						//auto delay = DelayTime::create(0.2f);
						//auto seq = Sequence::create(delay, monster->delayHit, delay, monster->delayHit, nullptr);
						//runAction(seq);
						//flag = false;
						monster->Hit(10);
						flag = false;
					}
					
				}
			}
		}
	}
	

	//monster 
	if (monster->ms != monster->Die) {
		if (monster->ms == monster->Atk) {

		}
		else if (monster->ms == monster->Cast) {
			if (player1->ps != player1->Sheild) {
				player1Body->ApplyForceToCenter(b2Vec2(-25, 40), true);
			}
			if (player2->ps != player2->Sheild) {
				player2Body->ApplyForceToCenter(b2Vec2(-25, 40), true);
			}
			if (player3->ps != player3->Sheild) {
				player3Body->ApplyForceToCenter(b2Vec2(-25, 40), true);
			}
		}
		else if (monster->ms == monster->CastLoop) {

		}
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

	dynamicBox.SetAsBox(size.width / 2 / PTM_RATIO, size.height / 2 / PTM_RATIO);
	fixtureDef.shape = &dynamicBox;

	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.2f;
	//filter.categoryBits = ...;
	if (type == 0) {
		fixtureDef.filter.maskBits = 0x0001;
		fixtureDef.filter.groupIndex = -1;
		fixtureDef.filter.categoryBits = 0x0001;
	}

	body->CreateFixture(&fixtureDef);

	return body;
}

void HelloWorld::setCharectorAnimations() {
	/////////////////////
	//  Player       ///
	////////////////////
	

	//player1 애니메이션 정의
	player1 = new Player(10, 20, 30, 1);
	

	//animation cache 추가
	cache = SpriteFrameCache::getInstance();

	//boss
	cache->addSpriteFramesWithFile("animations/f5_altgeneral.plist");

	//player1
	cache->addSpriteFramesWithFile("animations/f1_sunstonetemplar.plist");

	//player2
	cache->addSpriteFramesWithFile("animations/neutral_mercswornavanger.plist");

	//player3
	cache->addSpriteFramesWithFile("animations/f1_elyxstormblade.plist");
	
	//player1 animation idle

	
	Vector<SpriteFrame*> player1_animFramesIdle;
	char str[100] = { 0 };

	
	for (int i = 1; i < 10; i++) {
		sprintf(str, "f1_sunstonetemplar_idle_%003d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		player1_animFramesIdle.pushBack(frame);
	}

	auto p1_idle_animation = Animation::createWithSpriteFrames(player1_animFramesIdle, 0.1f);
	auto p1_idle_animate = Animate::create(p1_idle_animation);
	auto player1_AnimIdle = RepeatForever::create(p1_idle_animate);
	
	//player1 animation atk
	Vector<SpriteFrame*> player1_animFramesAtk;
	
	for (int i = 1; i < 19; i++) {
		sprintf(str, "f1_sunstonetemplar_attack_%003d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		player1_animFramesAtk.pushBack(frame);
	}

	auto p1_atk_animation = Animation::createWithSpriteFrames(player1_animFramesAtk, 0.1f);
	auto p1_atk_animate = Animate::create(p1_atk_animation);
	auto player1_AnimAtk = Sequence::create(p1_atk_animate, player1->stopAim, nullptr);

	//player1 animation shield
	Vector<SpriteFrame*> player1_animFramesShield;

	for (int i = 0; i < 5; i++) {
		sprintf(str, "f1_sunstonetemplar_death_%003d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		player1_animFramesShield.pushBack(frame);
	}

	auto p1_shield_animation = Animation::createWithSpriteFrames(player1_animFramesShield, 0.1f);
	auto p1_shield_animate = Animate::create(p1_shield_animation);
	auto player1_AnimShield = Sequence::create(p1_shield_animate, player1->stopAim, nullptr);

	//player1 animation run
	Vector<SpriteFrame*> player1_animFramesRun;

	for (int i = 1; i < 8; i++) {
		sprintf(str, "f1_sunstonetemplar_run_%003d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		player1_animFramesRun.pushBack(frame);
	}

	auto p1_run_animation = Animation::createWithSpriteFrames(player1_animFramesRun, 0.1f);
	auto p1_run_animate = Animate::create(p1_run_animation);
	auto player1_AnimRun = RepeatForever::create(p1_run_animate);

	//검사 액션
	auto act = Spawn::create(player1_AnimRun, MoveBy::create(2, Vec2(200,0)),nullptr);
	//auto seq = Sequence::create(act, p1_atk_animate, nullptr);


	//player1 animation die
	Vector<SpriteFrame*> player1_animFramesDie;

	for (int i = 1; i < 12; i++) {
		sprintf(str, "f1_sunstonetemplar_death_%003d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		player1_animFramesDie.pushBack(frame);
	}

	auto p1_die_animation = Animation::createWithSpriteFrames(player1_animFramesDie, 0.1f);
	auto p1_die_animate = Animate::create(p1_die_animation);
	auto player1_AnimDie = Sequence::create(p1_die_animate, nullptr);


	//player1  idle 스프라이트
	player1->setSpriteFrame("f1_sunstonetemplar_idle_001.png"); //vector의 처음으로 들어간 데이터
	//this->addChild(player1);

	player1->animAtk = player1_AnimAtk;
	player1->animAtk->retain();

	player1->animSheild = player1_AnimShield;
	player1->animSheild->retain();

	player1->animIdle = player1_AnimIdle;
	player1->animIdle->retain();

	player1->animRun = player1_AnimRun;
	player1->animRun->retain();

	player1->animDie = player1_AnimDie;
	player1->animDie->retain();

	player1->EndAnimation();
	player1->setUI(Vec2((winSize.width / 8 ) * 3 - 70, winSize.height / 8), this);

	player1Coll = Sprite::create("collisionBox/collisionBox.png");
	player1Coll->setPosition(Vec2((winSize.width / 8), winSize.height / 2));
	player1Coll->setZOrder(-1);
	//player1Coll->setOpacity(0);
	this->addChild(player1Coll);

	
	auto p1CollSize = player1Coll->getContentSize();
	player1->setPosition(Vec2(p1CollSize.width / 2, p1CollSize.height / 2));
	player1Coll->addChild(player1);

	//////////////////////////
	//player2   /////////////
	/////////////////////////

	//player2 애니메이션 정의
	player2 = new Player(10, 20, 30, 2);

	//player2 animation idle
	Vector<SpriteFrame*> player2_animFramesIdle;

	for (int i = 1; i < 11; i++) {
		sprintf(str, "neutral_mercswornavanger_idle_%003d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		player2_animFramesIdle.pushBack(frame);
	}

	auto p2_idle_animation = Animation::createWithSpriteFrames(player2_animFramesIdle, 0.1f);
	auto p2_idle_animate = Animate::create(p2_idle_animation);
	auto player2_AnimIdle = RepeatForever::create(p2_idle_animate);

	//player2 animation atk
	Vector<SpriteFrame*> player2_animFramesAtk;

	for (int i = 1; i < 14; i++) {
		sprintf(str, "neutral_mercswornavanger_attack_%003d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		player2_animFramesAtk.pushBack(frame);
	}

	auto p2_atk_animation = Animation::createWithSpriteFrames(player2_animFramesAtk, 0.1f);
	auto p2_atk_animate = Animate::create(p2_atk_animation);
	auto player2_AnimAtk = Sequence::create(p2_atk_animate, player2->stopAim, nullptr);

	//player2 animation shield
	Vector<SpriteFrame*> player2_animFramesShield;

	for (int i = 0; i < 3; i++) {
		sprintf(str, "neutral_mercswornavanger_hit_%003d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		player2_animFramesShield.pushBack(frame);
	}

	auto p2_shield_animation = Animation::createWithSpriteFrames(player2_animFramesShield, 0.15f);
	auto p2_shield_animate = Animate::create(p2_shield_animation);
	auto player2_AnimShield = Sequence::create(p2_shield_animate, player2->stopAim, nullptr);

	//player2 animation run
	Vector<SpriteFrame*> player2_animFramesRun;

	for (int i = 1; i < 8; i++) {
		sprintf(str, "neutral_mercswornavanger_run_%003d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		player2_animFramesRun.pushBack(frame);
	}

	auto p2_run_animation = Animation::createWithSpriteFrames(player2_animFramesRun, 0.1f);
	auto p2_run_animate = Animate::create(p2_run_animation);
	auto player2_AnimRun = RepeatForever::create(p2_run_animate);

	//player2 animation die
	Vector<SpriteFrame*> player2_animFramesDie;

	for (int i = 1; i < 9; i++) {
		sprintf(str, "neutral_mercswornavanger_death_%003d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		player2_animFramesDie.pushBack(frame);
	}

	auto p2_die_animation = Animation::createWithSpriteFrames(player2_animFramesDie, 0.1f);
	auto p2_die_animate = Animate::create(p2_die_animation);
	auto player2_AnimDie = Sequence::create(p2_die_animate, nullptr);


	//player2  idle 스프라이트
	player2->setSpriteFrame("neutral_mercswornavanger_idle_001.png"); //vector의 처음으로 들어간 데이터

	player2->animAtk = player2_AnimAtk;
	player2->animAtk->retain();

	player2->animSheild = player2_AnimShield;
	player2->animSheild->retain();

	player2->animIdle = player2_AnimIdle;
	player2->animIdle->retain();

	player2->animRun = player2_AnimRun;
	player2->animRun->retain();

	player2->animDie = player2_AnimDie;
	player2->animDie->retain();

	player2->EndAnimation();
	player2->setUI(Vec2(winSize.width / 2, winSize.height / 8), this);

	player2Coll = Sprite::create("collisionBox/collisionBox.png");
	player2Coll->setPosition(Vec2((winSize.width / 8 * 3), winSize.height / 2));
	player2Coll->setZOrder(-1);
	//player1Coll->setOpacity(0);
	this->addChild(player2Coll);


	auto p2CollSize = player2Coll->getContentSize();
	player2->setPosition(Vec2(p2CollSize.width / 2, p2CollSize.height / 2));
	player2Coll->addChild(player2);

	//////////////////////
	//player3  ///////////
	/////////////////////

	//player3 애니메이션 정의
	player3 = new Player(100, 100, 30, 3);

	//player3 animation idle
	Vector<SpriteFrame*> player3_animFramesIdle;

	for (int i = 1; i < 12; i++) {
		sprintf(str, "f1_elyxstormblade_idle_%003d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		player3_animFramesIdle.pushBack(frame);
	}

	auto p3_idle_animation = Animation::createWithSpriteFrames(player3_animFramesIdle, 0.1f);
	auto p3_idle_animate = Animate::create(p3_idle_animation);
	auto player3_AnimIdle = RepeatForever::create(p3_idle_animate);

	//player3 animation atk
	Vector<SpriteFrame*> player3_animFramesAtk;

	for (int i = 1; i < 12; i++) {
		sprintf(str, "f1_elyxstormblade_attack_%003d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		player3_animFramesAtk.pushBack(frame);
	}

	auto p3_atk_animation = Animation::createWithSpriteFrames(player3_animFramesAtk, 0.1f);
	auto p3_atk_animate = Animate::create(p3_atk_animation);
	auto player3_AnimAtk = Sequence::create(p3_atk_animate, player3->stopAim, nullptr);

	//player3 animation shield
	Vector<SpriteFrame*> player3_animFramesShield;

	for (int i = 1; i < 7; i++) {
		sprintf(str, "f1_elyxstormblade_run_007.png");
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		player3_animFramesShield.pushBack(frame);
	}

	auto p3_shield_animation = Animation::createWithSpriteFrames(player3_animFramesShield, 0.1f);
	auto p3_shield_animate = Animate::create(p3_shield_animation);
	auto player3_AnimShield = Sequence::create(p3_shield_animate, player3->stopAim, nullptr);

	//player3 animation run
	Vector<SpriteFrame*> player3_animFramesRun;

	for (int i = 1; i < 8; i++) {
		sprintf(str, "f1_elyxstormblade_run_%003d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		player3_animFramesRun.pushBack(frame);
	}

	auto p3_run_animation = Animation::createWithSpriteFrames(player3_animFramesRun, 0.1f);
	auto p3_run_animate = Animate::create(p3_run_animation);
	auto player3_AnimRun = RepeatForever::create(p3_run_animate);

	//player3 animation die
	Vector<SpriteFrame*> player3_animFramesDie;

	for (int i = 1; i < 11; i++) {
		sprintf(str, "f1_elyxstormblade_death_%003d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		player3_animFramesDie.pushBack(frame);
	}

	auto p3_die_animation = Animation::createWithSpriteFrames(player3_animFramesDie, 0.1f);
	auto p3_die_animate = Animate::create(p3_die_animation);
	auto player3_AnimDie = Sequence::create(p3_die_animate, nullptr);


	//player3  idle 스프라이트
	player3->setSpriteFrame("f1_elyxstormblade_idle_001.png"); //vector의 처음으로 들어간 데이터

	player3->animAtk = player3_AnimAtk;
	player3->animAtk->retain();

	player3->animSheild = player3_AnimShield;
	player3->animSheild->retain();

	player3->animIdle = player3_AnimIdle;
	player3->animIdle->retain();

	player3->animRun = player3_AnimRun;
	player3->animRun->retain();

	player3->animDie = player3_AnimDie;
	player3->animDie->retain();

	player3->EndAnimation();
	player3->setUI(Vec2((winSize.width / 8)  * 5 + 70, winSize.height / 8), this);

	player3Coll = Sprite::create("collisionBox/collisionBox2.png");
	player3Coll->setPosition(Vec2((winSize.width / 8) * 4, winSize.height / 2));
	player3Coll->setZOrder(-1);
	//player1Coll->setOpacity(0);
	this->addChild(player3Coll);


	auto p3CollSize = player3Coll->getContentSize();
	player3->setPosition(Vec2(p3CollSize.width / 2, p3CollSize.height / 2));
	player3Coll->addChild(player3);

	////////////
	//command///
	////////////

	command->setPlayerAction(player1, player2, player3);


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

	auto m_atk_animation = Animation::createWithSpriteFrames(monster_animFramesAtk, 0.1f);
	auto m_atk_animate = Animate::create(m_atk_animation);
	auto m_AnimAtk = Sequence::create(m_atk_animate, monster->stopAim, nullptr);

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
	auto m_AnimRun = RepeatForever::create(m_run_animate);

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
	
	//monster animation casting
	Vector<SpriteFrame*> monster_animFramesCasting;

	for (int i = 0; i < 14; i++) {
		sprintf(str, "f5_altgeneral_casting_%003d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		monster_animFramesCasting.pushBack(frame);
	}

	auto m_casting_animation = Animation::createWithSpriteFrames(monster_animFramesCasting, 0.1f);
	auto m_casting_animate = Animate::create(m_casting_animation);
	auto m_AnimCasting = Sequence::create(m_casting_animate, monster->stopAim, nullptr);

	//monster anumation castLoop
	Vector<SpriteFrame*> monster_animFramesCastLoop;

	for (int i = 0; i < 8; i++) {
		sprintf(str, "f5_altgeneral_castloop_%003d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		monster_animFramesCastLoop.pushBack(frame);
	}

	auto m_cast_loop_animation = Animation::createWithSpriteFrames(monster_animFramesCastLoop, 0.1f);
	auto m_cast_loop_animate = Animate::create(m_cast_loop_animation);
	auto m_AnimCastLoop = Sequence::create(m_cast_loop_animate, m_cast_loop_animate, monster->stopAim , nullptr);

	monster->animAtk = m_AnimAtk;
	monster->animAtk->retain();

	monster->animCasting = m_AnimCasting;
	monster->animCasting->retain();

	monster->animDie = m_AnimDie;
	monster->animDie->retain();

	monster->animRun = m_AnimRun;
	monster->animRun->retain();

	monster->animCastLoop = m_AnimCastLoop;
	monster->animCastLoop->retain();

	monster->animIdle = m_AnimIdle;
	monster->animIdle->retain();

	monster->setSpriteFrame("f5_altgeneral_idle_000.png");
	monster->setFlipX(true);
	monster->setScale(1.5f);
	monster->StartAnimation();

	//충돌 체크할 스프라이트추가
	monsterColl = Sprite::create("collisionBox/BossCollisionBox.png");
	monsterColl->setPosition(Vec2((winSize.width / 8) * 7, winSize.height / 2));
	monsterColl->setZOrder(-1);
	monsterColl->setOpacity(0);
	this->addChild(monsterColl);

	auto monCollSize = monsterColl->getContentSize();		 
	monster->setPosition(Vec2(monCollSize.width/2, monCollSize.height/4 * 3));
	monsterColl->addChild(monster);

	monster->setUI(Vec2((winSize.width / 8) * 7 + 10, (winSize.height / 8) * 7 - 15), this);
}

void HelloWorld::shooting() {
	//bullet
	auto batch = SpriteBatchNode::create("Skill/4080arrow.png", 10);
	auto texture = batch->getTexture();

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);

	for (int i = 0; i < 4; i++) {
		int colum = i % 4; // 0,1,2,3,4
		int row = i / 4; //0,1,2
						 // x,y 좌표 x로 얼마만큼  y로 얼마만큼
		animation->addSpriteFrameWithTexture(texture, Rect(colum * 80, row * 40, 80, 40));
	}

	arrow = Sprite::create("Skill/4080arrow.png", Rect(0, 0, 80, 40));
	arrow->setPosition(player2Coll->getPosition());
	this->addChild(arrow);

	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);

	auto spa = Spawn::create(MoveBy::create(2.5f, Vec2(1000, 0)), nullptr);

	arrow->runAction(rep);
	arrow->runAction(spa);
	
	log("bbb");
	b_bullet = true;

	_arrow.pushBack(arrow);
}