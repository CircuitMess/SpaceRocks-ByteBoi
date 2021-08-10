#include "EraseHighscoreState.h"
#include "bitmaps/spacerocks_gameover.hpp"
#include <Input/Input.h>
#include "SpaceRocks.h"
#include "Highscore/Highscore.h"
#include "bitmaps/spacerocks_backdrop.hpp"

SpaceRocks::EraseHighscoreState *SpaceRocks::EraseHighscoreState::instance = nullptr;

SpaceRocks::EraseHighscoreState::EraseHighscoreState(Sprite *sprite) : State(sprite)
{
	instance = this;
	blinkState = 0;
	blinkTime = 0;
}
void SpaceRocks::EraseHighscoreState::start(SpaceRocks& _game)
{
	game = &_game;
	Input::getInstance()->setBtnPressCallback(BTN_B, [](){
		instance->game->openHighscores();

	});
	Input::getInstance()->setBtnPressCallback(BTN_A, [](){
		Highscore.clear();
		instance->game->returnToTitle();

	});
}
void SpaceRocks::EraseHighscoreState::stop()
{
	Input::getInstance()->removeBtnPressCallback(BTN_A);
	Input::getInstance()->removeBtnPressCallback(BTN_B);
}
void SpaceRocks::EraseHighscoreState::draw()
{
	display->clear(TFT_BLACK);
	display->drawIcon(spacerocks_backdrop, 0, 0, 160, 120, 1, TFT_BLACK);
	display->clear(TFT_BLACK);
	display->setFont(&fonts::Font2);
	display->setTextColor(TFT_WHITE);
	display->setTextDatum(textdatum_t::bottom_center);
	display->drawString("ARE YOU SURE?", display->width() / 2, 17);
	display->drawString("This cannot be reverted!", display->width() / 2, 37);
	//	baseSprite->drawString("", screen.getWidth() / 2, 53);

	display->drawString("B: Cancel", display->width() / 2, 105);

	display->setCursor(35, 81);
	display->print("A:");

	if (blinkState){
		display->drawRect(55, 64, 30*2, 9*2, TFT_RED);
		display->drawRect(55, 64, 30*2, 9*2, TFT_RED);
		display->setTextColor(TFT_RED);
		display->setCursor(62, 81);
		display->print("DELETE");
	}
	else {
		display->fillRect(55, 64, 30*2, 9*2, TFT_RED);
		display->setTextColor(TFT_WHITE);
		display->setCursor(62, 81);
		display->print("DELETE");
	}
	display->setTextDatum(textdatum_t::top_center);
}

void SpaceRocks::EraseHighscoreState::update(uint _time, SpaceRocks& game)
{
	blinkTime+=_time;
	if(blinkTime >= 350000)
	{
		blinkTime = 0;
		blinkState = !blinkState;
	}
}
