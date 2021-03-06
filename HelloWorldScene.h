﻿#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__


#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include <GLES-Render.h>
#include "Button.h"
#include "Command.h"
#include "Player.h"
#include "Monster.h"
#include "Effect.h"
#include "extensions/cocos-ext.h"

#define PTM_RATIO 32

//레이어 z_oder
#define BGLAYER -10
#define UILAYER 10

//한방 데미지 25
#define MONSTER_SKILL2 31

//화살 데미지 5
#define MONSTER_SKILL3 7

using namespace cocos2d;
using namespace cocos2d::extension;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(HelloWorld);
	~HelloWorld();

	cocos2d::Size winSize;
	cocos2d::Texture2D* texture;
	


	//menu
	cocos2d::Menu* menu;


	//Box2d
	void tick(float dt);
	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
	bool createBox2dWorld(bool debug);

	b2Body* addNewSprite(Vec2 point, Size size, b2BodyType bodytype,
						 Sprite* spriteName, int type);
	b2World* _world;
	GLESDebugDraw* m_debugDraw;

	bool bDrag;
	b2Body* dragBody;
	b2MouseJoint* mouseJoint;
	b2Body *gbody;
	
	//command input
	Command* command;
	cocos2d::Layer* UILayer;

	//Player
	Player* player1;
	b2Body* player1Body;
	cocos2d::Sprite* player1Coll;

	Player* player2;
	b2Body* player2Body;
	cocos2d::Sprite* player2Coll;

	Player* player3;
	cocos2d::Sprite* player3Coll;
	b2Body* player3Body;

	//Monster
	Monster* monster;
	cocos2d::Sprite* monsterColl;
	b2Body* monsterBody;

	//플레이어2(아처) 슈팅함수
	void shooting();

	//animation SpriteFrameCahe createWithTexture
	cocos2d::SpriteFrameCache *cache;
	void setCharectorAnimations();

	//background
	cocos2d::Sprite* bg;
	cocos2d::Layer* bgLayer;
	//cocos2d::Layer* uiLayer;
	cocos2d::Layer* EffectLayer;

	//player skill
	void heal();
	bool heal_skill;

	//Effect
	Effect* effect;
	cocos2d::SpriteBatchNode* effect_batch;

	//flag
	cocos2d::Action* act_flag;
	bool flag;
	void setFlag();

	//monster skill
	cocos2d::Action* act_flag2;
	bool flag2;
	void setFlag2();

	cocos2d::Action* act_flag3;
	bool flag3;
	void setFlag3();

	cocos2d::Action* act_flag4;
	bool flag4;
	void setFlag4();

	cocos2d::Action* act_flag5;
	bool flag5;
	void setFlag5();

	//monster skill
	void MonsterSkill();
	void MonsterSkill2();
	void MonsterSkill3(float dt);

	//player swordman skill bool
	bool b_block;
	void offBlock();
	cocos2d::Sprite* block;


	//player skill 
	//플레이어 클래스 스택을 3스택이 쌓이면 플레이어 스킬이 발동
	void swordSkill();
	void healerSkill();
	void archerSkill();

	//씬 이동
	bool scene_move;
	void gameOver(Ref* pSender);
	void moveScene();

	//time score
	cocos2d::LabelAtlas* score;
	int time_score;
	void uptateTime(float dt);

	//리더보드
	void doSendTime();
	std::string txtNum;

protected:
		void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
		cocos2d::CustomCommand _customCmd;

private:
	std::vector<cocos2d::Sprite*> _arrow;
	std::vector<cocos2d::Sprite*> _skill;
	Vector<cocos2d::Sprite*> _monster_arrow;
	Vector<cocos2d::Sprite*> remove_arrow;
};

#endif // __HELLOWORLD_SCENE_H__
