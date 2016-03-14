#include "PlayerPad.h"

void PlayerPad::changePadPositionY(int y) {
	if (y >= PLAY_GROUND_SIZE_Y
			&& y <= PLAY_GROUND_SIZE_Y + PLAY_GROUND_SIZE_H - pad.h)
		pad.y = y;
}
int PlayerPad::getPadPositionY() {
	return pad.y;
}
void PlayerPad::setPadX(int x) {
	pad.x = x;
}
void PlayerPad::setPadY(int y) {
	pad.y = y;
}
void PlayerPad::setPadW(int w) {
	pad.w = w;
}
void PlayerPad::setPadH(int h) {
	pad.h = h;
}
void PlayerPad::setPoints(int p) {
	points = p;
}
int PlayerPad::getPoints() {
	return points;
}
SDL_Rect* PlayerPad::getPad() {
	return &pad;
}
