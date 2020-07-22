#ifndef SPACEROCKS_SHIP_PLAYERINPUT_H
#define SPACEROCKS_SHIP_PLAYERINPUT_H
#include <Arduino.h>
#include "InputComponent.h"
#include <avr/pgmspace.h>

namespace SpaceRocks
{

class DemoInputComponent : public InputComponent
{
public:
	DemoInputComponent();
	~DemoInputComponent(){}
	void update(uint _time, Ship& ship) override;
	void start(Ship& ship) override;
private:
	uint rotateTimer = 0;
};

};
#endif