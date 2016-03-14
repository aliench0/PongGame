#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED
#include<SDL.h>
#include "Const.h"

class Ball {
private:
	int velocityX; // скорост на топчето по Х
	int velocityY; // скорост на топчето по У
	SDL_Rect ball; // правоъгълник - топчето

public:
	void setVelocityX(int);
	void setVelocityY(int);
	void setBallX(int);
	void setBallY(int);
	int getVelocityX();
	int getVelocityY();
	int getBallX();
	int getBallY();
	int getBallW();
	int getBallH();
	void setBall(int, int, int, int);
	SDL_Rect* getBall();

};

#endif // BALL_H_INCLUDED
