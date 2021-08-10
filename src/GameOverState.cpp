#include "GameOverState.h"
#include "bitmaps/spacerocks_gameover.hpp"
#include <Input/Input.h>
#include "SpaceRocks.h"
#include "bitmaps/spacerocks_backdrop.hpp"

SpaceRocks::GameOverState *SpaceRocks::GameOverState::instance = nullptr;

SpaceRocks::GameOverState::GameOverState(Sprite* sprite) : State(sprite)
{
	instance = this;
	linesDrawn = 0;
	animationOver = 0;
}
void SpaceRocks::GameOverState::start(SpaceRocks& _game)
{
	game = &_game;
	Input::getInstance()->setBtnPressCallback(BTN_A, [](){
		if(instance->animationOver){
			instance->game->enterHighscore();
		}
	});
	Input::getInstance()->setBtnPressCallback(BTN_B, [](){
		if(instance->animationOver){
			instance->game->enterHighscore();
		}
	});
}
void SpaceRocks::GameOverState::stop()
{
	Input::getInstance()->removeBtnPressCallback(BTN_A);
	Input::getInstance()->removeBtnPressCallback(BTN_B);
}
void SpaceRocks::GameOverState::draw()
{
	display->clear(TFT_BLACK);
	display->drawIcon(spacerocks_backdrop, 0, 0, 160, 120, 1, TFT_BLACK);
	for (int i = 0; i <= linesDrawn*4; i+=4)
	{
		display->drawFastHLine(0, i, display->width(), TFT_DARKGREY);
		display->drawFastHLine(0, i+1, display->width(), TFT_DARKGREY);
	}
	if(linesDrawn >= 32)
	{
		display->drawBitmap(26, 12, spacerocks_gameover, 112, 98, TFT_DARKGREY, (uint8_t)1);
		display->drawBitmap(28, 10, spacerocks_gameover, 112, 98, TFT_BLACK, (uint8_t)1);
	}
}
void SpaceRocks::GameOverState::update(uint _time, SpaceRocks& game)
{
	if(linesDrawn < 32){
		linesDrawn++;
		if(linesDrawn >= 32){
			animationOver = 1;
		}
	}
}
