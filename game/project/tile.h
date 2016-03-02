#ifndef TILE_H
#define TILE_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include "globaldefines.h"

#define TS 16

QT_BEGIN_NAMESPACE
class QPainter;
class QPaintEvent;
QT_END_NAMESPACE


class Tile
{
public:
	enum tiletype {
				 TT_AIR,
				 TT_APPLE,
				 TT_PLAYERSPAWN,
				 TT_WATER,
				 TT_SAND,
				 TT_DIRT,
				 TT_ROCK,
				 TT_BRICK
	};
	Tile();
	Tile(uint x, uint y, tiletype ty, uint seedseed);
	void draw(QPainter *painter);
	void draw2(QPainter *painter);
	//void set(int x,int y,tiletype ty){x=x;y=y;type=ty;}
	tiletype settype(Tile::tiletype newtype){return type=newtype;}
	int setx(int newx){return x=newx;}
	int sety(int newy){return y=newy;}
	int setgrassiness(int newgrassiness){return grassiness=newgrassiness;}
	int isSolid(){return (type!=TT_AIR) && (type!=TT_WATER) && (type!=TT_PLAYERSPAWN) && (type!=TT_APPLE);}

	int operator=(int newgrassiness){return grassiness=newgrassiness;}
	tiletype operator=(Tile::tiletype newtype){return type=newtype;}
private:
	void drawGrass(QPainter *painter,int X,int Y, uint seed=4, tiletype type=TT_DIRT);
	int x,y;
	tiletype type;
	int grassiness;
	uint seed;
};

#endif // TILE_H
