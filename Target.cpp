#include "Target.h"
#include <math.h>

void Target::initTarget(double _x, double _y)
{
	x = _x;
	y = _y;

	d = sqrt((_x * _x) + (_y * _y));
	vx = (1 / d) * _x;
	vy = (1 / d) * _y;
}

void Target::moveTarget()
{
	x -= vx;
	y -= vy;
}