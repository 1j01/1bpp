#include "world.h"
#include <vector>

World::World(QSize windowSize)
{
	///Initialize the world and the player; render the world.

	//Setup some rectangles. Units are (sometimes inconveniently) pixels.
	/*windowRect = QRect(0,0,256,256);
	//windowRect = QRect(0,0,painter->window().width(),painter->window().height());
	viewRect = QRect(0,0,256,256);*/
	worldRect = QRect(0,0,40,40);
	windowRect = QRect(QPoint(0,0),windowSize);
	viewRect = QRect(QPoint(0,0),windowSize);
	//viewRect = QRect(windowRect);

	//a not-so-random random seed
	uint se=0;
	/*if(QApplication.arguments().size()){
		QString arg=QApplication.arguments()[0];
		se=arg.toUInt();
	}*/

	//Add Tiles to the grid
	//Note usage of worldRect/TS. That's a bad thing.
	for(uint i=0;i<(uint)worldRect.width();i++){
		std::vector<Tile*> levelrow;
		for(uint j=0;j<(uint)worldRect.height();j++){
			Tile* tile=new Tile(i,j,Tile::TT_AIR,rand_r(&se));
			*tile=60;
			//or
			//tile->setgrassiness(60);
			levelrow.push_back(tile);
		}
		levelgrid.push_back(levelrow);
	}

	//Make a nice little level out of them.
	//setLevel();
	generateWorld(se);

	//Create the player.
	player=new Player(20,20);

	//Initialize the keyboard input.
	keyLeft=false,keyRight=false,keyDown=false,keyUp=false,keyMap=false;

	//Initialize the step counter.
	steps=0;

	//Render the ENTIRE WORLD to a QImage.
	view=renderScene();
	//Represent the ENTIRE WORLD with a QImage.
	mapView=renderMap();
}

void World::step(){
	///Tell the player to move.
	if(!keyMap){
		player->step(&levelgrid,keyLeft,keyRight,keyDown,keyUp,this);
	}
}

void World::draw(QPainter *painter){
	///Show the world's contents and the world image.

	//Clear.
	painter->setBrush(QBrush(Qt::black));
	painter->drawRect(windowRect);
	painter->setBrush(QBrush(Qt::white,Qt::Dense6Pattern));
	painter->drawRect(windowRect);
	if(keyMap){
		//Draw the cached map.
		painter->drawImage((viewRect.width()-worldRect.width())/2,(viewRect.height()-worldRect.height())/2,mapView);

		//Draw the player as a dot, sometimes.
		if(steps%5){
			painter->setPen(QPen(Qt::white));
			painter->drawPoint(player->getX()/16,player->getY()/16);
		}
	}else{
		//Draw the cached image.
		painter->drawImage(-viewRect.x(),-viewRect.y(),view);
		//Tell the player to draw itself.
		player->draw(painter,this);
	}
/* Invert the screen!
	painter->setCompositionMode(QPainter::CompositionMode_Difference);
	painter->fillRect(viewRect, Qt::white);
*/
}

QImage World::renderScene(){
	///Render the ENTIRE WORLD to a QImage.

	//la imagen para regresar
	QImage img=QImage(worldRect.size()*16,QImage::Format_Mono);
	//QImage img=QImage(viewRect.size(),QImage::Format_Mono);
	QPainter *painter=new QPainter(&img);
	//Clear.
	painter->setBrush(QBrush(QColor(0,0,0)));
	painter->drawRect(QRect(0,0,worldRect.width()*16,worldRect.height()*16));
	//Draw each tile.
	for(uint i=0;i<levelgrid.size();i++){
		for(uint j=0;j<levelgrid[i].size();j++){
			levelgrid[i][j]->draw(painter);
		}
	}
	//Draw each tile's second layer.
	for(uint i=0;i<levelgrid.size();i++){
		for(uint j=0;j<levelgrid[i].size();j++){
			levelgrid[i][j]->draw2(painter);
		}
	}
	return img;
}

QImage World::renderMap(){
	///Represent the ENTIRE WORLD with a QImage.

	//la imagen para regresar
	QImage img=QImage(worldRect.size(),QImage::Format_Mono);
	//QImage img=QImage(viewRect.size(),QImage::Format_Mono);
	QPainter *painter=new QPainter(&img);
	//Clear.
	painter->setBrush(QBrush(Qt::black));
	painter->drawRect(worldRect);
	painter->setPen(QPen(Qt::white));
	//Draw each tile.
	for(uint i=0;i<levelgrid.size();i++){
		for(uint j=0;j<levelgrid[i].size();j++){
			if(levelgrid[i][j]->isSolid()){
				painter->drawPoint(i,j);
			}
		}
	}
	return img;
}

void World::moveView(int x,int y){
	///Move the view in increments of the view size.

	viewRect.translate( x*viewRect.width(),
						y*viewRect.height());
}


