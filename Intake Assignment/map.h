#pragma once
#include "surface.h"
#include "template.h"

namespace Tmpl8
{
	class Map
	{
	public:
		Surface tiles = ("assets/MediumMap.png");
		static const int MapWidth = 26; // Number of tiles horizontally
		static const int MapHeight = 26; // Number of tiles vertically
		static const int TileSize = 48; // Size of each tile in pixels
		static const int MapSize = 1264; // Width of the tileset image in pixels
		static float cameraX, cameraY; // Map offset

		int getMapWidth() { return MapWidth; }
		int getMapHeight() { return MapHeight; }
		int getTileSize() { return TileSize; }
		int getMapSize() { return MapSize; }
		int getCameraX() { return cameraX; }
		int getCameraY() { return cameraY; }

		bool IsBlocked(int x, int y); // Check if tile at (x,y) is blocked
		void DrawTile(Surface* screen, int tx, int ty, int x, int y); // Draw a single tile at (x,y) on the screen
		void DrawMap(Surface* screen); // Draw the entire map on the screen'
	private:
	
		char map[MapHeight][79] =
		{
			"00X10X20X30X40X50X60X70X80X90X:0X;0X<0X=0X>0X?0X@0XA0XB0XC0XD0XE0XF0XG0XH0XI0X",
			"01X11X21X31X41X51X61X71X81 91 :1 ;1X<1 =1 >1 ?1 @1 A1 B1XC1XD1 E1 F1 G1 H1 I1X",
			"02X12X22X32X42X52X62 72 82 92 :2 ;2X<2X=2X>2 ?2 @2 A2 B2 C2 D2 E2 F2 G2 H2 I2X",
			"03X13X23X33X43X53X63 73 83 93 :3 ;3X<3X=3X>3 ?3 @3 A3 B3 C3 D3 E3 F3XG3 H3 I3X",
			"04X14 24 34 44 54 64 74 84 94 :4 ;4 <4 =4 >4X?4X@4 A4 B4 C4 D4 E4 F4 G4 H4 I4X",
			"05X15 25 35 45 55 65 75 85 95 :5 ;5 <5 =5 >5 ?5 @5 A5 B5 C5 D5 E5 F5 G5 H5 I5X",
			"06X16 26 36 46 56 66 76 86 96 :6 ;6 <6 =6 >6 ?6 @6 A6 B6 C6 D6 E6 F6 G6 H6 I6X",
			"07X17 27 37 47 57 67 77 87 97 :7 ;7 <7 =7 >7 ?7 @7 A7 B7 C7 D7 E7 F7 G7 H7 I7X",
			"08X18 28 38 48 58 68 78 88 98 :8 ;8 <8 =8 >8 ?8 @8 A8 B8 C8 D8 E8 F8 G8 H8 I8X",
			"09X19 29 39 49 59 69 79 89 99 :9 ;9 <9 =9 >9 ?9 @9 A9 B9 C9 D9 E9 F9 G9 H9 I9X",
			"0:X1: 2: 3: 4: 5: 6: 7: 8: 9: :: ;: <: =: >: ?: @: A: B: C: D: E: F: G: H: I:X",
			"0;X1; 2; 3; 4; 5; 6; 7; 8; 9; :; ;; <; =; >; ?; @; A; B; C; D; E; F; G; H; I;X",
			"0<X1< 2< 3< 4< 5< 6< 7< 8< 9< :< ;< << =< >< ?< @< A< B< C< D< E< F< G< H< I<X",
			"0=X1= 2= 3= 4= 5= 6= 7= 8= 9= := ;= <= == >= ?= @= A= B= C= D= E= F= G= H= I=X",
			"0>X1> 2> 3> 4> 5> 6> 7> 8> 9> :> ;> <> => >> ?> @> A> B> C> D> E> F> G> H> I>X",
			"0?X1? 2? 3? 4? 5? 6? 7? 8? 9? :? ;? <? =? >? ?? @? A? B? C? D? E? F? G? H? I?X",
			"0@X1@ 2@ 3@ 4@ 5@ 6@ 7@ 8@ 9@ :@ ;@ <@ =@ >@ ?@ @@ A@ B@ C@ D@ E@ F@ G@ H@ I@X",
			"0AX1A 2A 3A 4A 5A 6A 7A 8A 9A :A ;A <A =A >A ?A @A AA BA CA DA EA FA GA HA IAX",
			"0BX1B 2B 3B 4B 5B 6B 7B 8B 9B :B ;B <B =B >B ?B @B AB BB CB DB EBXFBXGBXHBXIBX",
			"0CX1C 2C 3C 4C 5C 6C 7C 8C 9C :C ;C <C =C >C ?C @C AC BC CC DC ECXFCXGCXHCXICX",
			"0DX1D 2D 3D 4D 5D 6D 7D 8D 9D :D ;D <D =D >D ?D @D AD BD CD DD EDXFDXGDXHDXIDX",
			"0EX1EX2EX3E 4E 5E 6E 7E 8E 9E :E ;E <E =E >E ?E @E AE BE CE DE EEXFEXGEXHEXIEX",
			"0FX1FX2FX3F 4F 5F 6F 7F 8F 9F :F ;F <F =F >F ?F @F AF BF CF DF EFXFFXGFXHFXIFX",
			"0GX1GX2GX3G 4G 5G 6G 7G 8G 9G :G ;G <G =G >G ?G @G AG BG CG DG EGXFGXGGXHGXIGX",
			"0HX1HX2HX3HX4HX5HX6HX7HX8HX9HX:HX;HX<HX=HX>HX?HX@HXAHXBHXCHXDHXEHXFHXGHXHHXIHX",
			"0IX1IX2IX3IX4IX5IX6IX7IX8IX9IX:IX;IX<IX=IX>IX?IX@IXAIXBIXCIXDIXEIXFIXGIXHIXIIX",
		}; //104 lectie

	};
};