#ifndef CONNECTION_H
#define CONNECTION_H
#include "obj.h"
class Obj;

class Connection
{
public:
	Obj* obj;//Connected to
	double len;//Try to be this distance from obj
	//double dir,delx,dely;//Try to BEAT THAT YEAH
	Connection();
};
#endif // CONNECTION_H
