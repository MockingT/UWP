#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene() {
	return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename) {
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init() {
	//////////////////////////////
	// 1. super init first
	if (!Scene::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto map = Sprite::create("map2.png");
	map->setScale(Director::getInstance()->getContentScaleFactor());
	map->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(map, 0);

	player0 = Sprite::create("Fire 0.png");
	player0->setPosition(visibleSize.width / 2 - 8, player0->getContentSize().height + 10);
	this->addChild(player0, 1);

	player1 = Sprite::create("Image 0.png");
	player1->setPosition(visibleSize.width / 2, player1->getContentSize().height);
	this->addChild(player1, 1);

	auto texture = Director::getInstance()->getTextureCache()->addImage("left.png");
	auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 60, 83)));
	player3 = Sprite::createWithSpriteFrame(frame0);
	player3->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(player3, 1);

	moveAni();
	fireAni();
	addTouchListener();

	return true;
}

void GameScene::moveAni() {
	move.reserve(10);
	char file[15];
	for (int i = 0; i < 10; i++) {
		sprintf(file, "Image %d.png",(i + 1) % 10);
		auto frame = SpriteFrame::create(file, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 33, 32)));
		move.pushBack(frame);
	}
	move1.reserve(5);
	for (int i = 0; i < 5; i++) {
		auto texture = Director::getInstance()->getTextureCache()->addImage("left.png");
		SpriteFrame* frame;
		if (i != 4)
			frame = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(66 * (i + 1), 0, 60, 83)));
		else
			frame = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 60, 83)));
		move1.pushBack(frame);
	}
}

void GameScene::fireAni() {
	fire.reserve(5);
	char file[15];
	for (int i = 0; i < 5; i++) {
		sprintf(file, "Fire %d.png", i);
		auto frame = SpriteFrame::create(file, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 80, 58)));
		fire.pushBack(frame);
	}
}

void GameScene::addTouchListener() {
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}


bool GameScene::onTouchBegan(Touch *touch, Event *event) {
	player0->runAction(Animate::create(Animation::createWithSpriteFrames(fire, 0.05f, 1)));
	player1->runAction(Animate::create(Animation::createWithSpriteFrames(move, 0.05f, 1)));
	player3->runAction(Animate::create(Animation::createWithSpriteFrames(move1, 0.05f, 1)));
	return true;
}
