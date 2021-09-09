#include <Arduino.h>
#include "src/SpaceRocks.h"
#include <CircuitOS.h>
#include <Input/I2cExpander.h>
#include <Input/InputI2C.h>
#include <Loop/LoopManager.h>
#include <SPIFFS.h>
#include <ByteBoi.h>
//#include "Nibble.hpp"
#include <Audio/Piezo.h>

SpaceRocks::SpaceRocks* game;

void setup() {
	Serial.begin(115200);
	ByteBoi.begin();
	ByteBoi.getDisplay()->commit();
	//gpio_init();
	//i2c.begin(0x74, 23, 22);
	//display.begin();
	LoopManager::addListener(Input::getInstance());

	game=new SpaceRocks::SpaceRocks(ByteBoi.getDisplay());
	LoopManager::addListener(game);
	game->unpack();
	game->start();

}

void loop() {
	LoopManager::loop();
	yield();
}