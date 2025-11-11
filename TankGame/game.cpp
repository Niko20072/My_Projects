#include "game.h"
#include "surface.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#define MapWidth 51
#define MapHeight 35

namespace Tmpl8
{
    Surface tiles("assets/nc2tiles.png");
    Sprite tank(new Surface("assets/ctankbase.tga"), 16);
    Sprite tank_gun(new Surface("assets/ctankgun.tga"), 16);

    const int screenWidth = 800;
    const int screenHeight = 512;

    int mapWidth = MapWidth; // lățimea hărții în tile-uri
    int mapHeight = MapHeight; // înălțimea hărții în tile-uri

    int cameraX = 0, cameraY = 0; // offset-ul hărții (cât s-a "mutat" harta pe ecran)

    int px = screenWidth / 2 - 16, py = screenHeight / 2 - 16;// poziția tancului pe ecran/ 16 = jumătate din dimensiunea sprite-ului

    // offset pentru centrare hartă (offset (de câţi pixeli trebuie să sari))
    int offsetX = (800 - mapWidth * 32) / 2; // offset pentru centrare pe X
    int offsetY = (512 - mapHeight * 32) / 2; // offset pentru centrare pe Y

    // hitbox tanc
    int collisionWidth = 30;// dimensiunea dreptunghiului de coliziune
    int collisionHeight = 24;
    int collisionOffsetX = 8; // cât să sară de la marginea sprite-ului/decalajul dreptunghiului față de sprite
    int collisionOffsetY = 8; // hitbox

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

    void Game::Init()
    {

    }
    void Game::Shutdown() {}

    char map[MapHeight][157] = {
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXhfXeeXdeXmeXneXoeXeeXdaXfb-fb-adXfb-fb-mbXndXndXndXnbXfb-fb-fb-mbXndXndXndXnbXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXfb-fb-fb-fb-fb-fb-fb-cbXfb-fb-cbXfb-fb-mcXpcXpcXpcXncXfb-fb-fb-mcXpcXpcXpcXncXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXfb-adXfb-fb-fb-fb-fb-cbXfb-fb-qaXfb-fb-mcXpcXmfXpcXncXfb-fb-fb-mcXpcXmfXpcXncXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXfb-abXga-ia-ha-deXeeXdcXfb-fb-fb-fb-fb-mcXpcXpcXpcXncXfb-fb-fb-mcXpcXpcXpcXncXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXfb-qaXfb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-mdXmeXneXoeXodXfb-fb-fb-mdXmeXneXoeXodXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXfb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-ec-fe-fe-fd-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXfb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fa-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXfb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fa-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-ff-kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXfb-fb-fb-fb-fb-fb-fb-fb-kcXkcXfe-fe-fd-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
        "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcXkcX"
    };

    void Game::DrawTile(int tx, int ty, Surface* screen, int x, int y)
    {
        // dimensiuni tile
        int sx = 0, sy = 0;       // offset în tile (punctul de start din tile)
        int w = 32, h = 32;       // dimensiune de copiat

        // clipping stânga/ sus: dacă tile începe în afara ecranului
        if (x < 0) sx = -x, w -= sx, x = 0;
        if (y < 0) sy = -y, h -= sy, y = 0;

        // clipping dreapta / jos
        if (x + w > 800) w = 800 - x;
        if (y + h > 512) h = 512 - y;

        // tile complet în afara -> nu desenăm nimic
        if (w <= 0 || h <= 0) return;

        // pointer la colțul tile-ului în imaginea tiles (1 px margin)
        Pixel* src = tiles.GetBuffer() + 1 + tx * 33 + (1 + ty * 33) * 595;

        // mutăm pointerul src la (sx, sy) din tile
        src += sy * 595 + sx;

        Pixel* dst = screen->GetBuffer() + x + y * 800;
        for (int i = 0; i < h; i++, src += 595, dst += 800)// 595 pitch în imaginea tiles (a ta), 800 pitch ecran
            for (int j = 0; j < w; j++)
                dst[j] = src[j];// copiem pixelii tile-ului pe ecran
    }

