#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "tile.h"

class World;
class Player
{
public:
	Player(int x,int y);
	void step(std::vector < std::vector < Tile * > > * levelgrid, bool keyLeft, bool keyRight, bool keyDown, bool keyUp, World* world);
	void draw(QPainter *painter, World *world);
	double getX(){return x;}
	double getY(){return y;}
private:
	int w,h;
	double x,y,vx,vy;
	bool testCollision(double X,double Y,std::vector < std::vector < Tile * > > * levelgrid);
	bool testPoint(double X,double Y,std::vector < std::vector < Tile * > > * levelgrid);
	QImage img,img2;
};

#endif // PLAYER_H
