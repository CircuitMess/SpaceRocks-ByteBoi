#ifndef SPACEROCKS_GAMEOVERSTATE_H
#define SPACEROCKS_GAMEOVERSTATE_H

#include "State.hpp"
#include <ByteBoi.h>

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
	virtual ~GameOverState();
private:
	uint linesDrawn;
	static GameOverState *instance;
	bool animationOver = 0;
	Sample* music = nullptr;

};

};

#endif