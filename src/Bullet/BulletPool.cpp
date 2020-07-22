#include "BulletPool.h"
void SpaceRocks::BulletPool::create(float x, float y, float xVel, float yVel, uint lifetime)
{
	for(uint8_t i = 0; i < POOL_SIZE; i++)
	{
		if(!bullets[i].inUse())
		{
			bullets[i].init(x, y, xVel, yVel, lifetime);
			return;
		}
	}
}
void SpaceRocks::BulletPool::update(Sprite* canvas)
{
	for(uint8_t i = 0; i < POOL_SIZE; i++)
	{
		bullets[i].update(canvas);
	}
}
void SpaceRocks::BulletPool::draw(Sprite* canvas)
{
	for(uint8_t i = 0; i < POOL_SIZE; i++)
	{
		bullets[i].draw(canvas);
	}
}