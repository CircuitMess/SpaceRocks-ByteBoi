#include "ShowHighscoreState.h"
#include "bitmaps/spacerocks_gameover.hpp"
#include <Input/Input.h>
#include "SpaceRocks.h"
#include "Highscore/Highscore.h"
#include "bitmaps/spacerocks_backdrop.hpp"

SpaceRocks::ShowHighscoreState *SpaceRocks::ShowHighscoreState::instance = nullptr;

SpaceRocks::ShowHighscoreState::ShowHighscoreState(Sprite *sprite) : State(sprite)
{
	instance = this;
}
void SpaceRocks::ShowHighscoreState::start(SpaceRocks& _game)
{
	game = &_game;
	Input::getInstance()->setBtnPressCallback(BTN_UP, [](){
		instance->game->deleteHighscores();
	});
	Input::getInstance()->setBtnPressCallback(BTN_A, [](){
		instance->game->returnToTitle();
	});
	Input::getInstance()->setBtnPressCallback(BTN_B, [](){
		instance->game->returnToTitle();
	});
}
void SpaceRocks::ShowHighscoreState::stop()
{
	Input::getInstance()->removeBtnPressCallback(BTN_UP);
	Input::getInstance()->removeBtnPressCallback(BTN_A);
	Input::getInstance()->removeBtnPressCallback(BTN_B);
}
void SpaceRocks::ShowHighscoreState::draw()
{
	display->clear(TFT_BLACK);
	display->drawIcon(spacerocks_backdrop, 0, 0, 160, 120, 1, TFT_BLACK);
	display->setTextSize(1);
	display->setFont(&fonts::Font2);
	display->setTextColor(TFT_WHITE);
	display->drawString("HIGHSCORES", display->width() / 2,-2);
	display->setCursor(3, 110);
	for (int i = 1; i < 6;i++)
	{
		display->setCursor(22, 2 + i * 16);
		if(i <= Highscore.count())
		{
			display->printf("%d.   %.3s    %04d", i, Highscore.get(i - 1).name, Highscore.get(i - 1).score);
		}
		else
		{
			display->printf("%d.    ---   ----", i);
		}
	}
	display->drawString("Press UP to erase", display->width() / 2, 105);
}

void SpaceRocks::ShowHighscoreState::update(uint _time, SpaceRocks& game)
{
}
