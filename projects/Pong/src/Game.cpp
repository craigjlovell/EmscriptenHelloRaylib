#include "Game.h"
#include "raylib.h"
#include "Ball.h"
#include "Paddle.h"



Game::Game()
{
	
}

Game::~Game()
{

}

void Game::ResetBall()
{
	m_ball->pos.x = windowWidth / 2;
	m_ball->pos.y = windowHeight / 2;
}

void Game::ResetPaddle()
{
    m_leftPaddle->pos.x = 50;
    m_leftPaddle->pos.y = windowHeight / 2.0f;

    m_rightPaddle->pos.x = windowWidth - 50;
    m_rightPaddle->pos.y = windowHeight / 2.0f;
}

void Game::UpdateBall()
{
    m_ball->pos.x += m_ball->dir.x * m_ball->speed;
    m_ball->pos.y -= m_ball->dir.y * m_ball->speed;

    if (m_ball->pos.x < 0)
    {
        ResetBall();

        m_rightPaddle->score += 1;

        if (m_rightPaddle->score >= 5)
        {
            m_rightPaddle->score = 0;
            ResetPaddle();
        }

    }
    if (m_ball->pos.x > windowWidth)
    {
        ResetBall();

        m_leftPaddle->score += 1;

        if (m_leftPaddle->score >= 5)
        {
            m_leftPaddle->score = 0;
            ResetPaddle();
        }
    }
    if (m_ball->pos.y < 0)       m_ball->dir.y = -m_ball->dir.y;
    if (m_ball->pos.y > windowHeight) m_ball->dir.y = -m_ball->dir.y;

}



void Game::Load()
{
	m_ball = new Ball();
	ResetBall();
	m_ball->dir.x = 1;
	m_ball->dir.y = 1;

    m_leftPaddle = new Paddle();
    m_leftPaddle->pos.x = 50;
    m_leftPaddle->pos.y = windowHeight / 2.0f;
    m_leftPaddle->upKey = KEY_W;
    m_leftPaddle->downKey = KEY_S;

    m_rightPaddle = new Paddle();
    m_rightPaddle->pos.x = windowWidth - 50;
    m_rightPaddle->pos.y = windowHeight / 2.0f;
    m_rightPaddle->upKey = KEY_UP;
    m_rightPaddle->downKey = KEY_DOWN;
}

void Game::UnLoad()
{
    delete m_ball;
    m_ball = nullptr;

    delete m_leftPaddle;
    m_leftPaddle = nullptr;

    delete m_rightPaddle;
    m_rightPaddle = nullptr;
}

void Game::Update()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);

    UpdateBall();
	DrawFPS(10, 10);

	EndDrawing();
}

void Game::Draw()
{
    DrawBall(m_ball);
    DrawPaddle(m_leftPaddle);
    DrawPaddle(m_rightPaddle);
}

void Game::DrawBall(Ball* b)
{

	DrawCircle((int)b->pos.x, (int)b->pos.y, b->radius, RED);
}

void Game::DrawPaddle(Paddle* p)
{
    DrawRectangle(p->pos.x, p->pos.y, 10, 100, GOLD);
}

