#pragma once
#include "surface.h"
#include "template.h"

namespace Tmpl8
{
	class Map
	{
	public:

		/*
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
		};*/

		/*
		Surface tiles = ("assets/BiggerMap.png");

		static const int MapWidth = 36;
		static const int MapHeight = 36;
		static const int TileSize = 48;
		static const int MapSize = 1760;

		static int cameraX, cameraY; //map offset

		char map[MapHeight][109] =
		{
			"00X10X20X30X40X50X60X70X80X90X:0X;0X<0X=0X>0X?0X@0XA0XB0XC0XD0XE0XF0XG0XH0XI0XJ0XK0XL0XM0XN0XO0XP0XQ0XR0XS0X",
			"01X11X21X31X41X51 61 71 81 91 :1 ;1 <1 =1 >1 ?1 @1 A1 B1 C1 D1 E1 F1 G1 H1 I1 J1 K1 L1 M1 N1 O1 P1 Q1 R1 S1X",
			"02X12X22X32X42X52 62 72 82 92 :2 ;2 <2 =2 >2 ?2 @2 A2 B2 C2 D2 E2 F2 G2 H2 I2 J2 K2 L2 M2 N2 O2 P2 Q2 R2 S2X",
			"03X13X23X33X43X53 63 73 83 93 :3X;3X<3X=3 >3 ?3 @3 A3 B3 C3 D3 E3 F3 G3 H3 I3 J3 K3 L3 M3 N3 O3 P3 Q3 R3 S3X",
			"04X14 24 34 44 54 64 74 84 94 :4 ;4 <4 =4 >4 ?4 @4 A4 B4 C4 D4 E4 F4 G4 H4 I4 J4 K4 L4 M4 N4 O4 P4 Q4 R4 S4X",
			"05X15 25 35 45 55 65 75 85 95 :5 ;5 <5 =5 >5 ?5 @5 A5 B5 C5 D5 E5 F5 G5 H5 I5 J5 K5 L5 M5 N5 O5 P5 Q5 R5 S5X",
			"06X16 26 36 46 56 66 76 86 96 :6 ;6 <6 =6 >6 ?6 @6 A6 B6 C6 D6 E6 F6 G6 H6 I6 J6 K6 L6 M6 N6 O6 P6 Q6 R6 S6X",
			"07X17 27 37 47 57 67 77 87 97 :7 ;7 <7 =7 >7 ?7 @7 A7 B7 C7 D7 E7 F7 G7 H7 I7 J7 K7 L7 M7 N7 O7 P7 Q7 R7 S7X",
			"08X18 28 38 48 58 68 78 88 98 :8 ;8 <8 =8 >8 ?8 @8 A8 B8 C8 D8 E8 F8 G8 H8 I8 J8 K8 L8 M8 N8 O8 P8 Q8 R8 S8X",
			"09X19 29 39 49 59 69 79 89 99 :9 ;9 <9 =9 >9 ?9 @9 A9 B9 C9 D9 E9 F9 G9 H9 I9 J9 K9 L9 M9 N9 O9 P9 Q9 R9 S9X",
			"0:X1: 2: 3: 4: 5: 6: 7: 8: 9: :: ;: <: =: >: ?: @: A: B: C: D: E: F: G: H: I: J: K: L: M: N: O: P: Q: R: S:X",
			"0;X1; 2; 3; 4; 5; 6; 7; 8; 9; :; ;; <; =; >; ?; @; A; B; C; D; E; F; G; H; I; J; K; L; M; N; O; P; Q; R; S;X",
			"0<X1< 2< 3< 4< 5< 6< 7< 8< 9< :< ;< << =< >< ?< @< A< B< C< D< E< F< G< H< I< J< K< L< M< N< O< P< Q< R< S<X",
			"0=X1= 2= 3= 4= 5= 6= 7= 8= 9= := ;= <= == >= ?= @= A= B= C= D= E= F= G= H= I= J= K= L= M= N= O= P= Q= R= S=X",
			"0>X1> 2> 3> 4> 5> 6> 7> 8> 9> :> ;> <> => >> ?> @> A> B> C> D> E> F> G> H> I> J> K> L> M> N> O> P> Q> R> S>X",
			"0?X1? 2? 3? 4? 5? 6? 7? 8? 9? :? ;? <? =? >? ?? @? A? B? C? D? E? F? G? H? I? J? K? L? M? N? O? P? Q? R? S?X",
			"0@X1@ 2@ 3@ 4@ 5@ 6@ 7@ 8@ 9@ :@ ;@ <@ =@ >@ ?@ @@ A@ B@ C@ D@ E@ F@ G@ H@ I@ J@ K@ L@ M@ N@ O@ P@ Q@ R@ S@X",
			"0AX1A 2A 3A 4A 5A 6A 7A 8A 9A :A ;A <A =A >A ?A @A AA BA CA DA EA FA GA HA IA JA KA LA MA NA OA PA QA RA SAX",
			"0BX1B 2B 3B 4B 5B 6B 7B 8B 9B :B ;B <B =B >B ?B @B AB BB CB DB EB FB GB HB IB JB KB LB MB NB OB PB QB RB SBX",
			"0CX1C 2C 3C 4C 5C 6C 7C 8C 9C :C ;C <C =C >C ?C @C AC BC CC DC EC FC GC HC IC JC KC LC MC NC OC PC QC RC SCX",
			"0DX1D 2D 3D 4D 5D 6D 7D 8D 9D :D ;D <D =D >D ?D @D AD BD CD DD ED FD GD HD ID JD KD LD MD ND OD PD QD RD SDX",
			"0EX1E 2E 3E 4E 5E 6E 7E 8E 9E :E ;E <E =E >E ?E @E AE BE CE DE EE FE GE HE IE JE KE LE ME NE OE PE QE RE SEX",
			"0FX1F 2F 3F 4F 5F 6F 7F 8F 9F :F ;F <F =F >F ?F @F AF BF CF DF EF FF GF HF IF JF KF LF MF NF OF PF QF RF SFX",
			"0GX1G 2G 3G 4G 5G 6G 7G 8G 9G :G ;G <G =G >G ?G @G AG BG CG DG EG FG GG HG IG JG KG LG MG NG OG PG QG RG SGX",
			"0HX1H 2H 3H 4H 5H 6H 7H 8H 9H :H ;H <H =H >H ?H @H AH BH CH DH EH FH GH HH IH JH KH LH MH NH OH PH QH RH SHX",
			"0IX1I 2I 3I 4I 5I 6I 7I 8I 9I :I ;I <I =I >I ?I @I AI BI CI DI EI FI GI HI II JI KI LI MI NI OI PI QI RI SIX",
			"0JX1J 2J 3J 4J 5J 6J 7J 8J 9J :J ;J <J =J >J ?J @J AJ BJ CJ DJ EJ FJ GJ HJ IJ JJ KJ LJ MJ NJ OJ PJ QJ RJ SJX",
			"0KX1K 2K 3K 4K 5K 6K 7K 8K 9K :K ;K <K =K >K ?K @K AK BK CK DK EK FK GK HK IK JK KK LK MK NK OK PK QK RK SKX",
			"0LX1L 2L 3L 4L 5L 6L 7L 8L 9L :L ;L <L =L >L ?L @L AL BL CL DL EL FL GL HL IL JL KL LL ML NL OL PL QL RL SLX",
			"0MX1M 2M 3M 4M 5M 6M 7M 8M 9M :M ;M <M =M >M ?M @M AM BM CM DM EM FM GM HM IM JM KM LM MM NM OM PMXQMXRMXSMX",
			"0NX1N 2N 3N 4N 5N 6N 7N 8N 9N :N ;N <N =N >N ?N @N AN BN CN DN EN FN GN HN IN JN KN LN MN NN ON PNXQNXRNXSNX",
			"0OX1O 2O 3O 4O 5O 6O 7O 8O 9O :O ;O <O =O >O ?O @O AO BO CO DO EO FO GO HO IO JO KO LO MO NO OO POXQOXROXSOX",
			"0PX1PX2PX3P 4P 5P 6P 7P 8P 9P :P ;P <P =P >P ?P @P AP BP CP DP EP FP GP HP IP JP KP LP MP NP OP PPXQPXRPXSPX",
			"0QX1QX2QX3Q 4Q 5Q 6Q 7Q 8Q 9Q :Q ;Q <Q =Q >Q ?Q @Q AQ BQ CQ DQ EQ FQ GQ HQ IQ JQ KQ LQ MQ NQ OQ PQXQQXRQXSQX",
			"0RX1RX2RX3RX4RX5RX6RX7RX8RX9RX:RX;RX<RX=RX>RX?RX@RXARXBRXCRXDRXERXFRXGRXHRXIRXJRXKRXLRXMRXNRXORXPRXQRXRRXSRX",
			"0SX1SX2SX3SX4SX5SX6SX7SX8SX9SX:SX;SX<SX=SX>SX?SX@SXASXBSXCSXDSXESXFSXGSXHSXISXJSXKSXLSXMSXNSXOSXPSXQSXRSXSSX"
		};
		*/

		Surface tiles = ("assets/MediumMap.png");

		static const int MapWidth = 26;
		static const int MapHeight = 26;
		static const int TileSize = 48;
		static const int MapSize = 1264;
		static int cameraX, cameraY; //map offset
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
		};

		bool IsBlocked(int x, int y);
		void DrawTile(Surface* screen, int tx, int ty, int x, int y);
		void DrawMap(Surface* screen);
	};
};