#include <QtGui>
#include "player.h"
#include "world.h"

Player::Player(int x, int y)
	:x(x),y(y)
{
	///Initialize the player.

	w=5;
	h=8;
	vx=1;
	vy=10;
	img=QImage(":/images/player.png");
	img2=QImage(":/images/player2.png");
}

void Player::step(std::vector < std::vector < Tile * > > * levelgrid, bool keyLeft, bool keyRight, bool keyDown, bool keyUp, World* world){
	///Move the player.

	bool grounded=testCollision(x,y+1,levelgrid);
	//movement:
	vx+=(keyRight-keyLeft) * (2 + 2*grounded);
	//Fly!
	vy-=(QApplication::keyboardModifiers()!=0) * 3;
	if(grounded){
		if(keyUp){
			vy=-12+keyDown*5;
		}
 //physics:
		//Apply friction.
		vx*=0.8;
	}
	//Apply gravity.
	vy+=1;
	//Limit speed.
	if(vy> 10)vy= 10;
	if(vx> 10)vx= 10;
	if(vx<-10)vx=-10;

	//Collide.
	if(testCollision(x,y,levelgrid)){
		x+=(rand()%10)-5;
		y+=(rand()%10)-5;
	}
	for(double i=0;i<10;i++){
		double yn=y+vy/10;
		if(testCollision(x,yn,levelgrid)){
			vy/=2;
		}else{
			y=yn;
		}
	}
	for(double i=0;i<10;i++){
		double xn=x+vx/10;
		if(testCollision(xn,y,levelgrid)){
			vx/=2;
		}else{
			x=xn;
		}
	}
	QRect vr=world->getViewRect();
	/*Wrap.
	if(y>wr.height()+h){
		y=-h;
	}
	if(y<-h){
		y=wr.height()+h;
	}
	if(x<-w){
		x=wr.width();
	}
	if(x>wr.width()){
		x=-w;
	}*/
	//Move the view when the player goes offscreen.
	//the position that the player is drawn
	double dx=x-vr.x();
	double dy=y-vr.y();
	if(dx<0)			{ world->moveView(-1, 0 ); }
	if(dx>vr.width())	{ world->moveView( 1, 0 ); }
	if(dy<0)			{ world->moveView( 0, -1); }
	if(dy>vr.height())	{ world->moveView( 0, 1 ); }
}

void Player::draw(QPainter *painter, World* world){
	///Draw the player.

	//Place the player on the window based on the viewRect.
	double dx=x-world->getViewRect().x();
	double dy=y-world->getViewRect().y();
	//Choose between the two images based on the player's X coord.
	if((int)(x/4)%2){
		painter->drawImage(dx-3,dy-1,img);
	}else{
		painter->drawImage(dx-3,dy-1,img2);
	}
	//Attempt to draw the player with lines and such.
	/*
	painter->setBrush(QBrush(Qt::black));
	painter->setPen(QPen(Qt::white));
	//body
	painter->drawRect(x,y,w,h);
	//shadow
	painter->drawLine(x+w-1,y,x+w-1,y+h);
	//arms
	painter->drawLine(x,y+4,x-1,y+4);
	painter->drawLine(x+w,y+4,x+w+1,y+4);
	//hands
	int o=1;
	painter->drawLine(x-2,y+4,x-3,y+4-o);
	painter->drawLine(x+w+2,y+4,x+w+3,y+4-o);
	painter->drawLine(x-1,y+4,x-2,y+4+o);
	painter->drawLine(x+w+1,y+4,x+w+2,y+4+o);
	*/
}

bool Player::testCollision(double X,double Y,std::vector < std::vector < Tile * > > * levelgrid){
	///Test the four corners of the player, and return whether there was a collision.

	return testPoint(X,Y,levelgrid)
		|| testPoint(X+w,Y,levelgrid)
		|| testPoint(X,Y+h,levelgrid)
		|| testPoint(X+w,Y+h,levelgrid);
}
bool Player::testPoint(double X,double Y,std::vector < std::vector < Tile * > > * levelgrid){
	///Test whether a point on the levelgrid collides.

	//position on grid
	int gx,gy;
	gx=(int)floor(X/16);
	gy=(int)floor(Y/16);
	//Test outside boundaries.
	if(gx<0 || gy<0 || gx>=(int)(*levelgrid).size() || gy>=(int)(*levelgrid).size()){
		return gy>0;
	}
	return (*levelgrid)[gx][gy]->isSolid();
}

