#include "game.h"
#include "surface.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#define MapWidth 10
#define MapHeight 11

namespace Tmpl8
{
    Surface tiles("assets/nc2tiles.png");
    Sprite tank(new Surface("assets/ctankbase.tga"), 16);
    Sprite tank_gun(new Surface("assets/ctankgun.tga"), 16);

    int mapWidth = MapWidth; // lățimea hărții în tile-uri
    int mapHeight = MapHeight; // înălțimea hărții în tile-uri

    int px = 0, py = 0;// poziția tancului pe ecran

    int offsetX = (800 - mapWidth * 32) / 2; // offset pentru centrare pe X
    int offsetY = (480 - mapHeight * 32) / 2; // offset pentru centrare pe Y

    int collisionWidth = 30;// dimensiunea dreptunghiului de coliziune
    int collisionHeight = 24;
    int collisionOffsetX = 8; // cât să sară de la marginea sprite-ului/decalajul dreptunghiului față de sprite
    int collisionOffsetY = 8;

    int frameA = 0, frameD = 0, frameW = 0, frameS = 0;// contor pentru animații
    // frame-urile pentru fiecare direcție
    int framesA[] = { 12, 13, 11 };
    int framesD[] = { 4, 5, 3 };
    int framesW[] = { 0, 1, 15 };
    int framesS[] = { 8, 9, 7 };
    int framesWA[] = { 14, 15, 13 };
    int framesWD[] = { 2, 3, 1 };
    int framesSA[] = { 10, 11, 9 };
    int framesSD[] = { 6, 7, 5 };

    void Game::Init() {}
    void Game::Shutdown() {}
    
    char map[MapHeight][31] = {
        "kc-kc-kc-kc-kc-kc-kc-kc-kc-kc-",
        "kc-fbXfbXfbXkc-kc-kc-kc-kc-kc-",
        "kc-fbXfbXfbXfbXfbXkc-kc-kc-kc-",
        "kc-lc-lc-fbXfbXfbXkc-kc-kc-kc-",
        "kc-kc-kc-lc-lc-lc-kc-kc-kc-kc-",
        "kc-kc-kc-kc-kc-kc-kc-kc-kc-kc-",
        "kc-kc-kc-kc-kc-kc-kc-kc-kc-kc-",
        "kc-kc-kc-kc-kc-kc-kc-kc-kc-kc-",
        "kc-kc-kc-kc-kc-kc-kc-kc-kc-kc-",
        "kc-kc-kc-kc-kc-kc-kc-kc-kc-kc-",
        "kc-kc-kc-kc-kc-kc-kc-kc-kc-kc-"
    };

    void Game::DrawTile(int tx, int ty, Surface* screen, int x, int y)// desenează un tile specific
    {
        Pixel* src = tiles.GetBuffer() + 1 + tx * 33 + (1 + ty * 33) * 595;// calculăm buffer-ul sursă și destinație
        Pixel* dst = screen->GetBuffer() + x + y * 800;
        for (int i = 0; i < 32; i++, src += 595, dst += 800)
            for (int j = 0; j < 32; j++)
                dst[j] = src[j];// copiem pixelii tile-ului pe ecran
    }

    bool Game::CheckPos(int x, int y)// verifică dacă poziția nu atinge tile blocat
    {
        int tx = (x - offsetX) / 32;
        int ty = (y - offsetY) / 32;
        return map[ty][tx * 3 + 2] != 'X';
    }

    bool Game::CheckRectCollision(int x, int y)// verifică coliziunea dreptunghiulară
    {
        // colțurile dreptunghiului
        int left = x + collisionOffsetX;
        int top = y + collisionOffsetY;
        int right = left + collisionWidth;
        int bottom = top + collisionHeight;

        // transformăm coordonatele în tile-uri
        int tx1 = (left - offsetX) / 32;//stanga sus
        int ty1 = (top - offsetY) / 32;
        int tx2 = (right - offsetX) / 32;//dreapta jos
        int ty2 = (bottom - offsetY) / 32;

        // verificăm colțurile
		if (map[ty1][tx1 * 3 + 2] == 'X') return false;//stanga sus
		if (map[ty1][tx2 * 3 + 2] == 'X') return false;//dreapta sus
		if (map[ty2][tx1 * 3 + 2] == 'X') return false;//stanga jos
		if (map[ty2][tx2 * 3 + 2] == 'X') return false;//dreapta jos

        return true; // toate colțurile sunt libere
    }
    
    void Game::UpdateAnimation(int& frame_number,int frames[])// actualizează animația tancului și turetei
    {
        if (frame_number > 30) tank.SetFrame(frames[0]);
        if (frame_number > 45) tank_gun.SetFrame(frames[0]);
        if (frame_number > 60) tank.SetFrame(frames[1]);
        if (frame_number > 75) tank_gun.SetFrame(frames[1]);
        if (frame_number > 90) tank.SetFrame(frames[2]);
        if (frame_number > 105) tank_gun.SetFrame(frames[2]), frame_number = 0;
        frame_number++;
    }

    void Game::Tick(float deltaTime)
    {
        screen->Clear(0);
        for (int y = 0; y < MapHeight; y++)
            for (int x = 0; x < MapWidth; x++)
            {
                int tx = map[y][x * 3] - 'a';
                int ty = map[y][x * 3 + 1] - 'a';
                DrawTile(tx, ty, screen, x * 32 + offsetX, y * 32 + offsetY);
            }
        tank.Draw(screen, px, py);
        tank_gun.Draw(screen, px, py);
        int nx = px, ny = py;// poziții noi calculate
        // orizontala
        if (GetAsyncKeyState('A')) nx--, UpdateAnimation(frameA, framesA);// deplasare stânga
        if (GetAsyncKeyState('D')) nx++, UpdateAnimation(frameD, framesD);// deplasare dreapta
        if (CheckRectCollision(nx, py)) // doar Y rămâne aceeași
            px = nx;// aplică coliziunea orizontală
		// verticala
        if (GetAsyncKeyState('W')) ny--, UpdateAnimation(frameW, framesW);// deplasare sus
        if (GetAsyncKeyState('S')) ny++, UpdateAnimation(frameS, framesS);// deplasare jos
        if (CheckRectCollision(px, ny)) // folosim px actualizat
            py = ny;// aplică coliziunea verticală
		// diagonala
        if (GetAsyncKeyState('W') && GetAsyncKeyState('A')) tank.SetFrame(14), tank_gun.SetFrame(14);
        if (GetAsyncKeyState('W') && GetAsyncKeyState('D')) tank.SetFrame(2), tank_gun.SetFrame(2);
        if (GetAsyncKeyState('S') && GetAsyncKeyState('A')) tank.SetFrame(10), tank_gun.SetFrame(10);
		if (GetAsyncKeyState('S') && GetAsyncKeyState('D')) tank.SetFrame(6), tank_gun.SetFrame(6);
    }
};