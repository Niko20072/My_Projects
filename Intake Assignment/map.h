#pragma once
#include "surface.h"
#include "template.h"

namespace Tmpl8
{
	class Map
	{
	public:

		Surface tiles = ("assets/Map.png");
		static const int MapWidth = 16;
		static const int MapHeight = 16;
		static const int TileSize = 48;
		static const int MapSize = 768;
		static int cameraX, cameraY; //map offset

		char map[MapHeight][49] =
		{
			"aa ba ca da ea fa ga ha ia ja ka la ma na oa pa ",
			"ab bb cb db eb fb gb hb ib jb kb lb mb nb ob pb ",
			"ac bc cc dc ec fc gc hc ic jc kc lc mc nc oc pc ",
			"ad bd cd dd ed fd gd hd id jd kd ld md nd od pd ",
			"ae be ce de ee fe ge he ie je ke le me ne oe pe ",
			"af bf cf df ef ff gf hf if jf kf lf mf nf of pf ",
			"ag bg cg dg eg fg gg hg ig jg kg lg mg ng og pg ",
			"ah bh ch dh eh fh gh hh ih jh kh lh mh nh oh ph ",
			"ai bi ci di ei fi gi hi ii ji ki li mi ni oi pi ",
			"aj bj cj dj ej fj gj hj ij jj kj lj mj nj oj pj ",
			"ak bk ck dk ek fk gk hk ik jk kk lk mk nk ok pk ",
			"al bl cl dl el fl gl hl il jl kl ll ml nl ol pl ",
			"am bm cm dm em fm gm hm im jm km lm mm nm om pm ",
			"an bn cn dn en fn gn hn in jn kn ln mn nn on pn ",
			"ao bo co do eo fo go ho io jo ko lo mo no oo po ",
			"ap bp cp dp ep fp gp hp ip jp kp lp mp np op pp "
		};

		void DrawTile(Surface* screen, int tx, int ty, int x, int y);
		void DrawMap(Surface* screen);
	};
}