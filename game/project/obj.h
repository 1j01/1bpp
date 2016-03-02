#ifndef OBJ_H
#define OBJ_H

#include <vector>
#include "connection.h"
class Connection;

class Obj
{
public:
	double x,y,vx,vy;
	std::vector<Connection> connections;
	Obj();
};



#endif // OBJ_H
