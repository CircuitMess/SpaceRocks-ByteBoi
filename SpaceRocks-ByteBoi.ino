#include <Arduino.h>
#include "src/SpaceRocks.h"
#include <CircuitOS.h>
#include <Input/I2cExpander.h>
#include <Input/InputI2C.h>
#include <Loop/LoopManager.h>
#include <SPIFFS.h>
#include <ByteBoi.h>
#include <SD.h>
#include "src/Highscore/Highscore.h"

SpaceRocks::SpaceRocks* game;

void setup() {
	Serial.begin(115200);
	ByteBoi.begin();
	ByteBoi.bindMenu();
	BatteryPopup.enablePopups(true);
	ByteBoi.setGameID("SRock");
	SD.begin(SD_CS, SPI);
	SpaceRocks::Highscore.begin();
	game=new SpaceRocks::SpaceRocks(ByteBoi.getDisplay());
	game->unpack();
	ByteBoi.splash();
	game->start();

}

void loop() {
	LoopManager::loop();
}