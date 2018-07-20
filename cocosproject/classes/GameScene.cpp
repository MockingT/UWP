#include "GameScene.h"

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

	auto playerLabel1 = Label::createWithTTF(ttfConfig, "player1: ");
	playerLabel1->setPosition(Vec2(origin.x + 50, visibleSize.height - 15));
	
	auto playerLabel2 = Label::createWithTTF(ttfConfig, "player2: ");
	playerLabel2->setPosition(Vec2(origin.x + 750, visibleSize.height - 15));
	this->addChild(playerLabel1, 0);
	this->addChild(playerLabel2, 0);

	Sprite* sp0 = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(0, 320, 420, 47)));
	Sprite* sp2 = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(0, 320, 420, 47)));
	Sprite* sp = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(610, 362, 4, 16)));

	hp1 = 100, hp2 = 100;

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

	auto playerBody = PhysicsBody::createBox(player1->getContentSize(), PhysicsMaterial(100.0f, 0.5f, 0.0f));
	playerBody->setCategoryBitmask(0x00000001);
	playerBody->setCollisionBitmask(0x00000001);
	playerBody->setContactTestBitmask(0x00000001);
	playerBody->setDynamic(false);

	player1->setPhysicsBody(playerBody);
	player1->setFlippedX(true);

	player2 = Sprite::createWithSpriteFrame(frame0);
	player2->setPosition(Vec2(visibleSize.width - 100, 100));

	auto playerBody2 = PhysicsBody::createBox(player2->getContentSize(), PhysicsMaterial(100.0f, 0.5f, 0.0f));
	playerBody2->setCategoryBitmask(0x00000001);
	playerBody2->setCollisionBitmask(0x00000001);
	playerBody2->setContactTestBitmask(0x00000001);
	playerBody2->setDynamic(false);

	player2->setPhysicsBody(playerBody2);

	this->addChild(player2, 1);
	this->addChild(player1, 1);
	headingLeft1 = false;
	headingLeft2 = true;

	moveAni();
	fireAni();
	addTouchListener();
	addKeyboardListener();

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
	auto bullet = Sprite::create("bullet.png");
	bullet->setAnchorPoint(Vec2(0.5, 0.5));
	MoveBy* moveby;
	if (p == 1) {
		bullet->setPosition(player1->getPosition());
		if (headingLeft1) {
			bullet->setRotation(-90);
			moveby = MoveBy::create(1.5f, Vec2(-visibleSize.width, 0));
		}
		else {
			bullet->setRotation(90);
			moveby = MoveBy::create(1.5f, Vec2(visibleSize.width, 0));
		}
	}
	else if (p == 2) {
		bullet->setPosition(player2->getPosition());
		if (headingLeft2) {
			bullet->setRotation(-90);
			moveby = MoveBy::create(1.5f, Vec2(-visibleSize.width, 0));
		}
		else {
			bullet->setRotation(90);
			moveby = MoveBy::create(1.5f, Vec2(visibleSize.width, 0));
		}
	}
	
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
		}
	}),
			nullptr
		)
	);
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
			player1->getPhysicsBody()->setVelocity(Vec2(-500, 0));
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
			player1->getPhysicsBody()->setVelocity(Vec2(500, 0));
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
			player2->getPhysicsBody()->setVelocity(Vec2(-500, 0));
		}

		player2->runAction(Animate::create(Animation::createWithSpriteFrames(move1, 0.05f, 1)));
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		if (headingLeft2) {
			player2->setFlippedX(true);
			headingLeft2 = false;
		}
		if (player2->getPosition().x < visibleSize.width - 30) {
			player2->getPhysicsBody()->setVelocity(Vec2(500, 0));
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

void GameScene::hitByBullet() {

}