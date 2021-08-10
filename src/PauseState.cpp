#include "PauseState.h"
#include "Ship/PlayerInputComponent.h"
#include "bitmaps/spacerocks_backdrop.hpp"
#include <Input/Input.h>
#include "SpaceRocks.h"
SpaceRocks::PauseState* SpaceRocks::PauseState::instance = nullptr;
SpaceRocks::PauseState::PauseState(Sprite* sprite) : State(sprite)
{
	instance = this;
}

void SpaceRocks::PauseState::stop()
{
	Input::getInstance()->removeBtnPressCallback(BTN_B);
	Input::getInstance()->removeBtnPressCallback(BTN_A);
}

void SpaceRocks::PauseState::start(SpaceRocks& _game)
{
	game = &_game;
	Input::getInstance()->setBtnPressCallback(BTN_B, [](){
		delete instance->game->pausedGameState;
		instance->game->pausedGameState = nullptr;
		instance->game->returnToTitle();
	});
	Input::getInstance()->setBtnPressCallback(BTN_A, [](){
		instance->game->resumeGame();
	});
	
}
void SpaceRocks::PauseState::update(uint _time, SpaceRocks& game)
{
}
void SpaceRocks::PauseState::draw()
{
	display->clear(TFT_BLACK);
	display->drawIcon(spacerocks_backdrop, 0, 0, 160, 120, 1, TFT_BLACK);
	display->setCursor(32, display->height()/2 - 25);
	display->setTextSize(2);
	display->setFont(&fonts::Font2);
	display->setTextColor(TFT_WHITE);
	display->printCenter("PAUSE");
	display->setTextSize(1);
	display->drawString("A: resume     B: quit", display->width()/2,100);
}