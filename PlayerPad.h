#ifndef PLAYERPAD_H_INCLUDED
#define PLAYERPAD_H_INCLUDED
#include <SDL.h>
#include "Const.h"

class PlayerPad {
private:
	int points; // точки на играча
	SDL_Rect pad; // правоъгълник - дъска на играча

public:
	void changePadPositionY(int);
	int getPadPositionY();
	void setPadX(int);
	void setPadY(int);
	void setPadW(int);
	void setPadH(int);
	void setPoints(int);
	int getPoints();
	SDL_Rect* getPad();
};

#endif // PLAYERPAD_H_INCLUDED
