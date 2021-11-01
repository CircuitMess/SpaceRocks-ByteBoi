#include "TitleState.h"
#include "Ship/DemoInputComponent.h"
#include "bitmaps/spacerocks_backdrop.hpp"
#include "bitmaps/spacerocks_title.hpp"
#include "bitmaps/spacerocks_arrowLeft.hpp"
#include "bitmaps/spacerocks_arrowRight.hpp"
#include <Input/Input.h>
#include "SpaceRocks.h"
#include <ByteBoi.h>

const char *SpaceRocks::TitleState::titleMenu[3] = {"Start", "Hiscores", "Quit"};
SpaceRocks::TitleState* SpaceRocks::TitleState::instance = nullptr;
SpaceRocks::TitleState::TitleState(Sprite* sprite) : State(sprite)
{
	instance = this;
	ship = new Ship(this, new DemoInputComponent(), display);
	ship->shipX = 20;
	ship->shipY = 85;
	ship->invincibility = 0;
	titleCursor = 0;
	blinkState = 0;
	blinkMicros = 0;
}

SpaceRocks::TitleState::~TitleState()
{
	stop();
	delete ship;
}
void SpaceRocks::TitleState::stop()
{
	Input::getInstance()->removeBtnPressCallback(BTN_LEFT);
	Input::getInstance()->removeBtnPressCallback(BTN_RIGHT);
	Input::getInstance()->removeBtnPressCallback(BTN_A);
	ship->stop();
}
void SpaceRocks::TitleState::start(SpaceRocks& _game)
{
	game = &_game;
	Input::getInstance()->setBtnPressCallback(BTN_LEFT, [](){
		if(instance->titleCursor > 0){
			instance->titleCursor--;
			Playback.tone(700, 40);

		}
	});
	Input::getInstance()->setBtnPressCallback(BTN_RIGHT, [](){
		if(instance->titleCursor < 2){
			instance->titleCursor++;
			Playback.tone(700, 40);

		}
	});
	Input::getInstance()->setBtnPressCallback(BTN_A, [](){
		switch (instance->titleCursor)
		{
			case 0:
				instance->game->newGame();
				break;
			
			case 1:
				instance->game->openHighscores();
				break;
			case 2:
				ByteBoi.backToLauncher();
				break;
		}
	});
	ship->start();
}
void SpaceRocks::TitleState::update(uint _time, SpaceRocks& game)
{
	blinkMicros+=_time;
	if(blinkMicros > 200000)
	{
		blinkState = !blinkState;
		blinkMicros = 0;
	}
	ship->update(_time);
	ship->velocityX = 1;
}
void SpaceRocks::TitleState::draw()
{
	display->clear(TFT_BLACK);
	display->drawIcon(spacerocks_backdrop, 0,0,160,120, 1, TFT_BLACK);
	ship->draw();
	display->drawIcon(spacerocks_title, 5,5,150,75, 1, TFT_WHITE);

	display->setFont(&fonts::Font2);
	display->setTextSize(1);
	display->setTextDatum(textdatum_t::top_center);

	display->setTextColor(TFT_WHITE);
	display->drawRect(34, 100, 92, 18, TFT_WHITE);
	display->drawRect(33, 99, 94, 20, TFT_WHITE);

	display->drawString(titleMenu[titleCursor], display->width()/2, 100);
	if(blinkState)
	{
		if (titleCursor == 0)
		{
			display->drawIcon(spacerocks_arrowLeft, 22, 102, 4, 7, 2, TFT_BLACK);
			display->drawIcon(spacerocks_arrowRight, 132, 102, 4, 7, 2, TFT_BLACK);
		}
		else if (titleCursor == 2)
		{
			display->drawIcon(spacerocks_arrowLeft, 20, 102, 4, 7, 2, TFT_BLACK);
			display->drawIcon(spacerocks_arrowRight, 130, 102, 4, 7, 2, TFT_BLACK);
		}
		else
		{
			display->drawIcon(spacerocks_arrowLeft, 20, 102, 4, 7, 2, TFT_BLACK);
			display->drawIcon(spacerocks_arrowRight, 132, 102, 4, 7, 2, TFT_BLACK);
		}
	}
	else
	{
		display->drawIcon(spacerocks_arrowLeft, 22, 102, 4, 7, 2, TFT_BLACK);
		display->drawIcon(spacerocks_arrowRight, 130, 102, 4, 7, 2, TFT_BLACK);
	}
}