#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__


#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include <GLES-Render.h>
#include "Button.h"
#include "Command.h"
#include "Player.h"
#include "Monster.h"

#define PTM_RATIO 32

using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(HelloWorld);
	~HelloWorld();

	cocos2d::Size winSize;
	cocos2d::Texture2D* texture;
	
	virtual void onEnter();
	virtual void onExit();

	//touch
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

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

	//button
	Button* atkBtn;
	Button* shelidBtn;
	
	//command input
	Command* command;
	void onAction();

	//Player
	Player* player1;
	b2Body* playerBody;
	Player* player2;
	Player* player3;

	//Monster
	Monster* monster;
	
	//animation SpriteFrameCahe createWithTexture
	cocos2d::SpriteFrameCache *cache;
	void setCharectorAnimations();

	//background
	cocos2d::Sprite* bg;
	void Test(Ref* pSender);
	void Test2(Ref* pSender);
	protected:
		void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
		cocos2d::CustomCommand _customCmd;
};

#endif // __HELLOWORLD_SCENE_H__
