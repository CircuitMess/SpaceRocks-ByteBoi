#include "State.hpp"
#include "bitmaps/planet.hpp"
const uint8_t littleStars[4][2] = {{9, 10}, {65, 3}, {152, 46}, {151, 78}};
const uint8_t bigStars[2][2] = {{31, 15}, {93, 117}};

SpaceRocks::State::~State(){
	stop();
}

void SpaceRocks::State::drawBackground(){
	display->drawIcon(planet, 116,85,41,37, 1, TFT_BLACK);
	for (auto &starCoord : littleStars){
		drawStar(starCoord[0], starCoord[1], 1, C_RGB(0, 130, 255));
	}
	for (auto &starCoord : bigStars){
		drawStar(starCoord[0], starCoord[1], 3, C_RGB(0, 190, 255));
	}
	drawStar(85, 110, 2, C_RGB(130, 255, 158));
}

void SpaceRocks::State::drawStar(int16_t x, int16_t y, uint8_t size, Color color){
	uint8_t r = (((((uint16_t)color >> 11) & 0x1F) * 527) + 23) >> 6;
	uint8_t g = (((((uint16_t)color >> 5) & 0x3F) * 259) + 33) >> 6;
	uint8_t b = ((((uint16_t)color & 0x1F) * 527) + 23) >> 6;

	display->drawPixel(x, y, color);
	for(uint8_t i = 0; i <= size; i++){
		float f = 0.9;
		r *= f;
		g *= f;
		b *= f;
		Color darker = C_RGB(r, g, b);
		display->drawLine(x - i, y, x, y - i, darker);
		display->drawLine(x, y - i, x + i, y, darker);
		display->drawLine(x + i, y, x, y + i, darker);
		display->drawLine(x, y+i, x - i, y, darker);
	}
}
