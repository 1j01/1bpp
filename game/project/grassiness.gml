///ruins=1~~!!!!!!!!;
var s,i,j,sw,sh,w,h,ruins;


w=12;h=w;
ruins=1;
circley=0//random(1);
angley=4//irandom(3)+3;
symetry=1//random(1);
gapey=0//random(1);
l=3//irandom_range(2,7);

/*
w=32;h=w;
ruins=0;
circley=0//random(1);
angley=4//irandom(3)+3;
symetry=1//random(1);
gapey=1//random(1);
l=1//irandom_range(2,7);
*/

sw=(500 div w)*w;
sh=(200 div h)*h;
//s=
if (variable_global_exists("finalSurf4c3")){
	if (surface_exists(global.finalSurf4c3)) {
		surface_free(global.finalSurf4c3);
	}
}

global.finalSurf4c3 = surface_create(sw,sh);
surface_set_target(global.finalSurf4c3);
draw_clear_alpha(0,0.2);
draw_set_color(c_white);
if ruins draw_clear_alpha(c_gray,1);
surface_reset_target();

for(j=0;j<sh;j+=h){
	/* /
	circley=random(1);
	angley=irandom(3)+3;
	symetry=random(1);
	gapey=random(1);
	l=irandom_range(2,7);
	/* */
	for(i=0;i<sw;i+=w){
		s=surface_create(w,h);
		surface_set_target(s);
		draw_clear_alpha(0,0);


		var xx,yy,xf,yf,c,d;
		c=w/2;
		d=360/angley*irandom(angley);
		yy=0;yf=0;
		xx=0;xf=0;
		while(random(50)){

			d+=360/angley*irandom_range(angley/2,-angley/2)+irandom_range(angley/3,-angley/3);
			xx+=lengthdir_x(l,d);
			yy+=lengthdir_y(l,d);

			if(xx<-c || yy<-c || xx>c || yy>c)break;
			//draw_set_color(c_white);
			if(random(1)>gapey){
				if random(1)>0.5 draw_line(c+xx,c+yy,c+xf,c+yf);
							else draw_line(c-xx,c+yy,c-xf,c+yf);
			}else if(random(1)<symetry){
				draw_line(c-xx,c+yy,c-xf,c+yf);draw_line(c+xx,c+yy,c+xf,c+yf);
			}

			//		if(random(1)>symetry)draw_line(c-xx,yy,c-xf,yf);
			//else if(random(1)>symetry)draw_line(c+xx,yy,c+xf,yf);
			//else if(random(1)<gapey){
			//	if random(1) draw_line(c+xx,yy,c+xf,yf);
			//				 	else draw_line(c-xx,yy,c-xf,yf);
			//}
			xf=xx;yf=yy;
		}
		surface_set_target(global.finalSurf4c3);
		draw_surface(s,i,j);
		surface_free(s);
	}
}
surface_reset_target();
