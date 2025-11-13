#include "tank.h"
#include "map.h"
#include <windows.h>
#include <iostream>

namespace Tmpl8
{
    Tank::Tank()
    {
        px = 800 / 2 - 16;// poziția tancului pe ecran/ 16 = jumătate din dimensiunea sprite-ului
        py = 512 / 2 - 16;
    }
    Tank::Tank(int startx, int starty)
    {
        px = startx;
        py = starty;
    }
    void Tank::UpdateAnimation(int& frame_number, int frames[])// actualizează animația tancului și turetei
    {
        if (frame_number > 30) tank.SetFrame(frames[0]);
        if (frame_number > 45) tank_gun.SetFrame(frames[0]);
        if (frame_number > 60) tank.SetFrame(frames[1]);
        if (frame_number > 75) tank_gun.SetFrame(frames[1]);
        if (frame_number > 90) tank.SetFrame(frames[2]);
        if (frame_number > 105) tank_gun.SetFrame(frames[2]), frame_number = 0;
        frame_number++;
    }
    bool Tank::CheckTankCollision(int x, int y, Map& map)// verifică coliziunea dreptunghiulară
    {
        // colțurile dreptunghiului
        int left = x + collisionOffsetX;
        int top = y + collisionOffsetY;
        int right = left + collisionWidth;
        int bottom = top + collisionHeight;

        // verificăm dacă vreun colț este blocat
        if (map.IsBlocked(left, top)) return false;      // stânga sus
        if (map.IsBlocked(right, top)) return false;     // dreapta sus
        if (map.IsBlocked(left, bottom)) return false;   // stânga jos
        if (map.IsBlocked(right, bottom)) return false;  // dreapta jos

        return true; // toate colțurile sunt libere, adică NU e coliziune
    }
    bool Tank::CheckTanktoTankCollision(int x, int y, Tank* tanks[], int tankCounter)
        {
            // hitbox pentru tancul curent (poziția nouă propusă)
            int leftA = x + collisionOffsetX;
            int topA = y + collisionOffsetY;
            int rightA = leftA + collisionWidth;
            int bottomA = topA + collisionHeight;

            for (int i = 0; i < tankCounter; i++)
            {
                Tank* otherTank = tanks[i];

                //tanks[i] → accesează tancul de la poziția i
                //& tanks[i] → ia adresa în memorie a acelui tanc
                //Tank* otherTank → declară un pointer la un Tank

                if (otherTank != this)// sărim peste noi înșine
                {
                    // hitbox pentru tancul celălalt
                    int leftB = otherTank->px + collisionOffsetX;
                    int topB = otherTank->py + collisionOffsetY;
                    int rightB = leftB + collisionWidth;
                    int bottomB = topB + collisionHeight;
                    // verificare coliziune dreptunghiulară
                    if (leftA < rightB && rightA > leftB && topA < bottomB && bottomA > topB)
                        return true;
                }
		    }
            return false;
        }
    void Tank::MoveRight(Surface* screen, Map& map, Tank* tanks[], int tankCount) //this is for fixed map
    {
        ///std::cout << "Drawing tank at: " << px << ", " << py << std::endl;
        tank.Draw(screen, px, py);
        tank_gun.Draw(screen, px, py);

        int nx = px;
        int ny = py;

        // verificăm dacă poate merge la dreapta
        if (CheckTankCollision(nx + 1, ny, map))
        {
            nx++; // mutare la dreapta
        }
        else
        {
            // dacă nu poate merge la dreapta, mutăm vertical
            if (py > 512 / 2) ok = 1; // jumătatea de jos a ecranului
            if (CheckTankCollision(nx, ny - 1, map) && ok == 1) // verificăm sus
                ny--; // mutare sus
            else ok = 0;
            if (CheckTankCollision(nx, ny + 1, map) && ok == 0) // verificăm jos
                ny++; // mutare jos
            else ok = 1;
        }

        if (CheckTanktoTankCollision(nx,ny,tanks,tankCount) == false)
        {
            px = nx;
            py = ny;
        }

        if (px == 729)
            px = 24;
        if (py == 8)
            py = 463;


        //std::cout << "newCameray + py: " << py << std::endl;
        //std::cout << "newCamerax + px: " << px << std::endl;
    }
    void Tank::Move(Surface* screen, Map& map)
    {
        std::cout << "Drawing tank at: " << px << ", " << py << std::endl;
        tank.Draw(screen, px, py);
        tank_gun.Draw(screen, px, py);

        int nx = px;
        int ny = py;
        // orizontala
        if (GetAsyncKeyState('A')) nx--, UpdateAnimation(frameA, framesA);// deplasare stânga
        if (GetAsyncKeyState('D')) nx++, UpdateAnimation(frameD, framesD);// deplasare dreapta
        // verticala
        if (GetAsyncKeyState('W')) ny--, UpdateAnimation(frameW, framesW);// deplasare sus
        if (GetAsyncKeyState('S')) ny++, UpdateAnimation(frameS, framesS);// deplasare jos
        // diagonala
        if (GetAsyncKeyState('W') && GetAsyncKeyState('A')) tank.SetFrame(14), tank_gun.SetFrame(14);
        if (GetAsyncKeyState('W') && GetAsyncKeyState('D')) tank.SetFrame(2), tank_gun.SetFrame(2);
        if (GetAsyncKeyState('S') && GetAsyncKeyState('A')) tank.SetFrame(10), tank_gun.SetFrame(10);
        if (GetAsyncKeyState('S') && GetAsyncKeyState('D')) tank.SetFrame(6), tank_gun.SetFrame(6);
        // verificare coliziuni
        if (CheckTankCollision(nx, ny, map) == true) px = nx, py = ny;//ma misc dacă nu e coliziune
        //std::cout << "py: " << py << std::endl;
        //std::cout << "px: " << px << std::endl;
    }
    

};