#include "map.h"

namespace Tmpl8
{
    int Map::GetWidth() { return MapWidth; }
    int Map::GetHeight() { return MapHeight; }
    bool Map::IsBlocked(int x, int y)// verifică dacă tile-ul este blocant
    {
        // transformă coordonata pixel în coordonată de tile
        int tx = x / TileSize;
        int ty = y / TileSize;
        // dacă coordonata e în afara hărții, considerăm că e blocată
        if (tx < 0 || tx >= MapWidth || ty < 0 || ty >= MapHeight) return true; // în afara hărții
        // verificăm în matrice dacă tile-ul e blocant
        return map[ty][tx * 3 + 2] == 'X'; // 'X' indică un tile blocant
        //true = blocat, false = liber
    }
    void Map::DrawTile(int tx, int ty, Surface* screen, int x, int y)
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
    void Map::DrawMap(Surface* screen)// desenare hartă
        {
            for (int y = 0; y < MapHeight; y++)
                for (int x = 0; x < MapWidth; x++)
                {
                    int tx = map[y][x * 3] - 'a';
                    int ty = map[y][x * 3 + 1] - 'a';
                    DrawTile(tx, ty, screen, x * 32, y * 32);
                }
        }
 };