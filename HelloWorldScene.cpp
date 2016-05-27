#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "ScoreScene.h"

#define MAINMUSIC "Sound/music_collection.ogg"
#define HEALER_SKILL "Sound/sfx_neutral_spelljammer_attack_swing.ogg"
#define SWORDMAN_SKILL "Sound/sfx_neutral_xho_attack_impact.ogg"
#define ARCHER_SKILL "Sound/sfx_spell_phoenixfire.ogg"

USING_NS_CC;
using namespace CocosDenshion;

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
	
	bgLayer = Layer::create();
	bgLayer->setZOrder(BGLAYER);
	addChild(bgLayer);

	UILayer = Layer::create();
	UILayer->setZOrder(UILAYER);
	addChild(UILayer);

	//오디오
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MAINMUSIC);
	SimpleAudioEngine::getInstance()->playBackgroundMusic(MAINMUSIC, true);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0f);

	//스킬들 프레임당 몇번씩 실행할지 결정하는 플래그들
	flag = true;
	flag2 = true;
	flag3 = true;
	flag4 = true;
	flag5 = true;

	scene_move = true;

	//힐스킬을 한번만 발동하기 위해서 힐러가 idle상태가 되면 다시 true로 바뀐다
	heal_skill = true;

	//블록이 있을떄만 충돌체크 하기위해서 
	b_block = false;

	winSize = Director::getInstance()->getWinSize();

	//effect  this부분에 Backgound 레이어 만들어서 넣을것
	effect = new Effect();
	effect->retain();
	//effect->getTypeEffect(1, Vec2(winSize.width / 2, winSize.height / 2), this);
	//effect->getTypeEffect(2, Vec2(winSize.width / 2 + 20, winSize.height / 2), this);
	//effect->getTypeEffect(3, Vec2(winSize.width / 2 + 40, winSize.height / 2), this);
	//effect->getTypeEffect(4, Vec2(winSize.width / 2 + 60, winSize.height / 2), this);
	//effect->getTypeEffect(5, Vec2(winSize.width / 2 + 80, winSize.height / 2), this);
	//effect->getTypeEffect(6, Vec2(winSize.width / 2 + 100, winSize.height / 2), this);
	//effect->getTypeEffect(7, Vec2(winSize.width / 2 + 120, winSize.height / 2), this);
	//effect->getTypeEffect(8, Vec2(winSize.width / 2 + 140, winSize.height / 2), this);
	//effect->getTypeEffect(9, Vec2(winSize.width / 2 + 160, winSize.height / 2), this);
	//effect->getTypeEffect(10, Vec2(winSize.width / 2 + 180, winSize.height / 2), this);
	//effect->getTypeEffect(11, Vec2(winSize.width / 2 + 200, winSize.height / 2), this);

	//command 
	command = new Command();
	command->setPosition(Vec2(winSize.width / 2, (winSize.height / 8)));

	//btn
	command->setBtnUI(Vec2(0, (winSize.height) - 100), UILayer);
	UILayer->addChild(command);
	
	setCharectorAnimations();
	
	if (createBox2dWorld(false)) {
		this->schedule(schedule_selector(HelloWorld::tick));
		this->schedule(schedule_selector(HelloWorld::uptateTime), 0.1f);
	}
	
	///////////////
	//backgrond ///
	///////////////
	
	auto batch = SpriteBatchNode::create("background/16.png", 10);
	auto texture = batch->getTexture();

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);

	for (int i = 0; i < 18; i++) {
		int colum = i % 5; // 0,1,2,3,4
		int row = i / 4; //0,1,2
						 // x,y 좌표 x로 얼마만큼  y로 얼마만큼
		animation->addSpriteFrameWithTexture(texture, Rect(colum * 200, row * 100, 200, 100));
	}

	auto bg = Sprite::create("background/16.png", Rect(0, 0, 200, 100));

	bg->setScale(3.8f);
	bg->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	bg->setZOrder(-3);
	bgLayer->addChild(bg);

	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	bg->runAction(rep);

	auto castle = Sprite::create("background/castle.png");
	castle->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	castle->setZOrder(-3);
	bgLayer->addChild(castle);

	auto bottom = Sprite::create("background/bottom11.png");
	bottom->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	bottom->setZOrder(-3);
	bgLayer->addChild(bottom);

	auto sky_rock = Sprite::create("background/sky_rock.png");
	sky_rock->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	sky_rock->setZOrder(-3);
	bgLayer->addChild(sky_rock);
	
	//sky_rock move act
	auto act_rock3 = MoveBy::create(4.0f, Vec2(0, 10));
	auto seq5 = Sequence::create(act_rock3, act_rock3->reverse(), nullptr);
	auto rep5 = RepeatForever::create(seq5);
	sky_rock->runAction(rep5);


	auto sky_rock2 = Sprite::create("background/sky_rock2.png");
	sky_rock2->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	sky_rock2->setZOrder(-3);
	bgLayer->addChild(sky_rock2);

	//sky_rock move act
	auto act_rock4 = MoveBy::create(3.0f, Vec2(0, 30));
	auto seq6 = Sequence::create(act_rock4, act_rock4->reverse(), nullptr);
	auto rep6 = RepeatForever::create(seq6);
	sky_rock2->runAction(rep6);


	//점수
	time_score = 0.0f;
	score = LabelAtlas::create("0", "number/numbers.png", 60, 86, '.');
	score->setPosition(Vec2(winSize.width / 2 - 50, winSize.height / 2 + 100));
	score->setScale(0.5f);
	score->setColor(Color3B::GRAY);
	this->addChild(score);
	
	////////////////////
	//sprite add body //
	////////////////////

	player1Body = addNewSprite(player1Coll->getPosition(), Size(45, 50), b2_dynamicBody, player1Coll, 0);
	player2Body = addNewSprite(player2Coll->getPosition(), Size(45, 50), b2_dynamicBody, player2Coll, 0);
	player3Body = addNewSprite(player3Coll->getPosition(), Size(45, 50), b2_dynamicBody, player3Coll, 0);

	this->addNewSprite(monsterColl->getPosition(), monsterColl->getContentSize(), b2_staticBody, monsterColl, 1);

	////////////////////////////////////////////////////////////////////////////////////////////
	//flags method  playing action(히트 함수를  시간의 따라 연속으로 불릴수있는 갯수정하기)////
	///////////////////////////////////////////////////////////////////////////////////////////

	auto delay = DelayTime::create(0.4f);
	auto seq = Sequence::create(delay, CallFunc::create(CC_CALLBACK_0(HelloWorld::setFlag, this)), nullptr);
	act_flag = seq;
	act_flag->retain();

	auto delay2 = DelayTime::create(1.5f);
	auto seq2 = Sequence::create(delay2, CallFunc::create(CC_CALLBACK_0(HelloWorld::setFlag2, this)), nullptr);
	act_flag2 = seq2;
	act_flag2->retain();

	auto delay3 = DelayTime::create(2.0f);
	auto seq3 = Sequence::create(delay3, CallFunc::create(CC_CALLBACK_0(HelloWorld::setFlag3, this)), nullptr);
	act_flag3 = seq3;
	act_flag3->retain();

	auto delay4 = DelayTime::create(3.0f);
	auto seq4 = Sequence::create(delay4, CallFunc::create(CC_CALLBACK_0(HelloWorld::setFlag4, this)), nullptr);
	act_flag4 = seq4;
	act_flag4->retain();

	auto delay5 = DelayTime::create(3.0f);
	auto delay5_sep = Sequence::create(delay5, CallFunc::create(CC_CALLBACK_0(HelloWorld::setFlag5, this)), nullptr);
	act_flag5= delay5_sep;
	act_flag5->retain();

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

	this->unschedule(schedule_selector(HelloWorld::tick));

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
	for (int i = 0; i <_arrow.size(); i++) {
		auto arrows = (Sprite*)_arrow[i];
		if (arrows->boundingBox().intersectsRect(monsterColl->boundingBox())){
			effect->getTypeEffect(9, Vec2(arrows->getPosition()), this);
			removeChild(arrows, false);
			_arrow.erase(_arrow.begin() + i);
			monster->Hit(10);
		}
	}

	//몬스터 화살 체크
	for (int i = 0; i < _monster_arrow.size(); i++) {
		auto arrows = (Sprite*)_monster_arrow.at(i);
		//소드맨 스킬이 있을떄 충돌체크
		if (b_block) {
			if (arrows->boundingBox().intersectsRect(block->boundingBox())){
				//effect->getTypeEffect(9, Vec2(arrows->getPosition()), this);
				removeChild(arrows, false);
				_monster_arrow.eraseObject(arrows);
			}
		}

		//플레이어 수만큼 체크
		for (int j = 1; j < 4; j++) {
			if (j == 1) {
				if (player1->ps != player1->Die) {
					if (arrows->boundingBox().intersectsRect(player1Coll->boundingBox())) {

						//effect->getTypeEffect(9, Vec2(arrows->getPosition()), this);
						removeChild(arrows, false);
						_monster_arrow.eraseObject(arrows);

						if (player1->ps != player1->Sheild) {
							player1->Hit(MONSTER_SKILL3);
						}
					}
				}
			}
			else if (j == 2) {
				if (player2->ps != player2->Die) {
					if (arrows->boundingBox().intersectsRect(player2Coll->boundingBox())) {

						//effect->getTypeEffect(9, Vec2(arrows->getPosition()), this);
						removeChild(arrows, false);
						_monster_arrow.eraseObject(arrows);

						if (player2->ps != player3->Sheild) {
							player2->Hit(MONSTER_SKILL3);
						}
					}
				}
			}
			else if (j == 3) {
				if (player3->ps != player3->Die) {
					if (arrows->boundingBox().intersectsRect(player3Coll->boundingBox())) {

						//effect->getTypeEffect(9, Vec2(arrows->getPosition()), this);
						removeChild(arrows, false);
						_monster_arrow.eraseObject(arrows);

						if (player3->ps != player3->Sheild) {
							player3->Hit(MONSTER_SKILL3);
						}
					}
				}
			}
		}
	}

	//몬스터 관통 스킬 체크
	for (int i = 0; i < _skill.size(); i++) {
		auto skill = (Sprite*)_skill[i];
		//플레이어 수만큼 체크
		if (flag5) {
			for (int j = 1; j < 4; j++) {
				if (j == 1) {
					if (player1->ps != player1->Die) {
						if (skill->boundingBox().intersectsRect(player1Coll->boundingBox())) {
							//effect->getTypeEffect(9, Vec2(arrows->getPosition()), this);
							//_skill.erase(_skill.begin() + i);
							player1->Hit(MONSTER_SKILL2);
						}
					}
				}
				else if (j == 2) {
					if (player2->ps != player2->Die) {
						if (skill->boundingBox().intersectsRect(player2Coll->boundingBox())) {
							//effect->getTypeEffect(9, Vec2(arrows->getPosition()), this);
							//_skill.erase(_skill.begin() + i);
							player2->Hit(MONSTER_SKILL2);
						}
					}
				}
				else if (j == 3) {
					if (player3->ps != player3->Die) {
						if (skill->boundingBox().intersectsRect(player3Coll->boundingBox())) {
							//effect->getTypeEffect(9, Vec2(arrows->getPosition()), this);
							//_skill.erase(_skill.begin() + i);
							player3->Hit(MONSTER_SKILL2);
						}
					}
				}	
			}
			flag5 = false;
			monster->runAction(act_flag5);
			_skill.erase(_skill.begin() + i);
		}
	}

	//player1, 2, ,3 이 다완성 되면 for문으로 묶어 3개를 다돌린다
	//플레이어 이동제어
	for (int i = 1; i < 4; i++) {
		if (i == 1) {
			if (player1->ps == player1->Run) {
				double dis;
				dis = monsterColl->getPosition().x - player1Coll->getPosition().x;
				if (dis > 340) {
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
				if (heal_skill) {
					auto seq = Sequence::create(DelayTime::create(0.7),
						CallFunc::create(CC_CALLBACK_0(HelloWorld::heal, this)), nullptr);
					this->runAction(seq);
					heal_skill = false;
				}
			}
			else if (player1->ps == player1->Idle) {
				heal_skill = true;;
			}
		}
		else if (i == 2) {
			if (player2->ps == player2->Run) {

				double dis;
				dis = monsterColl->getPosition().x - player2Coll->getPosition().x;

				if (dis > 270) {
					player2Body->ApplyForceToCenter(b2Vec2(35, 0), true);
				}
				else {
					//활을 쏠때 뒤로밀려난다
					player2Body->ApplyForceToCenter(b2Vec2(-550, 0), true);
					player2->atkAction();
					
					//슈팅부분 0.7;
					auto seq = Sequence::create(DelayTime::create(0.7), 
												CallFunc::create(CC_CALLBACK_0(HelloWorld::shooting, this)), 
												nullptr);
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
						monster->Hit(10);
						flag = false;
						this->runAction(act_flag);
					}
					
				}
			}
		}
	}
	
	//monster skill
	if (monster->ms != monster->Die) {
		if (monster->ms == monster->Atk) {
			if (flag3) {
				flag3 = false;
				monster->runAction(act_flag3);
				MonsterSkill();
			}
		}
		else if (monster->ms == monster->Cast) {
			if (flag2) {
				if (player1->ps != player1->Sheild) {
					player1Body->ApplyForceToCenter(b2Vec2(1100, 0), true);
				}
				if (player2->ps != player2->Sheild) {
					player2Body->ApplyForceToCenter(b2Vec2(1100, 0), true);
				}
				if (player3->ps != player3->Sheild) {
					player3Body->ApplyForceToCenter(b2Vec2(1100, 0), true);
				}
				flag2 = false;
				monster->runAction(act_flag2);
			}
		}
		else if (monster->ms == monster->CastLoop) {

			if (flag4) {
				this->schedule(schedule_selector(HelloWorld::MonsterSkill3), 0.1);
				flag4 = false;
				monster->runAction(act_flag4);
			}

		}
		else if (monster->ms == monster->Idle) {

			this->unschedule(schedule_selector(HelloWorld::MonsterSkill3));

		}
	}
	else {
		this->unschedule(schedule_selector(HelloWorld::MonsterSkill3));
	}


	//플레이어 스킬 가능 부분 공, 방 3스택이 쌓이면 스킬 실행 아처만 공스택 3 나머지 방스택 3
	if (player1->shield_stack == 3) {

		player1->shield_stack = 0;
		healerSkill();
		player1->setShieldLabel();
	}
	if (player2->atk_stack == 3) {

		player2->atk_stack = 0;
		archerSkill();
		player2->setAtkLabel();
	}
	if (player3->shield_stack == 3) {

		player3->shield_stack = 0;
		swordSkill();
		player3->setShieldLabel();
	}

	//플레이어 3명 죽음 체크
	if (player1->ps == player1->Die && player2->ps == player2->Die && player3->ps == player3->Die) {
		//log("세명 다 죽었습니다");
		//Director::getInstance()->pause();
		//removeChild(command);
		this->unschedule(schedule_selector(HelloWorld::uptateTime));
		command->setVisible(false);
	}
	if (monster->ms == monster->Die) {
		//log("몬스터 가 죽었습니다");
		
		if (scene_move) {
			this->unschedule(schedule_selector(HelloWorld::uptateTime));
			command->setVisible(false);

			auto pScene = ScoreScene::createScene();
			Director::getInstance()->pushScene(TransitionCrossFade::create(0.5, pScene));
			
			scene_move = false;
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

//플레이어, 보스 애니메이션 구현
void HelloWorld::setCharectorAnimations() {
	/////////////////////
	//  Player       ///
	////////////////////
	

	//player1 애니메이션 정의
	player1 = new Player(100, 100, 30, 1);
	

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
	this->addChild(player1Coll);

	
	auto p1CollSize = player1Coll->getContentSize();
	player1->setPosition(Vec2(p1CollSize.width / 2, p1CollSize.height / 2));
	player1Coll->addChild(player1);
	player1Coll->setOpacity(0);

	//////////////////////////
	//player2   /////////////
	/////////////////////////

	//player2 애니메이션 정의
	player2 = new Player(100, 100, 30, 2);

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
	player2Coll->setOpacity(0);

	//////////////////////
	//player3  ///////////
	/////////////////////

	//player3 애니메이션 정의
	player3 = new Player(200, 200, 30, 3);

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
	this->addChild(player3Coll);


	auto p3CollSize = player3Coll->getContentSize();
	player3->setPosition(Vec2(p3CollSize.width / 2, p3CollSize.height / 2));
	player3Coll->addChild(player3);
	player3Coll->setOpacity(0);

	////////////
	//command///
	////////////

	command->setPlayerAction(player1, player2, player3);


	//////////////////////////////
	//       monster            //
	/////////////////////////////

	monster = new Monster(100);

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
	monsterColl->setPosition(Vec2((winSize.width / 8) * 7, winSize.height / 2 - 40));
	monsterColl->setZOrder(-1);
	monsterColl->setOpacity(0);
	this->addChild(monsterColl);

	auto monCollSize = monsterColl->getContentSize();		 
	monster->setPosition(Vec2(monCollSize.width/2, monCollSize.height/4 * 3));
	monsterColl->addChild(monster);

	monster->setUI(Vec2((winSize.width / 8) * 7 + 10, (winSize.height / 8) * 7 - 15), this);
}

//아처 화살
void HelloWorld::shooting() {
	auto batch = SpriteBatchNode::create("Skill/4080arrow.png", 10);
	auto texture = batch->getTexture();

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.05f);

	for (int i = 0; i < 4; i++) {
		int colum = i % 4; // 0,1,2,3,4
		int row = i / 4; //0,1,2
						 // x,y 좌표 x로 얼마만큼  y로 얼마만큼
		animation->addSpriteFrameWithTexture(texture, Rect(colum * 80, row * 40, 80, 40));
	}

	auto arrow = Sprite::create("Skill/4080arrow.png", Rect(0, 0, 80, 40));
	arrow->setPosition(player2Coll->getPosition());
	this->addChild(arrow);

	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);

	auto spa = Spawn::create(MoveBy::create(2.5f, Vec2(1000, 0)), nullptr);

	arrow->runAction(rep);
	arrow->runAction(spa);
	
	_arrow.push_back(arrow);
}

