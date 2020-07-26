#ifndef SPACEROCKS_GAMEOVERSTATE_H
#define SPACEROCKS_GAMEOVERSTATE_H

#include "State.hpp"

namespace SpaceRocks
{

class GameOverState : public State
{
public:
	GameOverState(Sprite* sprite);
	void update(uint _time, SpaceRocks& game) override;
	void draw() override;
	void start(SpaceRocks& _game) override;
	void stop() override;
private:
	void drawBitmap(int16_t x, int16_t y, const byte *bitmap, uint16_t color, uint8_t scale = 1);
	uint linesDrawn;
	static GameOverState *instance;
	bool animationOver = 0;
};

};

#endif