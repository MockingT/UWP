﻿#include "GameScene.h"

USING_NS_CC;

void GameScene::setPhysicsWorld(PhysicsWorld* world) { m_world = world; }

Scene* GameScene::createScene() {
	//return GameScene::create();
	auto scene = Scene::createWithPhysics();

	scene->getPhysicsWorld()->setAutoStep(true);

	// Debug ģʽ
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, -300.0f));
	auto layer = GameScene::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	//layer->setJoint();
	scene->addChild(layer);
	return scene;
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

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	auto map = Sprite::create("map2.png");
	map->setScale(Director::getInstance()->getContentScaleFactor());
	map->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(map, 0);

	TTFConfig ttfConfig;
	ttfConfig.fontFilePath = "fonts/arial.ttf";
	ttfConfig.fontSize = 24;

	//the base
	auto base = Sprite::create("bar.png");
	base->setScaleX(3);
	base->setPosition(Vec2(visibleSize.width / 2, 20));

	auto baseBody = PhysicsBody::createBox(base->getContentSize(), PhysicsMaterial(100.0f, 0.5f, 0.0f));
	baseBody->setCategoryBitmask(0xFFFFFFFF);
	baseBody->setCollisionBitmask(0xFFFFFFFF);
	baseBody->setContactTestBitmask(0xFFFFFFFF);
	baseBody->setGravityEnable(false);
	baseBody->setDynamic(false);
	base->setPhysicsBody(baseBody);

	this->addChild(base, 1);

	auto base1 = Sprite::create("bar.png");
	base1->setScaleY(0.5);
	base1->setScaleX(0.7);
	base1->setPosition(Vec2(visibleSize.width / 2 - 200, 150));

	auto baseBody1 = PhysicsBody::createBox(base1->getContentSize(), PhysicsMaterial(100.0f, 0.5f, 0.0f));
	baseBody1->setCategoryBitmask(0xFFFFFFFF);
	baseBody1->setCollisionBitmask(0xFFFFFFFF);
	baseBody1->setContactTestBitmask(0xFFFFFFFF);
	baseBody1->setGravityEnable(false);
	baseBody1->setDynamic(false);
	baseBody1->setRotationEnable(false);
	base1->setPhysicsBody(baseBody1);
	this->addChild(base1, 1);

	auto base2 = Sprite::create("bar.png");
	base2->setScaleY(0.5);
	base2->setScaleX(0.7);
	base2->setPosition(Vec2(visibleSize.width / 2 + 300, 250));

	auto baseBody2 = PhysicsBody::createBox(base2->getContentSize(), PhysicsMaterial(100.0f, 0.5f, 0.0f));
	baseBody2->setCategoryBitmask(0xFFFFFFFF);
	baseBody2->setCollisionBitmask(0xFFFFFFFF);
	baseBody2->setContactTestBitmask(0xFFFFFFFF);
	baseBody2->setGravityEnable(false);
	baseBody2->setDynamic(false);
	baseBody2->setRotationEnable(false);
	base2->setPhysicsBody(baseBody2);
	this->addChild(base2, 1);

	auto playerLabel1 = Label::createWithTTF(ttfConfig, "player1: ");
	playerLabel1->setPosition(Vec2(origin.x + 50, visibleSize.height - 15));

	auto playerLabel2 = Label::createWithTTF(ttfConfig, "player2: ");
	playerLabel2->setPosition(Vec2(origin.x + 750, visibleSize.height - 15));
	this->addChild(playerLabel1, 0);
	this->addChild(playerLabel2, 0);

	Sprite* sp0 = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(0, 320, 420, 47)));
	Sprite* sp2 = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(0, 320, 420, 47)));
	Sprite* sp = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(610, 362, 4, 16)));

	hp1 = 100, hp2 = 100, ct;

	pT1 = ProgressTimer::create(sp);
	pT1->setScaleX(90);
	pT1->setAnchorPoint(Vec2(0, 0));
	pT1->setType(ProgressTimerType::BAR);
	pT1->setBarChangeRate(Point(1, 0));
	pT1->setMidpoint(Point(0, 1));
	pT1->setPercentage(100);
	pT1->setPosition(Vec2(origin.x + 100 + 14 * pT1->getContentSize().width, origin.y + visibleSize.height - 2 * pT1->getContentSize().height));
	addChild(pT1, 1);
	sp0->setAnchorPoint(Vec2(0, 0));
	sp0->setPosition(Vec2(origin.x + 100 + pT1->getContentSize().width, origin.y + visibleSize.height - sp0->getContentSize().height));
	addChild(sp0, 0);

	pT2 = ProgressTimer::create(sp);
	pT2->setScaleX(90);
	pT2->setAnchorPoint(Vec2(0, 0));
	pT2->setType(ProgressTimerType::BAR);
	pT2->setBarChangeRate(Point(1, 0));
	pT2->setMidpoint(Point(0, 1));
	pT2->setPercentage(100);
	pT2->setPosition(Vec2(origin.x + 800 + 14 * pT2->getContentSize().width, origin.y + visibleSize.height - 2 * pT2->getContentSize().height));
	addChild(pT2, 1);
	sp2->setAnchorPoint(Vec2(0, 0));
	sp2->setPosition(Vec2(origin.x + 800 + pT2->getContentSize().width, origin.y + visibleSize.height - sp0->getContentSize().height));
	addChild(sp2, 0);

	/*player1 = Sprite::create("Fire 0.png");
	player1->setPosition(visibleSize.width / 2 - 8, player1->getContentSize().height + 10);
	this->addChild(player1, 1);
	// 旋转180°
	player1->setRotation(180);
	headingLeft1 = false;

	playerFeet = Sprite::create("Image 0.png");
	playerFeet->setPosition(visibleSize.width / 2, playerFeet->getContentSize().height);
	playerFeet->s
	this->addChild(playerFeet, 1);*/

	auto texture = Director::getInstance()->getTextureCache()->addImage("left.png");
	auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 60, 83)));
	player1 = Sprite::createWithSpriteFrame(frame0);
	player1->setPosition(Vec2(100, 100));
	player1->setColor(Color3B::ORANGE);

	auto playerBody = PhysicsBody::createBox(player1->getContentSize(), PhysicsMaterial(100.0f, 1.0f, 0.5f));
	playerBody->setCategoryBitmask(0x03);
	playerBody->setCollisionBitmask(0x03);
	playerBody->setContactTestBitmask(0x03);
	playerBody->setGravityEnable(true);
	playerBody->setDynamic(true);
	playerBody->setRotationEnable(false);

	player1->setPhysicsBody(playerBody);
	player1->setFlippedX(true);

	player2 = Sprite::createWithSpriteFrame(frame0);
	player2->setPosition(Vec2(visibleSize.width - 100, 100));

	auto playerBody2 = PhysicsBody::createBox(player2->getContentSize(), PhysicsMaterial(100.0f, 1.0f, 1.0f));
	playerBody2->setCategoryBitmask(0x03);
	playerBody2->setCollisionBitmask(0x03);
	playerBody2->setContactTestBitmask(0x03);
	playerBody2->setGravityEnable(true);
	playerBody2->setRotationEnable(false);
	playerBody2->setDynamic(true);

	player2->setPhysicsBody(playerBody2);

	this->addChild(player2, 1);
	this->addChild(player1, 1);

	headingLeft1 = false;
	headingLeft2 = true;

	moveAni();
	fireAni();
	addTouchListener();
	addKeyboardListener();
	addCustomListener();

	// 调度器
	schedule(schedule_selector(GameScene::update), 0.04f, kRepeatForever, 0);

	srand(time(NULL));

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

