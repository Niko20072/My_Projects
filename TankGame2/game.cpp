#include "game.h"
#include "surface.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#define MapWidth 25
#define MapHeight 16
#include <iostream>
#include "template.h"
#include "tank.h"
#include "map.h"

namespace Tmpl8
{
    Tank mytank;
	Map mymap;
    Tank* MyTanks[5];

    void Game::Init()
    {
        srand(time(0));
        int tileSize = 32;// Dimensiunea unui tile (pătrat din hartă)
        int occupied[MapHeight][MapWidth] = { 0 }; // 0 = liber, 1 = ocupat
        int tileX, tileY;

        for (int i = 0; i < 5; i++)
        {
            int startX, startY;
            bool valid = false;// variabilă care indică dacă poziția aleasă e validă
            do// Continuăm să generăm o poziție până găsim una validă (fără coliziune)
            {
                // Alegem o poziție aleatorie în coordonate de tile-uri
                tileX = IRand(MapWidth);
                tileY = IRand(MapHeight);

                // Convertim tile-urile în coordonate reale (pixeli)
                startX = tileX * tileSize;
                startY = tileY * tileSize;

                // Creăm un tanc temporar la poziția respectivă
                Tank testTank(startX, startY);

                // Verificăm dacă acest tanc se ciocnește cu ceva (perete, obstacol etc.)
                valid = testTank.CheckTankCollision(startX, startY, mymap) && (occupied[tileY][tileX] == 0);
            } while (!valid); //dacă nu e valid, repetăm procesul cu altă poziție

            MyTanks[i] = new Tank(startX, startY);// Dacă am găsit o poziție bună, creăm tancul real și îl salvăm în listă
            occupied[tileY][tileX] = 1; // marcăm tile-ul ca ocupat
        }
    }

    void Game::Shutdown() 
    {
        for (int i = 0; i < 5; i++) delete MyTanks[i];
    }

    void Game::Tick(float deltaTime)
    {
        screen->Clear(0);
        mymap.DrawMap(screen);
        for(int i=0; i<5; i++)
            MyTanks[i]->MoveRight(screen,mymap);
    }
};
