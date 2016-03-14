#include "Game.h"
Game::Game() {
	playGround.x = PLAY_GROUND_SIZE_X;
	playGround.y = PLAY_GROUND_SIZE_Y;
	playGround.w = PLAY_GROUND_SIZE_W;
	playGround.h = PLAY_GROUND_SIZE_H;
	pad1.setPadX(FIRST_PLAYER_X);
	pad1.setPadY(FIRST_PLAYER_Y);
	pad1.setPadW(PLAYER_PAD_W);
	pad1.setPadH(PLAYER_PAD_H);
	pad1.setPoints(0);
	pad2.setPadX(SECOND_PLAYER_X);
	pad2.setPadY(SECOND_PLAYER_Y);
	pad2.setPadW(PLAYER_PAD_W);
	pad2.setPadH(PLAYER_PAD_H);
	pad2.setPoints(0);
	ball.setBall(BALL_X, BALL_Y, BALL_W, BALL_H);
	ball.setVelocityX(BALL_VELOCITY_X);
	ball.setVelocityY(BALL_VELOCITY_Y);
	changeTime = 0;
}
void Game::runGame() {
	if (!initEverything())
		throw std::invalid_argument("Error: Initialize Everything");
	bool loop = true;
	while (loop) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				loop = false;
			else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_w:
					// ��� ������� ������� ������� �� ������� �����, ������� ���� �� ���� �� ����� �������
					if (ball.getBallX() > PLAY_GROUND_SIZE_X + PLAYER_PAD_W)
						pad1.changePadPositionY(
								pad1.getPadPositionY() - PLAYER_PAD_MOVE);
					break;
				case SDLK_s:
					// ��� ������� ������� ������� �� ������� �����, ������� ���� �� ���� �� ����� �������
					if (ball.getBallX() > PLAY_GROUND_SIZE_X + PLAYER_PAD_W)
						pad1.changePadPositionY(
								pad1.getPadPositionY() + PLAYER_PAD_MOVE);
					break;
				case SDLK_UP:
					// ��� ������� ������� ������� �� ������� �����, ������� ���� �� ���� �� ����� �������
					if (ball.getBallX() + ball.getBallW()
							< PLAY_GROUND_SIZE_X + PLAY_GROUND_SIZE_W
									- PLAYER_PAD_W && AI_ON_OFF == false)
						pad2.changePadPositionY(
								pad2.getPadPositionY() - PLAYER_PAD_MOVE);
					break;
				case SDLK_DOWN:
					// ��� ������� ������� ������� �� ������� �����, ������� ���� �� ���� �� ����� �������
					if (ball.getBallX() + ball.getBallW()
							< PLAY_GROUND_SIZE_X + PLAY_GROUND_SIZE_W
									- PLAYER_PAD_W && AI_ON_OFF == false)
						pad2.changePadPositionY(
								pad2.getPadPositionY() + PLAYER_PAD_MOVE);
					break;
				default:
					break;

				}
			}
		}
		if (AI_ON_OFF)
			AI();
		moveBall();
		render();
		SDL_Delay(16);
	}
}
bool Game::initEverything() {
	if (!initSDL())
		return false;
	if (!createWindow())
		return false;
	if (!createRenderer())
		return false;
	if (!initTTF())
		return false;
	setupRenderer();
	return true;
}
bool Game::initSDL() {
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		throw std::invalid_argument("Error: Failed to initialize SDL");
	}

	return true;
}
bool Game::createWindow() {
	window = SDL_CreateWindow("Pong Game", WINDOW_POSITION_X, WINDOW_POSITION_Y,
	WINDOW_SIZE_X, WINDOW_SIZE_Y, 0);
	if (window == NULL) {
		throw std::invalid_argument("Error: Failed to create window");
	}

	return true;
}
bool Game::createRenderer() {
	renderer = SDL_CreateRenderer(window, -1, 0);

	if (renderer == NULL) {
		throw std::invalid_argument("Error: Failed to create renderer");
	}

	return true;
}
void Game::setupRenderer() {
	SDL_RenderSetLogicalSize(renderer, WINDOW_SIZE_X, WINDOW_SIZE_Y);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
bool Game::initTTF() {
	if (TTF_Init() == -1) {
		throw std::invalid_argument("Error: Failed to initialize TTF");
	}
	return true;
}
void Game::renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y) {
	// �������� ��������� �� ������������� � ����� �� �� ������� ���������
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	// ������� ��������� � ���������� �� ������
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL, &dst);
}
SDL_Texture* Game::renderText(const char* message, const char* fontFile,
		SDL_Color color, int fontSize, SDL_Renderer *renderer) {
	// ��������� ������
	TTF_Font *font = TTF_OpenFont(fontFile, fontSize);

	SDL_Surface *surf = TTF_RenderText_Blended(font, message, color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);

	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	return texture;
}
char* Game::convertResultToChar() { // ������������ ��������� �� int �� char, ����� �� �������
	char* toShow = new char[8];
	int fPlayerPoints[3] = { -1, -1, 0 }, sPlayerPoints[3] = { -1, -1, 0 }, num1,
			num2, fCount = 0, sCount = 0;
	num1 = pad1.getPoints();
	num2 = pad2.getPoints();
	for (int i = 2; i >= 0; i--) {
		if (num1 != 0) {
			fPlayerPoints[i] = num1 % 10;
			num1 /= 10;
		}
		if (num2 != 0) {
			sPlayerPoints[i] = num2 % 10;
			num2 /= 10;
		}
	}
	for (int i = 0; i < 3; i++) {
		if (fPlayerPoints[i] != -1)
			toShow[i] = (char) fPlayerPoints[i] + (char) '0';
		else
			toShow[i] = ' ';
	}
	toShow[3] = ':';
	for (int i = 4; i < 7; i++) {
		if (sPlayerPoints[i - 4] != -1)
			toShow[i] = (char) sPlayerPoints[i - 4] + (char) '0';
		else
			toShow[i] = ' ';
	}
	toShow[7] = '\0';
	return toShow;
}
void Game::showResult(int x, int y) {
	char* result = convertResultToChar();
	SDL_Color color = { 255, 255, 255, 255 };
	SDL_Texture *image = renderText(result, PATH_TO_FONTFILE, color, 20,
			renderer);
	renderTexture(image, renderer, x, y);
	delete[] result;
}
void Game::render() {
	SDL_RenderClear(renderer); // ���������� �������
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // �������� ����� ����
	SDL_RenderDrawRect(renderer, &playGround); // �������� ����������� �� ������
	SDL_RenderFillRect(renderer, pad1.getPad()); // �������� ������� �� ������ �����
	SDL_RenderFillRect(renderer, pad2.getPad()); // �������� ������� �� ������ �����
	SDL_RenderFillRect(renderer, ball.getBall()); // �������� �������
	showResult(RESULT_X, RESULT_Y); // �������� ���������
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // �������� ����� ����
	SDL_RenderPresent(renderer); // ��������� ������
}
void Game::moveBall() {
	if (ball.getBallY()
			+ ball.getBallH()>=PLAY_GROUND_SIZE_Y+PLAY_GROUND_SIZE_H) { // �������� �� ������
		ball.setVelocityY(ball.getVelocityY() * (-1));
	}
	if (ball.getBallY() <= PLAY_GROUND_SIZE_Y) { // �������� �� ������
		ball.setVelocityY(ball.getVelocityY() * (-1));
	}
	// �������� �� �� ������� �� ������ ����� ��� ������ �������� �����
	if (ball.getBallX()
			+ ball.getBallW()>=PLAY_GROUND_SIZE_X+PLAY_GROUND_SIZE_W-PLAYER_PAD_W) {
		if (ball.getBallY()+ball.getBallH()
				>= pad2.getPadPositionY() && ball.getBallY()<=pad2.getPadPositionY()+PLAYER_PAD_H) {
			ball.setVelocityX(ball.getVelocityX() * (-1));
		} else if (ball.getBallX()
				+ ball.getBallW()>PLAY_GROUND_SIZE_X+PLAY_GROUND_SIZE_W-BALL_VELOCITY_X) {
			pad1.setPoints(pad1.getPoints() + 1);
			reset();
		}
	}
	// �������� �� �� ������� �� ������ ����� ��� ������ �������� �����
	if (ball.getBallX() <= PLAY_GROUND_SIZE_X + PLAYER_PAD_W) {
		if (ball.getBallY()+ball.getBallH()
				>= pad1.getPadPositionY() && ball.getBallY()<=pad1.getPadPositionY()+PLAYER_PAD_H) {
			ball.setVelocityX(ball.getVelocityX() * (-1));
		} else if (ball.getBallX() < PLAY_GROUND_SIZE_X + BALL_VELOCITY_X) {
			pad2.setPoints(pad2.getPoints() + 1);
			reset();
		}
	}
	ball.setBallX(ball.getBallX() + ball.getVelocityX());
	ball.setBallY(ball.getBallY() + ball.getVelocityY());
}
int Game::oneOrMinusOneNumber() { // ����� -1 ��� 1
	int number;
	srand(time(NULL));
	number = rand() % 2 + 0; // ����� ���������� ����� � ��������� [0,1]
	if (number == 1)
		return 1;
	else
		return -1;
}
void Game::reset() { // ������� 2 ������� � ����� ������� � ������� ������� � ���������� ������

	SDL_Delay(2000);
	ball.setBall(BALL_X, BALL_Y, BALL_W, BALL_H);
	ball.setVelocityX(BALL_VELOCITY_X * oneOrMinusOneNumber());
	ball.setVelocityY(BALL_VELOCITY_Y * oneOrMinusOneNumber());
}
void Game::AI() { // ��������� �������� ��������� ������� �����
	int number;
	srand(time(NULL) + changeTime);
	changeTime++;
	number = rand() % 101 + 1; // random number from 1 to 100
	if (number <= AI_level) {
		if (ball.getBallY() > (pad2.getPadPositionY() + PLAYER_PAD_H / 2))
			pad2.changePadPositionY(pad2.getPadPositionY() + BALL_VELOCITY_Y);
		else
			pad2.changePadPositionY(pad2.getPadPositionY() - BALL_VELOCITY_Y);
	}
}

