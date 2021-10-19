#ifndef SPACEROCKS_SHIP_PLAYERINPUT_H
#define SPACEROCKS_SHIP_PLAYERINPUT_H
#include <Arduino.h>
#include "InputComponent.h"


namespace SpaceRocks
{

class PlayerInputComponent : public InputComponent
{
public:
	PlayerInputComponent();
	~PlayerInputComponent(){}
	void update(uint _time, Ship& ship) override;
	void start(Ship& ship) override;
	void stop() override;
private:
	Ship* ship;
	static PlayerInputComponent* instance;
	static constexpr float headingTable[24][2] PROGMEM = {
		{ +0.00, -0.30}, { +0.15, -0.29},
		{ +0.20, -0.27}, { +0.24, -0.24},
		{ +0.27, -0.20}, { +0.29, -0.15},
		{ +0.30, +0.00}, { +0.29, +0.15},
		{ +0.27, +0.20}, { +0.24, +0.24},
		{ +0.20, +0.27}, { +0.15, +0.29},
		{ +0.00, +0.30}, { -0.15, +0.29},
		{ -0.20, +0.27}, { -0.24, +0.24},
		{ -0.27, +0.20}, { -0.29, +0.15},
		{ -0.30, +0.00}, { -0.29, -0.15},
		{ -0.27, -0.20}, { -0.24, -0.24},
		{ -0.20, -0.27}, { -0.15, -0.29}
	};
};

};

#endif