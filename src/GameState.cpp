#include "GameState.h"
#include "Ship/PlayerInputComponent.h"
#include "bitmaps/spacerocks_backdrop.hpp"
#include <Input/Input.h>
#include "SpaceRocks.h"
const char *SpaceRocks::GameState::titleMenu[3] = {"Start", "Hiscores", "Quit"};
SpaceRocks::GameState* SpaceRocks::GameState::instance = nullptr;
SpaceRocks::GameState::GameState(Sprite* sprite) : State(sprite)
{
	instance = this;
	ship = new Ship(this, new PlayerInputComponent(), display);
	UIship = new Ship(this, nullptr, display);
	ship->shipX = display->width()/2;
	ship->shipY = display->height()/2;
	UIship->shipX = 99;
	UIship->shipY = 10;
	life = 3;
	score = 0;
	level = 0;
	asteroidTime = 0;
	dead = 0;
	deadTime = 0;
	levelChangeTime = 2000000;
}

SpaceRocks::GameState::~GameState()
{
	stop();
	delete ship;
}

void SpaceRocks::GameState::start(SpaceRocks& _game)
{
	game = &_game;
	Input::getInstance()->setBtnPressCallback(BTN_B, [](){
		instance->game->pauseGame();
	});
	ship->start();
}
void SpaceRocks::GameState::stop()
{
	Input::getInstance()->removeBtnPressCallback(BTN_B);
	ship->stop();
}
void SpaceRocks::GameState::update(uint _time, SpaceRocks& game)
{
	//death animation handling
	if(dead)
	{
		deadTime+=_time;
		if(int(deadTime / 200000) >= 7)
		{
			game.score = score;
			game.gameOver();
		}
		return;
	}

	ship->update(_time);
	asteroids.update(display);
	bool noAsteroids = 1;
	//collision check
	for(int i = 0; i < asteroids.POOL_SIZE; i++)
	{
		//continue if blank asteroid or ship is invincible
		if(!asteroids.asteroids[i].inUse()) continue;
		noAsteroids = 0;
		for(uint8_t j = 0; j < ship->bullets.POOL_SIZE; j++)
		{
			if(!ship->bullets.bullets[j].inUse()) continue;
			if(rectRect(ship->bullets.bullets[j].x, ship->bullets.bullets[j].y, 2, 2,
				asteroids.asteroids[i].x, asteroids.asteroids[i].y, asteroids.asteroids[i].getWidth(), asteroids.asteroids[i].getWidth()))
			{
				tone(BUZZ_PIN, 50, 50);
				switch (asteroids.asteroids[i].type)
				{
				case AsteroidType::asteroid:
					score+=2;
					break;
				case AsteroidType::rock:
					score+=4;
					break;
				case AsteroidType::pebble:
					score+=8;
					break;
				}
				asteroids.broken(i);
				ship->bullets.bullets[j].hit();
			}
		}

		//check overlap ship-asteroid - TODO: actual triangle-rectangle intersection
		if(ship->shipX > asteroids.asteroids[i].x && ship->shipX < asteroids.asteroids[i].x + asteroids.asteroids[i].getWidth() && 
		ship->shipY > asteroids.asteroids[i].y && ship->shipY < asteroids.asteroids[i].y + asteroids.asteroids[i].getWidth() &&
		!ship->invincibility)
		{
			tone(BUZZ_PIN, 50, 50);
			asteroids.broken(i);
			if(life > 0)
			{
				ship->destroyed();
				life--;
			}
			else
			{
				dead = 1;
				deadTime = 0;
			}
		}
	}
	if(noAsteroids)
	{
		if(levelChangeTime < 0)
		{
			levelChangeTime = 0;
		}
		else
		{
			levelChangeTime+=_time;
		}
		
		if(levelChangeTime >= 2000000)
		{
			newLevel();
		}
	}

}
void SpaceRocks::GameState::draw()
{
	display->drawIcon(spacerocks_backdrop, 0, 0, 128, 128);
	if(dead)
	{
		uint8_t passes = (deadTime / 200000) * 2;
		display->drawLine(ship->shipX, ship->shipY + passes, ship->shipX, ship->shipY + passes + 3, TFT_WHITE);
		display->drawLine(ship->shipX, ship->shipY - passes, ship->shipX, ship->shipY - passes - 3, TFT_WHITE);
		display->drawLine(ship->shipX + passes, ship->shipY, ship->shipX + passes + 3, ship->shipY, TFT_WHITE);
		display->drawLine(ship->shipX - passes, ship->shipY, ship->shipX - passes - 3, ship->shipY, TFT_WHITE);
		display->drawLine(ship->shipX + passes, ship->shipY + passes, ship->shipX + passes + 2, ship->shipY + passes + 2, TFT_WHITE);
		display->drawLine(ship->shipX - passes, ship->shipY - passes, ship->shipX - passes - 2, ship->shipY - passes - 2, TFT_WHITE);
		display->drawLine(ship->shipX + passes, ship->shipY - passes, ship->shipX + passes + 2, ship->shipY - passes - 2, TFT_WHITE);
		display->drawLine(ship->shipX - passes, ship->shipY + passes, ship->shipX - passes - 2, ship->shipY + passes + 2, TFT_WHITE);
	}
	else{
		ship->draw();
	}
	asteroids.draw(display);
	display->setTextWrap(0);
	display->setTextFont(2);
	display->setTextSize(1);
	display->setTextColor(TFT_GREEN);
	display->setCursor(4, 2);
	display->printf("LV:%d    %04d    X%d", level, score, life);
	UIship->draw();
}
bool SpaceRocks::GameState::rectRect(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) {
	if (x1 + w1 >= x2 && x1 <= x2 + w2 &&
		y1 + h1 >= y2 && y1 <= y2 + h2)
	{
		return true;
	}
	return false;
}
void SpaceRocks::GameState::newLevel()
{
	level++;
	//TODO - speed up randomization of 
	for(uint8_t i = 0; i < level; i++){
		uint8_t tempX = random(10, 118);
        uint8_t tempY =  random(10, 118);
        while(abs(tempX - ship->shipX) < 40 && abs(tempY-ship->shipY) < 40)
        {
          tempX = random(10, 118);
          tempY = random(10, 118);
        }
		asteroids.create(tempX, tempY, random(-10, 10) * 0.05, random(-10, 10) * 0.05, AsteroidType::asteroid, random(0,3));
	}
	levelChangeTime = -1;
}