void World::generateWorld(uint seed){
	///Generate the world.

	//la semilla de números aleatorios!
	uint se,_se=se=seed;
	//Generate the terrain.
	for(int i=0;i<worldRect.width();i++){
		for(int j=5;j<worldRect.height();j++){
			double s=50;
			double n1=sin(_se+-s*i/100-s*j/59+(rand_r(&se)%5)/7)*0.5;
			double n2=cos(_se+s*i/145-s*j/80+(rand_r(&se)%5)/7)*0.5;
			double n3=sin(_se+s*i/245+s*j/150+(rand_r(&se)%5)/4)*0.5;
			double n4=cos(_se+-s*i/345+s*j/180+(rand_r(&se)%5)/10)*0.5;
			double n=n1+n2-n3-n4;
			//if(n>1-((double)j)/10){
			if(n>0){
				*levelgrid[i][j]=Tile::TT_DIRT;
				if(n>0.7){
					*levelgrid[i][j]=Tile::TT_ROCK;
				}else if(n1+n2<0){
					*levelgrid[i][j]=Tile::TT_SAND;
				}/*else if(n3+n4<0){
					*levelgrid[i][j]=Tile::TT_WATER;
				}*/
				//*levelgrid[i][j]=80-n*50;
			}else if(n<-1 && (rand_r(&se)%50==3)){
				*levelgrid[i][j]=Tile::TT_APPLE;
			}
		}
	}
	//Add in some "buildings".
	//For each nonexistant blueprint...
	for(int i=0;i<worldRect.width()*worldRect.height()/1000;i++){
		//position on the grid
		int x,y;
		//Choose a random starting position.
		x=rand_r(&se)%(worldRect.width());
		y=rand_r(&se)%(worldRect.height());
		//{true: move x, false: move y}
		bool dir=(rand_r(&se)%100)<50;
		//{true: move foreward, false: move backward.}
		bool dir2=(rand_r(&se)%100)<50;
		//Make a |200| block building.
		for(int j=0;j<50;j++){
			//Maybe make a turn?
			if((rand_r(&se)%100)<25){
				dir^=1;
				//Maybe turn the other way?
				if((rand_r(&se)%100)<25){
					dir2^=1;
				}
			}
			//Move.
			if(dir){
				if(dir2){
					x++;
				}else{
					x--;
				}
			}else{
				if(dir2){
					y++;
				}else{
					y--;
				}
			}
			//Check bounds. Don't go outside them. Don't crash the game.
			if(x<0 || y<0 || x>=(int)levelgrid.size() || y>=(int)levelgrid.size()){
				break;
			}
			//Make the wall.
			*levelgrid[x][y]=Tile::TT_BRICK;
			*levelgrid[x][y]=1;
		}
	}
	//Add in some tunnels.
	//For each nonexistant blueprint...
	for(int i=0;i<worldRect.width()*worldRect.height()/10000;i++){
		//position on the grid
		int x,y;
		//Choose a random starting position.
		x=rand_r(&se)%(worldRect.width());
		y=rand_r(&se)%(worldRect.height());
		//{true: move x, false: move y}
		bool dir=(rand_r(&se)%100)<50;
		//{true: move foreward, false: move backward.}
		bool dir2=(rand_r(&se)%100)<50;
		//Make a |200| block building.
		for(int j=0;j<200;j++){
			//Maybe make a turn.
			if((rand_r(&se)%100)<15){
				dir^=1;
			}
			//Move.
			if(dir){
				if(dir2){
					x++;
				}else{
					x--;
				}
			}else{
				if(dir2){
					y++;
				}else{
					y--;
				}
			}
			//Check bounds. Don't go outside them. Don't crash the game.
			if(x<0 || y<0 || x>=(int)levelgrid.size() || y>=(int)levelgrid.size()){
				break;
			}
			//Make the hole.
			*levelgrid[x][y]=Tile::TT_WATER;
			*levelgrid[x][y]=1;
		}
	}
}
/*
void World::setLevel(){
	///Make a nice little stupid level..

	*levelgrid[2][3]=Tile::TT_DIRT;
	*levelgrid[2][4]=Tile::TT_DIRT;
	*levelgrid[3][3]=Tile::TT_DIRT;
	*levelgrid[4][3]=Tile::TT_DIRT;
	levelgrid[4][4]->settype(Tile::TT_DIRT);
	levelgrid[4][5]->settype(Tile::TT_DIRT);
	levelgrid[5][3]->settype(Tile::TT_DIRT);
	levelgrid[5][2]->settype(Tile::TT_BRICK);
	levelgrid[5][1]->settype(Tile::TT_BRICK);
	levelgrid[5][0]->settype(Tile::TT_BRICK);
	levelgrid[5][5]->settype(Tile::TT_BRICK);
	levelgrid[3][4]->settype(Tile::TT_APPLE);
	levelgrid[5][14]->settype(Tile::TT_SAND);
	levelgrid[6][14]->settype(Tile::TT_SAND);
	levelgrid[7][14]->settype(Tile::TT_SAND);
	levelgrid[8][14]->settype(Tile::TT_SAND);
	levelgrid[9][14]->settype(Tile::TT_WATER);
	levelgrid[10][14]->settype(Tile::TT_WATER);
	levelgrid[11][14]->settype(Tile::TT_WATER);
	levelgrid[9][15]->settype(Tile::TT_WATER);
	levelgrid[10][15]->settype(Tile::TT_WATER);
	levelgrid[11][15]->settype(Tile::TT_WATER);
	levelgrid[3][15]->settype(Tile::TT_ROCK);
	levelgrid[3][13]->settype(Tile::TT_ROCK);
	levelgrid[4][13]->settype(Tile::TT_ROCK);
	levelgrid[4][14]->settype(Tile::TT_ROCK);
	levelgrid[4][15]->settype(Tile::TT_ROCK);
	levelgrid[5][15]->settype(Tile::TT_ROCK);
	levelgrid[6][15]->settype(Tile::TT_ROCK);
	levelgrid[7][15]->settype(Tile::TT_ROCK);
	levelgrid[8][15]->settype(Tile::TT_ROCK);
	*levelgrid[40][3]=Tile::TT_DIRT;
	*levelgrid[4][17]=Tile::TT_DIRT;
	*levelgrid[17][17]=Tile::TT_DIRT;
}*/
