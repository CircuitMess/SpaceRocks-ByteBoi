#ifndef SPACEROCKS_H
#define SPACEROCKS_H

#include <Arduino.h>
#include <CircuitOS.h>
#include <Input/Input.h>
#include <Loop/LoopManager.h>
#include <Support/Context.h>
#include <ByteBoi.h>

#include <UI/Image.h>
#include <Display/Sprite.h>

namespace SpaceRocks
{

class State;
class SpaceRocks : public Context, public LoopListener
{
public:
	SpaceRocks(Display* Display);
	void draw() override;
	void start() override;
	void loop(uint _time) override;
	void stop() override;
	void pack() override;

	void newGame();
	void enterHighscore();
	void openHighscores();
	void deleteHighscores();
	void pauseGame();
	void gameOver();
	void resumeGame();
	void returnToTitle();
	uint score;
	State *pausedGameState = nullptr;
private:
	static SpaceRocks *instance;
	State *state;
	Display *display;
	Sprite *canvas;
};

};

#endif