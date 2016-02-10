#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "Food.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
	boolean collisionDetected(float snakeHeadX, float snakeHeadY);
	boolean collisionDetected(float snakeHeadX, float snakeHeadY, float xPosFood, float yPosFood);
	Vector<Player *> snakeArray;
	int dir;
	float xHeadPos;
	float yHeadPos;
	float prevX;
	float prevY;
	Sprite* background;
	Sprite* bg_layer;
	int score;
	Label* label_two;
	Label* label_one;
	CREATE_FUNC(HelloWorld);

private:
	Player* player;
	Player* playerTail;
	Food* food;
	void update(float dt)override;
};

#endif // __HELLOWORLD_SCENE_H__
