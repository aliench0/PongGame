#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <stdexcept>
#include <cstdlib>
#include <SDL.h>
#include <SDL_ttf.h>
#include <time.h>
#include "Const.h"
#include "PlayerPad.h"
#include "Ball.h"

class Game {
private:
	SDL_Window* window; // �������� ��� ���������
	SDL_Renderer* renderer; // �������� ��� �������
	SDL_Rect playGround; // ������������ - ��������� ����
	PlayerPad pad1; // ������� �� ������ �����
	PlayerPad pad2; // ������� �� ������ �����
	Ball ball; // �������
	int changeTime; // ������� ������� ��� ��������� �� ���������� �����

	bool initEverything();
	bool initSDL();
	bool createWindow();
	bool createRenderer();
	void setupRenderer();
	bool initTTF();
	void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
	SDL_Texture* renderText(const char* message, const char* fontFile,
			SDL_Color color, int fontSize, SDL_Renderer *renderer);
	char* convertResultToChar();
	void showResult(int, int);
	void render();
	void moveBall();
	int oneOrMinusOneNumber();
	void reset();
	void AI();

public:
	Game();
	void runGame();
};

#endif // GAME_H_INCLUDED
