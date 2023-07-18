#pragma once

struct Target {

	double x;
	double y;
	double d;
	double vx;
	double vy;

	void initTarget(double _x, double _y);
	void moveTarget();
};