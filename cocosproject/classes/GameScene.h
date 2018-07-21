#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace std;
class GameScene : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	void setPhysicsWorld(PhysicsWorld * world);

	virtual bool init();

	void moveAni();

	void fireAni();

	void fireBullet(int p);

	void addTouchListener();

	bool onTouchBegan(Touch * touch, Event * event);

	void addKeyboardListener();
	void onKeyPressed(EventKeyboard::KeyCode code, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode code, Event* event);

	void hitByBullet(EventCustom * event);
	void update(float);
	void addCustomListener();

	void gameOver();

	void replayCallback(Ref * pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

private:
	Sprite * player1;
	Sprite * player2;
	Sprite * playerFeet;
	list<Vec2> doorposition;
	cocos2d::Vector<SpriteFrame*> move;
	cocos2d::Vector<SpriteFrame*> fire;
	cocos2d::Vector<SpriteFrame*> move1;
	Size visibleSize;
	Vec2 origin;
	bool headingLeft1;
	bool headingLeft2;

	char movekey1;
	char movekey2;

	PhysicsWorld* m_world;

	cocos2d::ProgressTimer* pT1, *pT2;
	int hp1, hp2;
	list<Sprite*> bullets1, bullets2;
};

#endif // __GAME_SCENE_H__
/*#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace std;
class GameScene : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	void setPhysicsWorld(PhysicsWorld * world);

	virtual bool init();

	void moveAni();

	void fireAni();

	void fireBullet(int p);

	void addTouchListener();

	bool onTouchBegan(Touch * touch, Event * event);

	void addKeyboardListener();
	void onKeyPressed(EventKeyboard::KeyCode code, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode code, Event* event);

	void hitByBullet();

	
	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

private:
	cocos2d::TMXTiledMap* tmx;
	cocos2d::TMXObjectGroup* brick;
	Sprite * player1;
	Sprite * player2;
	Sprite * playerFeet;
	cocos2d::Vector<SpriteFrame*> move;
	cocos2d::Vector<SpriteFrame*> fire;
	cocos2d::Vector<SpriteFrame*> move1;
	Size visibleSize;
	Vec2 origin;
	bool headingLeft1;
	bool headingLeft2;

	char movekey1;
	char movekey2;

	PhysicsWorld* m_world;

	cocos2d::ProgressTimer* pT1, *pT2;
	int hp1, hp2;

};

#endif // __GAME_SCENE_H__
*/
