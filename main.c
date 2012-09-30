#include "lib/figures.c"
#include <stdio.h>

int main(int argc, char** argv){
	OBJECT obj = object();
	int i;
	for(i=0;i<1000;i++){
		POINT p = point(i,i+1,i+2,RGBi(100,100,100));
		POINT p2 = point(i,i-1,i-2,RGBi(255,255,255));
		addPoint(&obj,p);
		addLine(&obj,line(p,p2));
		printf("%d. %f,%f,%f\n",i,(*(obj.points+i)).x,(*(obj.points+i)).y,(*(obj.points+i)).z);
	}
	return 0;
}