//发射子弹
void GameScene::fireBullet(int p) {

	MoveBy* moveby;
	if (p == 1) {
		auto bullet = Sprite::create("bullet.png");
		bullet->setAnchorPoint(Vec2(0.5, 0.5));
		bullet->setPosition(player1->getPosition());

		if (headingLeft1) {
			bullet->setRotation(-90);
			moveby = MoveBy::create(1.5f, Vec2(-visibleSize.width, 0));
		}
		else {
			bullet->setRotation(90);
			moveby = MoveBy::create(1.5f, Vec2(visibleSize.width, 0));
		}
		bullets1.push_back(bullet);
		addChild(bullet, 1);
		//SimpleAudioEngine::getInstance()->playEffect("music/fire.wav", false);

		// 移除飞出屏幕外的子弹
		// Todo

		bullet->runAction(
			Sequence::create(
				moveby,
				CallFunc::create([bullet, this] {
			if (bullet->getPosition().y >= visibleSize.height) {
				auto tmp = bullet;
				tmp->removeFromParentAndCleanup(true);
				bullets1.remove(bullet);
			}
		}),
				nullptr
			)
		);
	}
	else if (p == 2) {
		auto bullet = Sprite::create("bullet.png");
		bullet->setAnchorPoint(Vec2(0.5, 0.5));
		bullet->setPosition(player2->getPosition());

		if (headingLeft2) {
			bullet->setRotation(-90);
			moveby = MoveBy::create(1.5f, Vec2(-visibleSize.width, 0));
		}
		else {
			bullet->setRotation(90);
			moveby = MoveBy::create(1.5f, Vec2(visibleSize.width, 0));
		}
		bullets2.push_back(bullet);
		
		addChild(bullet, 1);
		//SimpleAudioEngine::getInstance()->playEffect("music/fire.wav", false);

		// 移除飞出屏幕外的子弹
		// Todo

		bullet->runAction(
			Sequence::create(
				moveby,
				CallFunc::create([bullet, this] {
			if (bullet->getPosition().y >= visibleSize.height) {
				auto tmp = bullet;
				tmp->removeFromParentAndCleanup(true);
				bullets2.remove(bullet);
			}
		}),
				nullptr
			)
		);
	}

}

