#ifndef SPACEROCKS_STATE_H
#define SPACEROCKS_STATE_H
#include <Display/Sprite.h>


namespace SpaceRocks
{

class SpaceRocks;
class State
{
public:
	State(Sprite* sprite) : display(sprite) {}
	virtual ~State();
	virtual void start(SpaceRocks& game) = 0;
	virtual void update(uint _time, SpaceRocks& game) = 0;
	virtual void draw() = 0;
	virtual void stop(){}

	void drawBackground();
	void drawStar(int16_t x, int16_t y, uint8_t size, Color color);

protected:
	Sprite* display;
	SpaceRocks* game;
};

};


#endif