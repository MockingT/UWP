#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace std;
class GameScene : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void moveAni();

	void fireAni();

	void addTouchListener();

	bool onTouchBegan(Touch * touch, Event * event);

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

private:
	Sprite * player0;
	Sprite * player1;
	Sprite * player3;
	cocos2d::Vector<SpriteFrame*> move;
	cocos2d::Vector<SpriteFrame*> fire;
	cocos2d::Vector<SpriteFrame*> move1;
};

#endif // __GAME_SCENE_H__
