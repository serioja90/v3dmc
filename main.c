#include "lib/figures.c"
#include <stdio.h>

int main(int argc, char** argv){
	OBJECT obj = object();
	int i;
	POINT p;
	POINTLIST element=NULL;
	for(i=0;i<1000;i++){
		p = point(i,i+1,i+2,RGBi(100,100,100));
		addPoint(&obj,p);
		element = getPointListElement(obj,i);
		p = element->point;
		//printf("%d. %f,%f,%f\n",i+1,p.x,p.y,p.z);
	}
	saveObject(obj,"models/points.mdl");
	return 0;
}