//검사 떄릴떄 프레임수 정하기
void HelloWorld::setFlag() {
	if (!flag) {
		flag = true;
	}
}

//몬스터 스킬1
void HelloWorld::setFlag2() {
	if (!flag2) {
		flag2 = true;
	}
	MonsterSkill2();
}

//몬스터 스킬2
void HelloWorld::setFlag3() {
	if (!flag3) {
		flag3 = true;
	}
}

//몬스터 스킬 화살 스케쥴 한번만 실행시키기 위해서
void HelloWorld::setFlag4() {
	if (!flag4) {
		flag4 = true;
	}
}

//몬스터 관통 스킬 발동수
void HelloWorld::setFlag5() {
	if (!flag5) {
		flag5 = true;
	}
}

void HelloWorld::MonsterSkill() {
	auto batch = SpriteBatchNode::create("Skill/monster_skill.png", 10);
	auto texture = batch->getTexture();

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);

	for (int i = 0; i < 16; i++) {
		int colum = i % 4; // 0,1,2,3,4
		int row = i / 4; //0,1,2
						 // x,y 좌표 x로 얼마만큼  y로 얼마만큼
		animation->addSpriteFrameWithTexture(texture, Rect(colum * 100, row * 100, 100, 100));
	}

	auto skill = Sprite::create("Skill/monster_skill2.png", Rect(0, 0, 100, 100));
	skill->setPosition(Vec2(monsterColl->getPositionX() - 100, monsterColl->getPositionY()));
	skill->setScale(1.5f);
	this->addChild(skill);

	auto removeAction = CCCallFunc::create(CC_CALLBACK_0(CCNode::removeChild, this, skill, false));

	auto animate = Animate::create(animation);
	//auto rep = RepeatForever::create(animate);

	auto seq = Sequence::create(animate, removeAction, nullptr);
	//auto spa = Spawn::create(MoveBy::create(2.5f, Vec2(1000, 0)), nullptr);

	skill->runAction(seq);
	//skill->runAction(spa);

	_skill.push_back(skill);
}

