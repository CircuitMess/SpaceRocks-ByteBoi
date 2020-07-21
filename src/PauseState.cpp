#include "PauseState.h"
#include "Ship/PlayerInputComponent.h"
#include "bitmaps/spacerocks_backdrop.hpp"
#include <Input/Input.h>
#include "SpaceRocks.h"
PauseState* PauseState::instance = nullptr;
PauseState::PauseState(Sprite* sprite) : State(sprite)
{
	instance = this;
}

PauseState::~PauseState()
{
	Input::getInstance()->removeBtnPressCallback(BTN_B);
	Input::getInstance()->removeBtnPressCallback(BTN_A);
}

void PauseState::start(SpaceRocks& _game)
{
	game = &_game;
	Input::getInstance()->setBtnPressCallback(BTN_B, [](){
		instance->game->quitGame();
	});
	Input::getInstance()->setBtnPressCallback(BTN_A, [](){
		instance->game->resumeGame();
	});
	
}
void PauseState::update(uint _time, SpaceRocks& game)
{
	
}
void PauseState::draw()
{
	display->drawIcon(spacerocks_backdrop, 0, 0, 128, 128);
	display->setCursor(32, display->height()/2 - 25);
	display->setTextSize(2);
	display->setTextFont(2);
	display->setTextColor(TFT_WHITE);
	display->printCenter("PAUSE");
	display->setTextSize(1);
	display->setCursor(110,110);
	display->printCenter("A: resume   B: quit");
}