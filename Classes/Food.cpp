#include "Food.h"
#include "cocos2d.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Food::Food()
{
}

Food * Food::create() {
	Food * food = new Food();

	if (food && food->initWithFile("Items/burger.png"))
	{
		food->autorelease();
		food->initFood();
		return food;
	}
	/*case 1:
		if (food && food->initWithFile("Items/burger.png"))
		{
			food->autorelease();
			food->initSpecialFood();
			return food;
		}
	}*/

	CC_SAFE_DELETE(food);
	return NULL;
}

/*
void Food::initSpecialFood() {
	this->schedule(schedule_selector(Food::UpdateTimer), 1.0f);

	this->unschedule(schedule_selector(Game::UpdateTimer));
}

void schedule_selector(CC_SCHEDULE_SELECTOR Food::Updatetimer, int counter;) {
}

void Game::UpdateTimer(float dt) {

}*/

void Food::initFood() {
	this->setPosition(Vec2(cocos2d::random(30, 400), cocos2d::random(0, 130)));
}

Food::~Food()
{
}
