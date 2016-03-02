#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <QtGui>
#include "obj.h"
#include "tile.h"
#include "globaldefines.h"
#include "player.h"
class Player;
class World
{
public:
	World(QSize windowSize);
	void step();
	void draw(QPainter* painter);
	void moveView(int x,int y);
	QRect getViewRect(){return viewRect;}
	bool keyLeft,keyRight,keyDown,keyUp,keyMap;
private:
	QImage renderScene();
	QImage renderMap();
	//void setLevel();
	void generateWorld(uint seed);
	std::vector<Obj> objs;
	std::vector<std::vector<Tile*> > levelgrid;
	//std::vector<std::vector<Player*> > playergrid;
	Player* player;

	QRect worldRect;
	QRect windowRect;
	//viewRect.x/y will be in increments of viewrect.width/height().
	QRect viewRect;
	QImage view;
	QImage mapView;

	uint steps;
};

#endif // WORLD_H
