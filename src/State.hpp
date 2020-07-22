#ifndef SPACEROCKS_STATE_H
#define SPACEROCKS_STATE_H
#include <Display/Sprite.h>
#include "../Nibble.hpp"

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

protected:
	Sprite* display;
	SpaceRocks* game;
};

};


#endif