void HelloWorld::MonsterSkill2() {
	auto batch = SpriteBatchNode::create("Skill/monster_skill2.png", 10);
	auto texture = batch->getTexture();

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);

	for (int i = 0; i < 26; i++) {
		int colum = i % 6; // 0,1,2,3,4
		int row = i / 6; //0,1,2
						 // x,y 좌표 x로 얼마만큼  y로 얼마만큼
		animation->addSpriteFrameWithTexture(texture, Rect(colum * 160, row * 450, 160, 450));
	}

	auto skill = Sprite::create("Skill/monster_skill2.png", Rect(0, 0, 160, 450));
	skill->setPosition(Vec2(monsterColl->getPositionX() - 100, monsterColl->getPositionY() + 150));
	this->addChild(skill);

	auto removeAction = CCCallFunc::create(CC_CALLBACK_0(CCNode::removeChild, this, skill, false));

	auto animate = Animate::create(animation);
	//auto rep = RepeatForever::create(animate);

	auto seq = Sequence::create(animate, removeAction, nullptr);
	//auto spa = Spawn::create(MoveBy::create(2.5f, Vec2(1000, 0)), nullptr);

	skill->runAction(seq);
	//skill->runAction(spa);

	_skill.push_back(skill);
}

void HelloWorld::MonsterSkill3(float dt) {

	auto batch = SpriteBatchNode::create("Skill/monster_skill3.png", 10);
	auto texture = batch->getTexture();

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);

	for (int i = 0; i < 4; i++) {
		int colum = i % 2; // 0,1,2,3,4
		int row = i / 2; //0,1,2
						 // x,y 좌표 x로 얼마만큼  y로 얼마만큼
		animation->addSpriteFrameWithTexture(texture, Rect(colum * 110, row * 39, 110, 39));
	}

	auto skill = Sprite::create("Skill/monster_skill2.png", Rect(0, 0, 110, 39));

	int posY = rand() % 70 + -50;

	skill->setPosition(Vec2(monsterColl->getPositionX() + 200, monsterColl->getPositionY() + posY));
	skill->setAnchorPoint(Vec2(0, 0.5));
	skill->setFlippedX(true);
	skill->setScale(1.5f);

	auto act = MoveBy::create(2.0f, Vec2(-1000, 0));
	this->addChild(skill);
	
	auto removeAction = CCCallFunc::create(CC_CALLBACK_0(CCNode::removeChild, this, skill, false));
	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	auto seq = Sequence::create(act, removeAction, nullptr);

	skill->runAction(rep);
	skill->runAction(seq);

	_monster_arrow.pushBack(skill);
}