    /*
    void Game::DrawTile(int tx, int ty, Surface* screen, int x, int y)
    {
        // adresă sursă (tile) și pitch-uri
        Pixel* srcBuf = tiles.GetBuffer();//începutul imaginii cu tile-urile (595px lățime)
        Pixel* dstBuf = screen->GetBuffer();//începutul ecranului (800px lățime)
        const int srcPitch = 595; // pitch în imaginea tiles (a ta)
        const int dstPitch = 800; // pitch ecran
        // pointer la colțul tile-ului în imaginea tiles (1 px margin)
        Pixel* src = srcBuf + 1 + tx * 33 + (1 + ty * 33) * srcPitch;

        // dimensiuni tile
        int sx = 0, sy = 0;       // offset în tile (punctul de start din tile)
        int w = 32, h = 32;       // dimensiune de copiat

        // clipping stânga/ sus: dacă tile începe în afara ecranului
        if (x < 0) { sx = -x; w -= sx; x = 0; }
        if (y < 0) { sy = -y; h -= sy; y = 0; }

        // clipping dreapta / jos
        if (x + w > screenWidth) w = screenWidth - x;
        if (y + h > screenHeight) h = screenHeight - y;

        // dacă nu rămâne nimic de desenat, pleacă
        if (w <= 0 || h <= 0) return;

        // mutăm pointerul src la (sx, sy) din tile
        src += sy * srcPitch + sx;

        // pointer dest la (drawX, drawY) pe ecran
        Pixel* dst = dstBuf + x + y * dstPitch;

        // copiem rând cu rând doar lățimea w
        for (int row = 0; row < h; row++)
        {
            // copie element cu element (poți folosi memcpy dacă preferi)
            for (int col = 0; col < w; col++) dst[col] = src[col];
            src += srcPitch;
            dst += dstPitch;
        }
    }

    void Game::DrawTile2(int tx, int ty, Surface* screen, int x, int y)// desenează un tile specific
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
    }*/

    bool Game::CheckTankCollision(int x, int y)// verifică coliziunea dreptunghiulară
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

        return true; // toate colțurile sunt libere, adică NU e coliziune
    }

    void Game::UpdateAnimation(int& frame_number, int frames[])// actualizează animația tancului și turetei
    {
        if (frame_number > 30) tank.SetFrame(frames[0]);
        if (frame_number > 45) tank_gun.SetFrame(frames[0]);
        if (frame_number > 60) tank.SetFrame(frames[1]);
        if (frame_number > 75) tank_gun.SetFrame(frames[1]);
        if (frame_number > 90) tank.SetFrame(frames[2]);
        if (frame_number > 105) tank_gun.SetFrame(frames[2]), frame_number = 0;
        frame_number++;
    }

    void Game::DrawMap()// desenare hartă
    {
        for (int y = 0; y < MapHeight; y++)
            for (int x = 0; x < MapWidth; x++)
            {
                int tx = map[y][x * 3] - 'a';
                int ty = map[y][x * 3 + 1] - 'a';
                DrawTile(tx, ty, screen, x * 32 - cameraX + offsetX, y * 32 - cameraY + offsetY);
            }
    }

    void Game::Tick(float deltaTime)
    {

        screen->Clear(0);
        DrawMap();

        // desenare sprite
        tank.Draw(screen, px, py);
        tank_gun.Draw(screen, px, py);

        int newCameraX = cameraX;
        int newCameraY = cameraY;

        // orizontala
        if (GetAsyncKeyState('A')) newCameraX--, UpdateAnimation(frameA, framesA);// deplasare stânga
        if (GetAsyncKeyState('D')) newCameraX++, UpdateAnimation(frameD, framesD);// deplasare dreapta
        // verticala
        if (GetAsyncKeyState('W')) newCameraY--, UpdateAnimation(frameW, framesW);// deplasare sus
        if (GetAsyncKeyState('S')) newCameraY++, UpdateAnimation(frameS, framesS);// deplasare jos
        // diagonala
        if (GetAsyncKeyState('W') && GetAsyncKeyState('A')) tank.SetFrame(14), tank_gun.SetFrame(14);
        if (GetAsyncKeyState('W') && GetAsyncKeyState('D')) tank.SetFrame(2), tank_gun.SetFrame(2);
        if (GetAsyncKeyState('S') && GetAsyncKeyState('A')) tank.SetFrame(10), tank_gun.SetFrame(10);
        if (GetAsyncKeyState('S') && GetAsyncKeyState('D')) tank.SetFrame(6), tank_gun.SetFrame(6);
        // verificare coliziuni
        if (CheckTankCollision(newCameraX + px, newCameraY + py) == true) cameraX = newCameraX, cameraY = newCameraY;//ma misc dacă nu e coliziune
    }
};
