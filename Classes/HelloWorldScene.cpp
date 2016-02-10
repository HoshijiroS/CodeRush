#include "HelloWorldScene.h"
#include "Player.h"
#include "cocos2d.h"
#include "Food.h"
#include "String.h"
#include "SimpleAudioEngine.h"
#define ccsf(...) CCString::createWithFormat(__VA_ARGS__)->getCString()

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool HelloWorld::init() {
	if (!Layer::init()) {
		return false;
	}

	Vec2 visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	background = Sprite::create("bg.png"); // 434 153
	background->setPosition(origin.x + visibleSize.x / 2, origin.y + visibleSize.y / 2);
	this->addChild(background);

	//play area
	bg_layer = Sprite::create("bg_layer.png");
	bg_layer->setPosition(origin.x + visibleSize.x / 2, origin.y - visibleSize.y / 2);
	background->addChild(bg_layer, 1);

	//score
	TTFConfig label_config;
	label_config.fontFilePath = "fonts/8-BIT WONDER.ttf";
	label_config.fontSize = 12;
	label_config.glyphs = GlyphCollection::DYNAMIC;
	label_config.customGlyphs = nullptr;
	label_config.distanceFieldEnabled = false;
	label_config.outlineSize = 0;
	this->label_two = Label::createWithTTF(label_config, "Score 0");
	label_two->setColor(ccc3(69, 69, 64));
	label_two->setPosition(Point(visibleSize.x / 2, visibleSize.y - 70));
	background->addChild(label_two, 6);

	//game over
	TTFConfig label_config1;
	label_config1.fontFilePath = "fonts/8-BIT WONDER.ttf";
	label_config1.fontSize = 36;
	label_config1.glyphs = GlyphCollection::DYNAMIC;
	label_config1.customGlyphs = nullptr;
	label_config1.distanceFieldEnabled = false;
	label_config1.outlineSize = 0;
	this->label_one = Label::createWithTTF(label_config1, "");
	label_one->setColor(ccc3(229, 255, 255));
	label_one->setPosition(Point(visibleSize.x / 2, visibleSize.y*0.5));
	background->addChild(label_one, 8);

	//music
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
		"bg-music.wav", true);

	//sprite
	player = Player::create(0);
	player->setPosition(Vec2(origin.x + visibleSize.x / 2
		, 300));
	background->addChild(player, 5);
	player->changeDirection(0);
	this->xHeadPos = origin.x + visibleSize.x / 2;
	this->yHeadPos = origin.y + visibleSize.y / 2;
	this->snakeArray.pushBack(this->player);

	//food
	food = Food::create();
	background->addChild(food, 5);

	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			((Player *)event->getCurrentTarget())->changeDirection(0);
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			((Player *)event->getCurrentTarget())->changeDirection(1);
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			((Player *)event->getCurrentTarget())->changeDirection(2);
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			((Player *)event->getCurrentTarget())->changeDirection(3);
			break;
		}
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, player);
	this->scheduleUpdate();
	//cocos2d::Director::getInstance()->pause();

	return true;
}

void HelloWorld::update(float dt) {
	//cocos2d::Director::getInstance()->pause();
	switch (player->dir) {
		case 0: //right
			xHeadPos = player->getPositionX() + 17;
			break;
		case 1: //left
			xHeadPos = player->getPositionX() - 17;
			break;
		case 2: //up
			yHeadPos = player->getPositionY() + 30;
			break;
		case 3: //down
			yHeadPos = player->getPositionY() - 30;
			break;
		default:
			break;
	}

	if (collisionDetected(xHeadPos, yHeadPos)) {
		this->label_one->setString("BOSS GOT YOU");
		CCLayerColor *bgLayer = CCLayerColor::create(ccc4(0, 0, 0, 170));
		background->addChild(bgLayer, 7);
		cocos2d::Director::getInstance()->pause();
	}

	if (collisionDetected(xHeadPos, yHeadPos, food->getPositionX(), food->getPositionY())) {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(
			"Beep4.wav");
		playerTail = Player::create(1);
		//playerTail->changeDirection(player->dir);
		background->addChild(playerTail, 5);
		playerTail->setPosition(this->snakeArray.back()->getPosition());
		//playerTail->changeDirection(player->dir);
		this->snakeArray.pushBack(playerTail);
		score += 10;
		this->label_two->setString(ccsf("Score %d", score));
		this->food->initFood();
		//OutputDebugStringA("Food!");
	}

	else {
		for (int i = snakeArray.size() - 1; i > 0; i--) {
			this->snakeArray.at(i)->setPosition(this->snakeArray.at(i - 1)->getPosition());
			this->snakeArray.at(i)->changeDirection(this->snakeArray.at(i - 1)->dir);
		}

		this->player->setPosition(xHeadPos, yHeadPos);
	}
	//setHeadPosition();
}

void HelloWorld::menuCloseCallback(Ref* pSender) {
	Director::getInstance()->end();
}

boolean HelloWorld::collisionDetected(float snakeHeadX, float snakeHeadY)
{
	if (snakeHeadX < this->background->getBoundingBox().getMinX() ||
		snakeHeadX > this->background->getBoundingBox().getMaxX() ||
		snakeHeadY < this->background->getBoundingBox().getMinY() ||
		snakeHeadY > 130) {
		return true;
	}

	for (int i = 0; i < snakeArray.size(); i++) {
		if (snakeArray.at(i)->getPositionX() == snakeHeadX && snakeArray.at(i)->getPositionY() == snakeHeadY) {
			return true;
		}
	}
	return false;
}

boolean HelloWorld::collisionDetected(float snakeHeadX, float snakeHeadY, float xPosFood, float yPosFood) {
	auto playerRect = this->player->getBoundingBox();
	auto foodRect = this->food->getBoundingBox();
	
	return playerRect.intersectsRect(foodRect);
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif