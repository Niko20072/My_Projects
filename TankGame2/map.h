#pragma once
#include "surface.h"
#define MapWidth 25
#define MapHeight 17
static constexpr int TileSize = 32;

namespace Tmpl8
{
    class Map
    {
    public:
        Surface tiles = ("assets/nc2tiles.png");

        char map[MapHeight][76] = {
        "aaXeeXeeXeeXeeXeeXeeXeeXeeXeeXeeXeeXeeXeeXeeXeeXeeXeeXeeXeeXeeXeeXeeXeeXdaX",
        "cbXfb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-cbXfb-fb-fb-fb-fb-fb-fb-fb-cbX",
        "cbXfb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-cbXfb-fb-fb-fb-fb-fb-fb-fb-cbX",
        "cbXfb-fb-fb-fb-hfXeeXdeXmeXneXoeXeeXdaXfb-fb-cbXfb-fb-mbXndXndXndXnbXfb-cbX",
        "cbXfb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-cbXfb-fb-cbXfb-fb-mcXpcXpcXpcXncXfb-cbX",
        "cbXfb-fb-fb-fb-fb-adXfb-fb-fb-fb-fb-cbXfb-fb-qaXfb-fb-mcXpcXmfXpcXncXfb-cbX",
        "cbXfb-fb-fb-fb-fb-abXga-ia-ha-deXeeXdcXfb-fb-fb-fb-fb-mcXpcXpcXpcXncXfb-cbX",
        "cbXfb-fb-fb-fb-fb-qaXfb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-mdXmeXneXoeXodXfb-cbX",
        "cbXfb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-cbXfb-fb-fb-fb-fb-fb-fb-fb-cbX",
        "cbXfb-fb-fb-cbXfb-fb-fb-fb-fb-fb-fb-fb-fb-fb-cbXfb-fb-fb-fb-fb-fb-fb-fb-cbX",
        "cbXfb-fb-fb-cbXfb-fb-fb-fb-fb-fb-fb-fb-fb-fb-cbXfb-fb-fb-fb-fb-fb-fb-fb-cbX",
        "cbXfb-fb-fb-cbXfb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-cbX",
        "cbXfb-fb-fb-cbXfb-fb-fb-fb-fb-fb-fb-fb-fb-fb-cbXfb-fb-fb-fb-fb-fb-fb-fb-cbX",
        "cbXfb-fb-fb-cbXfb-fb-fb-fb-fb-fb-fb-fb-fb-fb-cbXfb-fb-fb-fb-fb-fb-fb-fb-cbX",
        "cbXfb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-fb-cbXfb-fb-fb-fb-fb-fb-fb-fb-cbX",
        "acXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXcdXddX"
        };
        int GetWidth();
        int GetHeight();
        bool IsBlocked(int x, int y);
        void DrawTile(int tx, int ty, Surface* screen, int x, int y);
        void DrawMap(Surface* screen);// desenare hartã
    };
}