#include "SpaceRocks.h"
#include "State.hpp"
#include "TitleState.h"
#include "GameState.h"
#include "GameOverState.h"
#include "PauseState.h"

SpaceRocks::SpaceRocks::SpaceRocks(Display& display) : Context(display), display(&display), canvas(display.getBaseSprite()), score(0)
{
	randomSeed(micros()*millis());
	state = new TitleState(canvas);
}

void SpaceRocks::SpaceRocks::draw()
{
	state->draw();
}
void SpaceRocks::SpaceRocks::update(uint _time)
{
	state->update(_time, *this);
	draw();
	display->commit();
}
void SpaceRocks::SpaceRocks::start()
{
	state->start(*this);
	UpdateManager::addListener(this);
}
void SpaceRocks::SpaceRocks::stop()
{
	UpdateManager::removeListener(this);
	delete state;
}
void SpaceRocks::SpaceRocks::newGame()
{
	delete state;
	state = new GameState(canvas);
	state->start(*this);
}
void SpaceRocks::SpaceRocks::gameOver()
{
	delete state;
	state = new GameOverState(canvas);
	state->start(*this);
}
void SpaceRocks::SpaceRocks::enterHighscore()
{

}
void SpaceRocks::SpaceRocks::pauseGame()
{
	state->stop();
	pausedGameState = state;
	state = new PauseState(canvas);
	state->start(*this);
}
void SpaceRocks::SpaceRocks::resumeGame()
{
	delete state;
	state = pausedGameState;
	state->start(*this);
}
void SpaceRocks::SpaceRocks::quitGame()
{
	delete state;
	state = new TitleState(canvas);
	state->start(*this);
}
void SpaceRocks::SpaceRocks::openHighscores()
{

}