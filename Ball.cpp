#include "Ball.h"

void Ball::setVelocityX(int x) {
	velocityX = x;
}
void Ball::setVelocityY(int y) {
	velocityY = y;
}
void Ball::setBallX(int x) {
	ball.x = x;
}
void Ball::setBallY(int y) {
	ball.y = y;
}
int Ball::getVelocityX() {
	return velocityX;
}
int Ball::getVelocityY() {
	return velocityY;
}
int Ball::getBallX() {
	return ball.x;
}
int Ball::getBallY() {
	return ball.y;
}
int Ball::getBallW() {
	return ball.w;
}
int Ball::getBallH() {
	return ball.h;
}
void Ball::setBall(int x, int y, int w, int h) {
	ball.x = x;
	ball.y = y;
	ball.w = w;
	ball.h = h;
}
SDL_Rect* Ball::getBall() {
	return &ball;
}
