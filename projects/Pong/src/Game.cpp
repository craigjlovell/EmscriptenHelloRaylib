#include "Game.h"
#include "raylib.h"
#include "raymath.h"
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

void Game::PaddleCol(Paddle* p, Ball* b)
{
    float top = p->pos.y - 100 / 2;
    float bottom = p->pos.y + 100 / 2;
    float right = p->pos.x + 10 / 2;
    float left = p->pos.x - 10/ 2;

    if (b->pos.y >= top && b->pos.y <= bottom && b->pos.x >= left && b->pos.x <= right)
    {

        b->dir.x = -b->dir.x;
        b->speed = b->speed * 1.05f;

    }
}

void Game::UpdateBall(Ball* b)
{
    b->pos.x += b->dir.x * b->speed;
    b->pos.y -= b->dir.y * b->speed;

    if (b->pos.x < 0)
    {
        ResetBall();

        m_rightPaddle->score += 1;

        if (m_rightPaddle->score >= 5)
        {
            m_rightPaddle->score = 0;
            ResetPaddle();
        }

    }
    if (b->pos.x > windowWidth)
    {
        ResetBall();

        m_leftPaddle->score += 1;

        if (m_leftPaddle->score >= 5)
        {
            m_leftPaddle->score = 0;
            ResetPaddle();
        }
    }
    if (b->pos.y < 0)       b->dir.y = -b->dir.y;
    if (b->pos.y > windowHeight) b->dir.y = -b->dir.y;

}

void Game::UpdatePaddle(Paddle* p)
{
    if (IsKeyDown(p->upKey))
    {
        p->pos.y -= p->speed;
    }

    if (IsKeyDown(p->downKey))
    {
        p->pos.y += p->speed;
    }
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
	ClearBackground(SKYBLUE);

    UpdateGame();
	DrawFPS(10, 10);

	EndDrawing();
}

void Game::UpdateGame()
{
    UpdateBall(m_ball);
    UpdatePaddle(m_leftPaddle);
    UpdatePaddle(m_rightPaddle);
    PaddleCol(m_leftPaddle, m_ball);
    PaddleCol(m_rightPaddle, m_ball);
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
    
    Rectangle dstRect = { p->pos.x, p->pos.y, 10, 100 };
    Vector2 origin = { dstRect.width / 2, dstRect.height / 2 };
    DrawRectanglePro(dstRect, origin, 0.0f, GOLD);
}

