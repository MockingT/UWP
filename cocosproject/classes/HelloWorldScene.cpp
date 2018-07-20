#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene() {
  return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename) {
  printf("Error while loading: %s\n", filename);
  printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
  //////////////////////////////
  // 1. super init first
  if (!Scene::init()) {
    return false;
  }

  auto visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();

  auto bgsprite = Sprite::create("bg.jpg");
  bgsprite->setPosition(visibleSize / 2);
  bgsprite->setScale(visibleSize.width / bgsprite->getContentSize().width,
	  visibleSize.height / bgsprite->getContentSize().height);
  this->addChild(bgsprite, 0);

  auto start = MenuItemImage::create("start-0.png", "start-1.png",CC_CALLBACK_1(HelloWorld::startMenuCallback,this));
  start->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y + 100));
  auto startMenu = Menu::create(start, NULL);
  startMenu->setPosition(Vec2::ZERO);
  this->addChild(startMenu, 1);
  

  return true;
}

void HelloWorld::startMenuCallback(Ref * pSender) {
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}
