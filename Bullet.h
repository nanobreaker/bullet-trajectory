#pragma once

struct Bullet {

	double x;
	double y;
	double d;
	double vx;
	double vy;

	void initBullet(double _x, double _y);
	void moveBullet();
};