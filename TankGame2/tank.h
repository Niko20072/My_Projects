#pragma once
#include "surface.h"
#include "map.h"

namespace Tmpl8
{
    class Tank
    {
    public:
        Sprite tank = Sprite(new Surface("assets/ctankbase.tga"), 16);
        Sprite tank_gun = Sprite(new Surface("assets/ctankgun.tga"), 16);

        // hitbox tanc
        int collisionWidth = 30;// dimensiunea dreptunghiului de coliziune
        int collisionHeight = 24;
        int collisionOffsetX = 8; // cât să sară de la marginea sprite-ului/decalajul dreptunghiului față de sprite
        int collisionOffsetY = 8; // hitbox

        int frameA = 0, frameD = 0, frameW = 0, frameS = 0;// contor pentru animații

        // frame-urile pentru fiecare direcție
        int framesA[3] = { 12, 13, 11 };
        int framesD[3] = { 4, 5, 3 };
        int framesW[3] = { 0, 1, 15 };
        int framesS[3] = { 8, 9, 7 };
        int framesWA[3] = { 14, 15, 13 };
        int framesWD[3] = { 2, 3, 1 };
        int framesSA[3] = { 10, 11, 9 };
        int framesSD[3] = { 6, 7, 5 };

        int px, py;

        int ok = 0;

        Tank();
        Tank(int startx, int starty);
        void UpdateAnimation(int& frame_number, int frames[]);// actualizează animația tancului și turetei
        bool CheckTankCollision(int x, int y, Map& map);// verifică coliziunea dreptunghiulară
        void MoveRight(Surface* screen, Map& map); //this is for fixed map
        void Move(Surface* screen, Map& map);
    };
}