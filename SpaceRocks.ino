#include <Arduino.h>
#include "src/SpaceRocks.h"
#include <CircuitOS.h>
#include <Input/I2cExpander.h>
#include <Input/InputI2C.h>
#include <Update/UpdateManager.h>
#include <ArduinoJson.h>
#include <spiffs_api.h>
#include <gpio.h>
#include <avr/pgmspace.h>
#include "Nibble.hpp"

Display display(128, 128, BL_PIN, 0);
I2cExpander i2c;
InputI2C buttons(&i2c);
SpaceRocks game(display);

void setup() {
	gpio_init();
	i2c.begin(0x74, 4, 5);
	display.begin();
	Serial.begin(115200);
	Serial.println("BL on");
	display.getBaseSprite()->clear(TFT_BLACK);
	display.commit();
	Serial.println("display ok");
	Serial.println("buttons begin");
	SPIFFS.begin();
	UpdateManager::addListener(&buttons);
	Serial.println("spiffs begin");
	
	game.unpack();
	game.start();
}

void loop() {
	UpdateManager::update();
	yield();
}