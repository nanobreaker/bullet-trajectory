#include <GL\glut.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <iostream>

#include "Bullet.h"
#include "Target.h"

using namespace std;

double PointX;
double PointY;
double MouseD;
double cosX;
double sinY;

vector<Bullet> bullets;
vector<Target> targets;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_LINES);
	glVertex2f(0,0);
	glVertex2f(cosX * 10, sinY * 10);
	glEnd();

	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPointSize(1);
	for(auto iter = bullets.begin(); iter != bullets.end(); ++iter)
	{
		glBegin(GL_POINTS);
		glColor3f(1, 1, 1);
		glVertex2f(iter -> x, iter -> y);
		glEnd();
	}

	glPointSize(5);
	for(auto iter = targets.begin(); iter != targets.end(); ++iter)
	{
		glBegin(GL_POINTS);
		glColor3f(1, 1, 1);
		glVertex2f(iter -> x, iter -> y);
		glEnd();
	}
	
	glutSwapBuffers();
}

void addBullet(int MouseX, int MouseY)
{
	Bullet b;
	b.initBullet(MouseX,MouseY);
	bullets.push_back(b);
}

void addRandomTarget()
{
	Target b;

	int angle = rand() % 361;
	b.initTarget(cos(angle) * 250, sin(angle) * 250);

	targets.push_back(b);
}

void addTarget(int MouseX, int MouseY)
{
	Target b;

	MouseX = MouseX - 250;
	MouseY = 250 - MouseY;

	b.initTarget(MouseX,MouseY);
	targets.push_back(b);
}

void MouseMove(int x, int y)
{
	PointX = x - 250;
	PointY = 250 - y;
}

void MovingTower(int x, int y)
{
	PointX = x - 250;
	PointY = 250 - y;
}

void MousePressed(int button, int state, int x, int y)
{
	switch(button)
	{
	case GLUT_LEFT_BUTTON: 
			switch(state)
			{
			case GLUT_UP: break;
			case GLUT_DOWN: addBullet(x, y);break;
			}
			break;
	case GLUT_MIDDLE_BUTTON: 
			switch(state)
			{
			case GLUT_UP: break;
			case GLUT_DOWN: break;
			}
			break;
	case GLUT_RIGHT_BUTTON: 
			switch(state)
			{
			case GLUT_UP: break;
			case GLUT_DOWN: addTarget(x, y); break;
			}
	}
}

void FirstTimer(int = 0)
{
	display();

	MouseD = sqrt( PointX * PointX + PointY * PointY );
	cosX = PointX / MouseD;
	sinY = PointY / MouseD;

	for(auto iter = bullets.begin(); iter != bullets.end();)
	{
		if( iter -> x > 250 || iter -> x < -250 || iter -> y > 250 || iter -> y < -250 ){
			iter = bullets.erase(iter);
		}else{
			iter -> moveBullet();
			++iter;
		}
	}

	for(auto iter = targets.begin(); iter != targets.end();)
	{
		if( iter -> x > 250 || iter -> x < -250 || iter -> y > 250 || iter -> y < -250 ){
			iter = targets.erase(iter);
		}else{
			iter -> moveTarget();
			++iter;
		}
	}

	for(auto iter_bullets = bullets.begin(); iter_bullets != bullets.end();	++iter_bullets)
	{
		for(auto iter_targets = targets.begin(); iter_targets != targets.end();)
		{
			if( (iter_bullets->x <= iter_targets->x + 5) && (iter_bullets->x >= iter_targets->x - 5) &&
				(iter_bullets->y < iter_targets->y + 5) && (iter_bullets->y > iter_targets->y - 5) )
			{
				iter_targets = targets.erase(iter_targets);
			}else{
				++iter_targets;
			}
		}
	}

	glutTimerFunc(10, FirstTimer, 0);
}

void SecondTimer(int = 1)
{
	addRandomTarget();
	glutTimerFunc(1000, SecondTimer, 1);
}

int main(int argc, char **argv)
{
	srand(time(NULL));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Bullet's trajectory");
	glClearColor(0, 0, 0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-250, 250, -250, 250, -1.0, 1.0);
	glutDisplayFunc(display);
	glutPassiveMotionFunc(MouseMove);
	glutMouseFunc(MousePressed);
	FirstTimer();
	SecondTimer();

	glutMainLoop();
}