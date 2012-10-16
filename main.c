#include "lib/figures.c"
#include <stdio.h>

int main(int argc, char** argv){
	v3dmc_object obj = load_object("models/point.mdl");
	v3dmc_point_list element = get_point_list_element(obj,1);
	v3dmc_point p = element->point;
	printf("%f,%f,%f\n",p.x,p.y,p.z);
	if(p.has_color){
		printf("The point has a color\n");
	}else{
		printf("The point doesn't have a color\n");
	}
	
	// int i;
	// v3dmc_object obj = object();
	// v3dmc_point p = create_point3p(3.5f,4.2f,-5.1f);
	// for(i=0;i<100;i++){
	// 	add_point(&obj,p);
	// }
	// save_object(obj,"models/point.mdl");
	return 0;
}