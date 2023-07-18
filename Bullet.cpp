#include "Bullet.h"
#include <math.h>

void Bullet::initBullet(double _x, double _y)
{
	x = 0;
	y = 0;

	_x = _x - 250;
	_y = 250 - _y;

	d = sqrt((_x * _x) + (_y * _y));
	vx = (2 / d) * _x;
	vy = (2 / d) * _y;
}

void Bullet::moveBullet()
{
	x += vx;
	y += vy;
}