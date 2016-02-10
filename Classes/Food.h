#pragma once
#include "cocos2d.h"

class Food : public cocos2d::Sprite
{
public:
	Food();
	~Food();
	static Food* create();
	void initSpecialFood();
	void initFood();

private:
};