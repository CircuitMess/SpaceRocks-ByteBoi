#include "DemoInputComponent.h"
#include "Input/Input.h"
#include "../../Nibble.hpp"
#include "Ship.h"
DemoInputComponent::DemoInputComponent() : rotateTimer(0) {}
void DemoInputComponent::start(Ship& ship)
{
}
void DemoInputComponent::update(uint _time, Ship& ship)
{
	rotateTimer+=_time;
	if(rotateTimer >= 300000){
		rotateTimer = 0;
		ship.shoot();
		bool turn = (random(0, 2) == 1);
		if (turn){
			ship.heading++;
		}else{
			ship.heading--;
		}
	}
}