void GameScene::addTouchListener() {
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}


bool GameScene::onTouchBegan(Touch *touch, Event *event) {
	player1->runAction(Animate::create(Animation::createWithSpriteFrames(move1, 0.05f, 1)));
	//playerFeet->runAction(Animate::create(Animation::createWithSpriteFrames(move, 0.05f, 1)));
	player2->runAction(Animate::create(Animation::createWithSpriteFrames(move1, 0.05f, 1)));
	fireBullet(1);
	return true;
}

// 添加键盘事件监听器
void GameScene::addKeyboardListener() {
	// Todo
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode code, Event* event) {
	switch (code) {

	case EventKeyboard::KeyCode::KEY_CAPITAL_A:
	case EventKeyboard::KeyCode::KEY_A:
		movekey1 = 'A';
		if (!headingLeft1) {
			player1->setFlippedX(false);
			headingLeft1 = true;
		}
		if (player1->getPosition().x > 30) {
			player1->getPhysicsBody()->setVelocity(Vec2(-200, 0) + player1->getPhysicsBody()->getVelocity());
		}
		player1->runAction(Animate::create(Animation::createWithSpriteFrames(move1, 0.05f, 1)));
		break;
	case EventKeyboard::KeyCode::KEY_CAPITAL_D:
	case EventKeyboard::KeyCode::KEY_D:
		//movekey = 'D';
		if (headingLeft1) {
			player1->setFlippedX(true);
			headingLeft1 = false;
		}
		if (player1->getPosition().x < visibleSize.width - 30) {
			player1->getPhysicsBody()->setVelocity(Vec2(200, 0) + player1->getPhysicsBody()->getVelocity());
		}
		player1->runAction(Animate::create(Animation::createWithSpriteFrames(move1, 0.05f, 1)));
		break;
	case EventKeyboard::KeyCode::KEY_CAPITAL_W:
	case EventKeyboard::KeyCode::KEY_W:
		if (player1->getPosition().y < visibleSize.height - 100) {
			player1->getPhysicsBody()->setVelocity(Vec2(0, 200) + player1->getPhysicsBody()->getVelocity());
		}
		player1->runAction(Animate::create(Animation::createWithSpriteFrames(move1, 0.05f, 1)));
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		//movekey2 = 'A';
		if (!headingLeft2) {
			player2->setFlippedX(false);
			headingLeft2 = true;
		}
		if (player2->getPosition().x > 30) {
			player2->getPhysicsBody()->setVelocity(Vec2(-200, 0) + player2->getPhysicsBody()->getVelocity());
		}

		player2->runAction(Animate::create(Animation::createWithSpriteFrames(move1, 0.05f, 1)));
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		if (headingLeft2) {
			player2->setFlippedX(true);
			headingLeft2 = false;
		}
		if (player2->getPosition().x < visibleSize.width - 30) {
			player2->getPhysicsBody()->setVelocity(Vec2(200, 0) + player2->getPhysicsBody()->getVelocity());
		}
		player2->runAction(Animate::create(Animation::createWithSpriteFrames(move1, 0.05f, 1)));
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		if (player2->getPosition().y < visibleSize.height - 100) {
			player2->getPhysicsBody()->setVelocity(Vec2(0, 200) + player2->getPhysicsBody()->getVelocity());
		}
		player2->runAction(Animate::create(Animation::createWithSpriteFrames(move1, 0.05f, 1)));
		break;
	case EventKeyboard::KeyCode::KEY_CAPITAL_G:
	case EventKeyboard::KeyCode::KEY_G:
		fireBullet(1);
		break;
	case EventKeyboard::KeyCode::KEY_CAPITAL_L:
	case EventKeyboard::KeyCode::KEY_L:
		fireBullet(2);
		break;
	}
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode code, Event* event) {
	switch (code) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
	case EventKeyboard::KeyCode::KEY_CAPITAL_A:
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
	case EventKeyboard::KeyCode::KEY_CAPITAL_D:
		player1->getPhysicsBody()->setVelocity(Vec2(0, 0));
		player2->getPhysicsBody()->setVelocity(Vec2(0, 0));
		break;
	}
}


