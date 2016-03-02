#include "tile.h"
#include <QtGui>
#include <math.h>

Tile::Tile()
{
	type=TT_AIR;
	grassiness=6;
}

Tile::Tile(uint x, uint y, tiletype ty=TT_AIR, uint _seed=0)
	:x(x),y(y),type(ty),grassiness(0)
{
	seed=rand_r(&(++_seed))+0x000001;
}

void Tile::draw(QPainter *painter){
	/*if(isSolid()){
		painter->drawRect(x*TS+4, y*TS+4, TS-8, TS-8);
	}*/
	uint se=seed;
	//if(rand_r(&se)%50)
	//	seed++;
	//painter->setPen(QPen(QColor(0,0,0),0));
	//painter->setPen(QPen());
	painter->setBrush(QBrush(QColor(0,0,0)));
	painter->setBrush(QBrush(QColor(255,255,255)));
	//painter->setPen(QPen());
	painter->setPen(QPen(QColor(255,255,255)));

	switch(type){
	case TT_AIR: break;
	case TT_SAND:
	case TT_DIRT:
	case TT_ROCK:
		painter->drawRect(x*TS, y*TS, TS, TS);
		break;
	case TT_BRICK:{
		painter->setBrush(QBrush(Qt::white));
		painter->drawRect(x*TS, y*TS, TS, TS);
		painter->setBrush(QBrush(Qt::black));
		 bool evenrow=true;
		 int tv=4,th=3;
		 for(int i=0;i<TS;i+=TS/th){
			for(int j=0;j<TS;j+=TS/tv){
				evenrow^=1;
				painter->drawRect(x*TS+i+((TS/th/2)*evenrow)-TS/th/2, y*TS+j, TS/th, TS/tv);
			}
		 }
		 break;}
	case TT_APPLE:
		painter->drawEllipse(x*TS+4, y*TS+4, TS-8, TS-8);
		break;
	case TT_WATER:
		painter->drawEllipse(x*TS+6, y*TS+6, TS-12, TS-12);
		painter->setBrush(QBrush(Qt::blue));
		painter->drawEllipse(x*TS+7, y*TS+7, TS-14, TS-14);
		break;
	default:
		painter->drawRoundedRect(x*TS-4, y*TS-4, TS+8, TS+8, 5, 5);
		break;
	}
	if(type!=TT_AIR && type!=TT_WATER){
		painter->setPen(QPen(Qt::white));
		for(int i=0;i<grassiness*7;i++){
			drawGrass(painter,x*TS+rand_r(&se)%TS,y*TS+rand_r(&se)%TS,rand_r(&se),type);
		}
	}
}

void Tile::draw2(QPainter *painter){
	uint se=seed;
	//painter->setPen(QPen(QColor(0,0,0),0));
	//painter->setPen(QPen());
	painter->setBrush(QBrush(Qt::black));
	painter->setPen(QPen());
	if(type!=TT_AIR && type!=TT_WATER) {
		painter->setPen(QPen(Qt::black));
		for(int i=0; i<grassiness; i++){
			drawGrass(painter,x*TS+rand_r(&se)%TS,y*TS+rand_r(&se)%TS,rand_r(&se),type);
		}
	}
	if(type==TT_ROCK){
		if(type!=TT_AIR && type!=TT_WATER) {
			for(int i=0; i<20; i++){
				if(rand_r(&se)%100<50){
					painter->setPen(QPen(Qt::white));
				}else{
					painter->setPen(QPen(Qt::black));
				}
				painter->drawRect(x*TS+rand_r(&se)%TS,y*TS+rand_r(&se)%TS,1,1);
			}
		}
	}
}
void Tile::drawGrass(QPainter *painter,int X,int Y,uint seed,tiletype type){
	//painter->setCompositionMode(QPainter::CompositionMode_Difference);
	double xx,yy,xf,yf,c,d,
	w=10,
	l=5;
	int angley=2,
	chanceToTurn=30,
	chanceToStop=30;
	//symetry=1,
	//gapey=0,
	uint se=seed;

	c=w/2;
	//d=360/angley*irandom(angley);
	//d=rand_r(&se)%360;
	//d=(rand_r(&se)%angley)*360/angley;
	d=0;
	//d=360;
	yy=0;yf=0;
	xx=0;xf=0;

	switch(type){
	case TT_APPLE: return;
	case TT_SAND:
		chanceToTurn=0;
		chanceToStop=50;
		l=1;
		break;
	/*case TT_WOOD:
		chanceToTurn=0;
		chanceToStop=50;
		l=1;
		break;*/
	case TT_ROCK:
		chanceToTurn=0;
		chanceToStop=30;
		l=2;
		d=45;
		break;
	default:
		break;
	}

	while((rand_r(&se)%100)>chanceToStop){
		//d+=360/angley*irandom_range(angley/2,-angley/2)+irandom_range(angley/3,-angley/3);
		if((rand_r(&se)%100)>chanceToTurn){
			d+=(360/angley);
		}
		if((rand_r(&se)%100)>chanceToTurn){
			d-=(360/angley);
		}

		//d/=2;

		xx+=cos(d)*l;
		yy+=sin(d)*l;
		/* *

		if((rand_r(&se)%100)>50){
		xx+=1;
		}else{
		xx-=1;
		}
		if((rand_r(&se)%100)>50){
		yy+=1;
		}else{
		yy-=1;
		}
		// */
		if(xx<-c || yy<-c || xx>c || yy>c)break;
		painter->drawLine(X-xx,Y-yy,X-xf,yf+Y);
		//painter->drawLine(c+xx+X,c+yy+Y,c+xf+X,c+yf+Y);
		xf=xx;
		yf=yy;
	}
}

