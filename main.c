#include "lib/figures.c"
#include <stdio.h>

int main(int argc, char** argv){
	OBJECT obj = object();
	int i;
	LINE l;
	POINT p;
	LINELIST line_element=NULL;
	POINTLIST point_element = NULL;
	for(i=0;i<100000;i++){
		POINT p1 = point(i,i+1,i+2,RGBi(100,100,100));
		POINT p2 = point(i,i-1,i-2,RGBi(100,100,100));
		addPoint(&obj,p1);
		addLine(&obj,line(p1,p2));
		line_element = getLineListElement(obj,i);
		l = line_element->line;
		point_element = getPointListElement(obj,i);
		p = point_element->point;
		//printf("%d. %f,%f,%f\n",i+1,p.x,p.y,p.z);
	}
	line_element = getLineListElement(obj,50000);
	l = line_element->line;
	point_element = getPointListElement(obj,50000);
	p = point_element->point;
	printf("%f,%f,%f\n",l.b.x,l.b.y,l.b.z);
	printf("%f,%f,%f\n",p.x,p.y,p.z);
	saveObject(obj,"models/lines.mdl");
	return 0;
}