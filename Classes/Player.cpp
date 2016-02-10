#include "Player.h"
#include "cocos2d.h"

USING_NS_CC;

Player::Player(void)
{
}

Player * Player::create(int type) {
	Player * player = new Player();
	switch (type) {
	case 0:
		if (player && player->initWithFile("Kumatora/idle/0001.png"))
		{
			//player->autorelease();
			player->initKumaSprite();
			player->type = 0;
			return player;
		}
		break;
	case 1:
		if (player && player->initWithFile("Ed/move_down/0002.png"))
		{
			//player->autorelease();
			player->initEdSprite();
			player->type = 1;
			return player;
		}
		break;
	}

	CC_SAFE_DELETE(player);
	return NULL;
}

void Player::initKumaSprite() {
	this->walkRight = playAnimation(4, "Kumatora/move_right/%04d.png");
	walkRight->retain();
	this->walkLeft = playAnimation(4, "Kumatora/move_left/%04d.png");
	walkLeft->retain();
	this->walkUp = playAnimation(5, "Kumatora/move_up/%04d.png");
	walkUp->retain();
	this->walkDown = playAnimation(5, "Kumatora/move_down/%04d.png");
	walkDown->retain();
}

void Player::initEdSprite() {
	this->walkRight = playAnimation(3, "Ed/move_right/%04d.png");
	walkRight->retain();
	this->walkLeft = playAnimation(3, "Ed/move_left/%04d.png");
	walkLeft->retain();
	this->walkUp = playAnimation(3, "Ed/move_up/%04d.png");
	walkUp->retain();
	this->walkDown = playAnimation(3, "Ed/move_down/%04d.png");
	walkDown->retain();
}

void Player::changeDirection(int dir) {
	switch (dir) {
	case 0:
		//this->stopAllActions();
		this->moveRightAnimation();
		
		this->dir = dir;
		break;
	case 1:
		//this->stopAllActions();
		//animation = Animate::create(Animation::createWithSpriteFrames(walkLeft, 0.09f));
		//this->runAction(RepeatForever::create(animation));
		this->moveLeftAnimation();

		this->dir = dir;
		break;
	case 2:
		//this->stopAllActions();
		//animation = Animate::create(Animation::createWithSpriteFrames(walkUp, 0.09f));
		//this->runAction(RepeatForever::create(animation));
		this->moveUpAnimation();

		this->dir = dir;
		break;
	case 3:
		//this->stopAllActions();
		//animation = Animate::create(Animation::createWithSpriteFrames(walkDown, 0.09f));
		//this->runAction(RepeatForever::create(animation));
		this->moveDownAnimation();

		this->dir = dir;
		break;
	}
}

int Player::getDirection() {
	return this->dir;
}

Animate* Player::playAnimation(int j, char* filename) {
	Vector<SpriteFrame*> animFrames;
	char str[100];
	for (int i = 1; i <= j; i++) {
		sprintf(str, filename, i);
		auto frame = SpriteFrame::create(str, Rect(0, 0, 17, 30));
		animFrames.pushBack(frame);
	}

	//return animFrames;
	return Animate::create(Animation::createWithSpriteFrames(animFrames, 0.09f));
	
	//animation->retain();
	//return animation;
}

void Player::moveRightAnimation() {
	//Animate* animation;
	//this->stopAllActions();
	//animation = Animate::create(Animation::createWithSpriteFrames(this->walkRight, 0.09f));
	//this->runAction(this->walkRight);
	this->runAction(RepeatForever::create(this->walkRight));
}

void Player::moveLeftAnimation() {
	//Animate* animation;
	//this->stopAllActions();
	//animation = Animate::create(Animation::createWithSpriteFrames(this->walkLeft, 0.09f));
	//this->runAction(this->walkLeft);
	//this->runAction(RepeatForever::create(animation));
	//animation->retain();
	this->runAction(RepeatForever::create(this->walkLeft)); //This will be the starting animation
}

void Player::moveUpAnimation() {
	//Animate* animation;
	//this->stopAllActions();
	//animation = Animate::create(Animation::createWithSpriteFrames(this->walkUp, 0.09f));
	this->runAction(RepeatForever::create(this->walkUp));
	//this->runAction(this->walkUp);
	//animation->retain();
}

void Player::moveDownAnimation() {
	//Animate* animation;
	//this->stopAllActions();
	//animation = Animate::create(Animation::createWithSpriteFrames(this->walkDown, 0.09f));
	//this->runAction(RepeatForever::create(animation));
	//animation->retain();
	//this->runAction(this->walkDown);
	this->runAction(RepeatForever::create(this->walkDown));
}

Player::~Player(void)
{
}