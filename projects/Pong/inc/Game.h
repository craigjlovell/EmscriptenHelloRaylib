#pragma once

class Ball;
class Paddle;


class Game
{
public:
	const int windowWidth = 800;
	const int windowHeight = 450;
	const char* windowTitle = "Hello Raylib";
	bool shouldQuit = false;

public:

	Game();
	~Game();

	void ResetBall();
	void ResetPaddle();

	void UpdateBall(Ball* b);
	void UpdatePaddle(Paddle* p);

	void PaddleCol(Paddle* p, Ball* b);

	void Load();
	void UnLoad();

	void Update();
	void UpdateGame();
	void Draw();

	void DrawBall(Ball* b);
	void DrawPaddle(Paddle* p);

protected:
private:

	Ball *m_ball = nullptr;
	Paddle *m_leftPaddle = nullptr;
	Paddle *m_rightPaddle = nullptr;

};