void HelloWorld::heal() {
	//플레이어 체력 퍼센트로 힐 스킬를 씀
	Player* heal_target[3];
	Player* heal;

	heal_target[0] = player1;
	heal_target[1] = player2;
	heal_target[2] = player3;

	double player_hpPer = 2.0f;
	//제일 적은 체력 퍼센트 플레이어를 힐 타켓으로 잡음
	for (int i = 0; i < 3; i++) {
		if (heal_target[i]->ps != heal_target[i]->Die) {
			if (player_hpPer > heal_target[i]->hpPer) {
				player_hpPer = heal_target[i]->hpPer;
				heal = heal_target[i];
			}
		}
	}

	heal->Heal();
}

void HelloWorld::swordSkill() {
	auto sprite = Sprite::create("Skill/80_sword_skill.png");
	auto texture = sprite->getTexture();
	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);

	for (int i = 0; i < 11; i++) {
		int colum = i % 4; // 0,1,2,3,4
		int row = i / 4; //0,1,2
						 // x,y 좌표 x로 얼마만큼  y로 얼마만큼
		animation->addSpriteFrameWithTexture(texture, Rect(colum * 80, row * 80, 80, 80));
	}

	block = Sprite::create("Skill/80_sword_skill.png", Rect(0, 0, 80, 80));
	block->setPosition(player3Coll->getPosition());
	this->addChild(block);

	//액션 정의
	auto delay = DelayTime::create(2.0f);
	auto removeAction = CCCallFunc::create(CC_CALLBACK_0(CCNode::removeChild, this, block, true));
	auto off = CCCallFunc::create(CC_CALLBACK_0(HelloWorld::offBlock, this));
	auto seq = Sequence::create(delay, off, removeAction, nullptr);
	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	block->runAction(rep);
	block->runAction(seq);
	b_block = true;
	log("소드맨스킬");
	SimpleAudioEngine::getInstance()->playEffect(SWORDMAN_SKILL);
}