void GameScene::hitByBullet(EventCustom * event) {
	auto gameover = CallFunc::create(CC_CALLBACK_0(GameScene::gameOver, this));
	for (auto i : bullets1) {
		if (player2->getBoundingBox().containsPoint(i->getPosition())) {
			// player2 掉血
			hp2 = hp2 - 10 <= 0 ? 0 : hp2 - 10;
			
			auto tmp = i;
			bullets1.remove(i);
			tmp->removeFromParentAndCleanup(true);
			CCProgressTo* progress = CCProgressTo::create(0.5, hp2);
			pT2->runAction(Sequence::create(progress, gameover, nullptr));
			break;
		}
	}

	for (auto i : bullets2) {
		if (player1->getBoundingBox().containsPoint(i->getPosition())) {
			// player1 掉血
			hp1 = hp1 - 10 <= 0 ? 0 : hp1 - 10;

			auto tmp = i;
			bullets2.remove(i);
			tmp->removeFromParentAndCleanup(true);
			CCProgressTo* progress = CCProgressTo::create(0.5, hp1);
			pT1->runAction(Sequence::create(progress, gameover, nullptr));
			break;
		}
	}
}

void GameScene::update(float fl) {
	// 分发自定义事件
	EventCustom e("hitByBullet");
	_eventDispatcher->dispatchEvent(&e);

	EventCustom e1("eatFruits");
	_eventDispatcher->dispatchEvent(&e1);
	//gameOver();
	ct++;
	if (ct == 250) {
		randomOffer();
		ct = 0;
	}
	if (ct == 200) {
		if (apple != nullptr) {
			apple->removeFromParentAndCleanup(true);
			apple = nullptr;
		}
		if (banana != nullptr) {
			banana->removeFromParentAndCleanup(true);
			banana = nullptr;
		}
		if (grape != nullptr) {
			grape->removeFromParentAndCleanup(true);
			grape = nullptr;
		}
	}
}

void GameScene::addCustomListener() {
	auto meetListener = EventListenerCustom::create("hitByBullet", CC_CALLBACK_1(GameScene::hitByBullet, this));
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(meetListener, this);

	auto meetListener1 = EventListenerCustom::create("eatFruits", CC_CALLBACK_1(GameScene::eatFruits, this));
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(meetListener1, this);
}

void GameScene::gameOver() {

	TTFConfig ttfConfig;
	ttfConfig.fontFilePath = "fonts/arial.ttf";
	ttfConfig.fontSize = 36;

	if (hp1 <= 0 || hp2 <= 0) {
		auto gameOver = Sprite::create("gameOver.png");
		gameOver->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
		this->addChild(gameOver, 3);
		auto label2 = Label::createWithTTF(ttfConfig, "Restart");
		label2->setColor(Color3B(0, 0, 0));
		auto replayBtn = MenuItemLabel::create(label2, CC_CALLBACK_1(GameScene::replayCallback, this));
		Menu* replay = Menu::create(replayBtn, NULL);
		replay->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 200);
		this->addChild(replay, 3);
	}

	if (hp1 <= 0) {
		auto winLabel = Label::createWithTTF(ttfConfig, "Player2 Win!");
		winLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 100));
		this->addChild(winLabel, 3);
		Director::getInstance()->pause();
		//Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	}
	else if (hp2 <= 0) {
		auto winLabel = Label::createWithTTF(ttfConfig, "Player1 Win!");
		winLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 100));
		this->addChild(winLabel, 3);
		Director::getInstance()->pause();
		//Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	}

}

void GameScene::replayCallback(Ref * pSender) {
	Director::getInstance()->resume();
	Director::getInstance()->replaceScene(GameScene::createScene());
}

