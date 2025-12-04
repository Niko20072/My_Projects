#include "game.h"
#include "surface.h"
#include "template.h"
#include "windows.h"
#include <cstdio> //printf

namespace Tmpl8
{
	Surface tiles("assets/map.jpg");
	Sprite pacmanSprite(new Surface("assets/pacman.jpg"), 4);

	const int MapWidth = 24;
	const int MapHeight = 12;

	static char map[MapHeight][73] =
	{
		"aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa ",
		"aa baXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaX",
		"aa baXaa aa aa aa baXaa aa aa aa aa aa aa aa aa aa aa baXaa aa aa aa baX",
		"aa baXaa baXbaXaa baXaa baXbaXbaXbaXbaXbaXbaXbaXbaXaa baXaa baXbaXaa baX",
		"aa baXaa baXaa aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa baXaa baX",
		"aa baXaa baXaa baXbaXaa baXaa aa aa baXaa aa aa baXaa baXbaXaa baXaa baX",
		"aa baXaa aa aa aa aa aa baXaa aa aa baXaa aa aa baXaa aa aa aa aa aa baX",
		"aa baXaa baXaa baXbaXaa baXbaXbaXbaXbaXbaXbaXbaXbaXaa baXbaXaa baXaa baX",
		"aa baXaa baXaa aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa baXaa baX",
		"aa baXaa baXbaXaa baXaa baXbaXbaXbaXbaXbaXbaXbaXbaXaa baXaa baXbaXaa baX",
		"aa baXaa aa aa aa baXaa aa aa aa aa aa aa aa aa aa aa baXaa aa aa aa baX",
		"aa baXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaXbaX"
	};

	
	void DrawTile(int tx, int ty, Surface* screen, int x, int y)
	{
		Pixel* src = tiles.GetBuffer() + tx * 32 + ty * 32 * 64;
		Pixel* dst = screen->GetBuffer() + x + y * 800;
		for (int i = 0; i < 32; i++, src += 64, dst += 800)
			for (int j = 0; j < 32; j++)
				dst[j] = src[j];
	}

	void DrawMap(Surface* screen)// desenare hartă
	{
		for (int y = 0; y < MapHeight; y++)
			for (int x = 0; x < MapWidth; x++)
			{
				int tx = map[y][x * 3] - 'a';
				int ty = map[y][x * 3 + 1] - 'a';
				DrawTile(tx, ty, screen, x * 32, y * 32);
			}
	}

	bool MapIsBlocked(int x, int y)
	{
		int tx = x / 32;
		int ty = y / 32;
		if (tx < 0 || tx >= MapWidth || ty < 0 || ty >= MapHeight) return true; 
		return map[ty][tx * 3 + 2] == 'X';
		//true = blocat, false = liber
	}


	class PacMan
	{
	public:

		float speed;
		int direction;
		float x, y;
		
		PacMan(float ix, float iy, float ispeed = 1.5f, int idirection = 0)
		{
			x = ix;
			y = iy;
			direction = idirection;
			speed = ispeed;
		}

		void Draw(Surface* screen)
		{
			pacmanSprite.Draw(screen, (int)x, (int)y);
		}

		bool CheckMapCollision(int x, int y)// verifică coliziunea dreptunghiulară
		{
			// colțurile dreptunghiului
			//x si y este stanga sus la sprite
			int left = x;
			int top = y;
			int right = left + 16;
			int bottom = top + 16;

			// verificăm dacă vreun colț este blocat
			if (MapIsBlocked(left, top)) return false;      // stânga sus
			if (MapIsBlocked(right, top)) return false;     // dreapta sus
			if (MapIsBlocked(left, bottom)) return false;   // stânga jos
			if (MapIsBlocked(right, bottom)) return false;  // dreapta jos

			return true; // toate colțurile sunt libere, adică NU e coliziune
		}

		void Move()
		{
			float nx = x;
			float ny = y;
			if (GetAsyncKeyState('A')) nx -= speed, direction = 2;
			if (GetAsyncKeyState('D')) nx += speed, direction = 0;
			if (GetAsyncKeyState('W')) ny -= speed, direction = 1;
			if (GetAsyncKeyState('S')) ny += speed, direction = 3;
			pacmanSprite.SetFrame(direction);
			if (CheckMapCollision(nx, ny) == true) x = nx, y = ny;
			printf("PacMan position: (%.2f, %.2f)\n", nx, ny);
		}
		
	};

	class Enemy : public PacMan
	{
		public:
		Enemy(float ix, float iy, float ispeed = 1.0f, int idirection = 0) : PacMan(ix, iy, ispeed, idirection)
		{
		}
		void Move(PacMan* target)
		{
			float angle = ((2 * PI) / 4) * direction;
			float nx = x + (sinf(angle) * speed);
			float ny = y + (-cosf(angle) * speed);
			if (CheckMapCollision(nx, ny) == true) x = nx, y = ny;
		}
		void Think(PacMan* target)
		{
			frame_timer++;
			if (frame_timer >= 8)
			{
				//Current direction of the AITank
				int toright = direction + 1;
				if (toright > 4) toright = 0;
				float angle = ((2 * PI) / 4) * (float)toright;
				float ax = sinf(angle);
				float ay = -cosf(angle);
				//The direction of the target tank relative to this tank
				float bx = (target->x - x);
				float by = (target->y - y);
				float dot_result = ax * bx + ay * by;
				if (dot_result > 0.0f)
					this->direction;
				else
					this->direction;

				// Add error if player is far away
				float distance = sqrtf(bx * bx + by * by);//valoarea absoluta a distantei dintre cele 2 tancuri
				if (distance > 250)
				{
					int error = rand() % 4;
					direction = (direction + error) % 16;
				}


				frame_timer = 0;
			}
		}
		int frame_timer = 0;
	};


	PacMan pacman(392,135);
	Enemy enemy1(72, 69);

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
	}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		screen->Clear(0);
		DrawMap(screen);
		
		pacman.Draw(screen);
		pacman.Move();
		
		enemy1.Draw(screen);
		enemy1.Move(&pacman);
		//enemy1.Think(&pacman);
	}
};