void HelloWorld::healerSkill() {

	auto sprite = Sprite::create("Skill/244_heal_skill.png");
	auto texture = sprite->getTexture();
	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);

	for (int i = 0; i < 25; i++) {
		int colum = i % 5; // 0,1,2,3,4
		int row = i / 5; //0,1,2
						 // x,y 좌표 x로 얼마만큼  y로 얼마만큼
		animation->addSpriteFrameWithTexture(texture, Rect(colum * 244, row * 244, 244, 244));
	}

	auto effect = Sprite::create("Skill/244_heal_skill.png", Rect(0, 0, 244, 244));
	effect->setPosition(Vec2(player1Coll->getPositionX(), player1Coll->getPositionY() + 120));
	effect->setScale(1.5f);
	this->addChild(effect);

	//이펙트 액션
	auto removeAction = CCCallFunc::create(CC_CALLBACK_0(CCNode::removeChild, this, effect, true));
	auto animate = Animate::create(animation);
	auto seq = Sequence::create(animate, removeAction, nullptr);
	effect->runAction(seq);

	player1->Heal();
	player2->Heal();
	player3->Heal();
	SimpleAudioEngine::getInstance()->playEffect(HEALER_SKILL);
	log("힐러 스킬");
}

void HelloWorld::archerSkill() {
	auto sprite = Sprite::create("Skill/150_archer_skill.png");
	auto texture = sprite->getTexture();
	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);

	for (int i = 0; i < 36; i++) {
		int colum = i % 5; // 0,1,2,3,4
		int row = i / 5; //0,1,2
						 // x,y 좌표 x로 얼마만큼  y로 얼마만큼
		animation->addSpriteFrameWithTexture(texture, Rect(colum * 150, row * 150, 150, 150));
	}

	auto effect = Sprite::create("Skill/244_heal_skill.png", Rect(0, 0, 150, 150));
	effect->setPosition(winSize.width/2 ,winSize.height/2);
	effect->setScale(2.0f);
	this->addChild(effect);

	//이펙트 액션
	auto removeAction = CCCallFunc::create(CC_CALLBACK_0(CCNode::removeChild, this, effect, true));
	auto animate = Animate::create(animation);
	auto seq = Sequence::create(animate, removeAction, nullptr);
	effect->runAction(seq);
	log("아처맨 스킬");

	monster->Hit(20);
	SimpleAudioEngine::getInstance()->playEffect(ARCHER_SKILL);
}

//소드맨 블록 스킬 존재여부
void HelloWorld::offBlock() {
	b_block = false;
}

//시간 업데이트
void HelloWorld::uptateTime(float dt) {
	time_score = time_score + 0.1f;

	char num[100];
	sprintf(num, "%0.1f", time_score);

	score->setString(num);
}