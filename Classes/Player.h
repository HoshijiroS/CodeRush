#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Player : public cocos2d::Sprite {
public:
	Player();
	static Player * create(int type);
	void moveRightAnimation();
	void moveLeftAnimation();
	void moveUpAnimation();
	void moveDownAnimation();
	void initKumaSprite();
	void initEdSprite();
	void changeDirection(int dir);
	int dir;
	int getDirection();
	Animate* playAnimation(int j, char * filename);
	int type;
	Animate* walkRight;
	Animate* walkLeft;
	Animate* walkUp;
	Animate* walkDown;
	~Player();
};

