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
	game=new SpaceRocks::SpaceRocks(ByteBoi.getDisplay());
	game->unpack();
	ByteBoi.splash();
	game->start();

}

void loop() {
	LoopManager::loop();
}