// 随机提供可以补血的物品
void GameScene::randomOffer() {
	int ranX = rand() % ((int)visibleSize.width - 50);
	if (ranX < 50)
	{
		ranX = 50;
	}
	auto ranPoint = Point(ranX, visibleSize.height - 80);

	apple = Sprite::create("apple.png");
	apple->setPosition(ranPoint);
	auto appleBody = PhysicsBody::createBox(apple->getContentSize(), PhysicsMaterial(100.0f, 0.5f, 0.0f));
	appleBody->setCategoryBitmask(0x100);
	appleBody->setCollisionBitmask(0x100);
	appleBody->setContactTestBitmask(0x100);
	appleBody->setDynamic(true);
	appleBody->setGravityEnable(true);
	apple->setPhysicsBody(appleBody);
	this->addChild(apple, 1);

	int ranX2 = rand() % ((int)visibleSize.width - 50);
	if (ranX2 < 50)
	{
		ranX2 = 50;
	}
	auto ranPoint2 = Point(ranX2, visibleSize.height - 80);

	banana = Sprite::create("banana.png");
	banana->setPosition(ranPoint2);
	auto bananaBody = PhysicsBody::createBox(banana->getContentSize(), PhysicsMaterial(100.0f, 0.5f, 0.0f));
	bananaBody->setCategoryBitmask(0x100);
	bananaBody->setCollisionBitmask(0x100);
	bananaBody->setContactTestBitmask(0x100);
	bananaBody->setDynamic(true);
	bananaBody->setGravityEnable(true);
	banana->setPhysicsBody(bananaBody);
	this->addChild(banana, 1);

	int ranX3 = rand() % ((int)visibleSize.width - 50);
	if (ranX3 < 50)
	{
		ranX3 = 50;
	}
	auto ranPoint3 = Point(ranX3, visibleSize.height - 80);

	grape = Sprite::create("grape.png");
	grape->setPosition(ranPoint3);
	auto grapeBody = PhysicsBody::createBox(grape->getContentSize(), PhysicsMaterial(100.0f, 0.5f, 0.0f));
	grapeBody->setCategoryBitmask(0x100);
	grapeBody->setCollisionBitmask(0x100);
	grapeBody->setContactTestBitmask(0x100);
	grapeBody->setDynamic(true);
	grapeBody->setGravityEnable(true);
	grape->setPhysicsBody(grapeBody);
	this->addChild(grape, 1);
}

void GameScene::eatFruits(EventCustom * event) {
	if (apple != nullptr && player1->getBoundingBox().containsPoint(apple->getPosition())) {
		hp1 = hp1 + 5 > 100 ? 100 : hp1 + 5;
		CCProgressTo* progress = CCProgressTo::create(0.5, hp1);
		pT1->runAction(progress);
		if (apple != nullptr) {
			apple->removeFromParentAndCleanup(true);
			apple = nullptr;
		}
	}
	if (apple != nullptr && player2->getBoundingBox().containsPoint(apple->getPosition())) {
		hp2 = hp2 + 5 > 100 ? 100 : hp2 + 5;
		CCProgressTo* progress = CCProgressTo::create(0.5, hp2);
		pT2->runAction(progress);
		if (apple != nullptr) {
			apple->removeFromParentAndCleanup(true);
			apple = nullptr;
		}
	}

	if (banana != nullptr && player1->getBoundingBox().containsPoint(banana->getPosition())) {
		hp1 = hp1 + 20 > 100 ? 100 : hp1 + 20;
		CCProgressTo* progress = CCProgressTo::create(0.5, hp1);
		pT1->runAction(progress);
		if (banana != nullptr) {
			banana->removeFromParentAndCleanup(true);
			banana = nullptr;
		}
	}
	if (banana != nullptr && player2->getBoundingBox().containsPoint(banana->getPosition())) {
		hp2 = hp2 + 20 > 100 ? 100 : hp2 + 20;
		CCProgressTo* progress = CCProgressTo::create(0.5, hp2);
		pT2->runAction(progress);
		if (banana != nullptr) {
			banana->removeFromParentAndCleanup(true);
			banana = nullptr;
		}
	}

	if (grape != nullptr && player1->getBoundingBox().containsPoint(grape->getPosition())) {
		hp1 = hp1 + 10 > 100 ? 100 : hp1 + 10;
		CCProgressTo* progress = CCProgressTo::create(0.5, hp1);
		pT1->runAction(progress);
		if (grape != nullptr) {
			grape->removeFromParentAndCleanup(true);
			grape = nullptr;
		}
	}
	if (grape != nullptr && player2->getBoundingBox().containsPoint(grape->getPosition())) {
		hp2 = hp2 + 10 > 100 ? 100 : hp2 + 10;
		CCProgressTo* progress = CCProgressTo::create(0.5, hp2);
		pT2->runAction(progress);
		if (grape != nullptr) {
			grape->removeFromParentAndCleanup(true);
			grape = nullptr;
		}
	}
}