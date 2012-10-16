#include "lib/figures.c"
#include <stdio.h>

int main(int argc, char** argv){
	// v3dmc_object obj = object();
	// int i;
	// v3dmc_line l;
	// v3dmc_point p;
	// v3dmc_line_list line_element=NULL;
	// v3dmc_point_list point_element = NULL;
	// for(i=0;i<100000;i++){
	// 	v3dmc_point p1 = point(i,i+1,i+2,rgbi(100,100,100));
	// 	v3dmc_point p2 = point(i,i-1,i-2,rgbi(100,100,100));
	// 	v3dmc_point p3 = point(i,i,i,rgbi(100,100,100));
	// 	v3dmc_point p4 = point(-i,-i,-i,rgbi(0,0,0));
	// 	v3dmc_texcoord coord = texcoord(0.0,0.0);
	// 	v3dmc_texture tex = texture(NULL,coord,coord,coord,coord);
	// 	add_point(&obj,p1);
	// 	add_line(&obj,line(p1,p2));
	// 	add_triangle(&obj,triangle(p1,p2,p3,tex));
	// 	add_quad(&obj,quad(p1,p2,p3,p4,tex));
	// 	line_element = get_line_list_element(obj,i);
	// 	l = line_element->line;
	// 	point_element = get_point_list_element(obj,i);
	// 	p = point_element->point;
	// 	//printf("%d. %f,%f,%f\n",i+1,p.x,p.y,p.z);
	// }
	// line_element = get_line_list_element(obj,50000);
	// l = line_element->line;
	// point_element = get_point_list_element(obj,50000);
	// p = point_element->point;
	// printf("%f,%f,%f\n",l.b.x,l.b.y,l.b.z);
	// printf("%f,%f,%f\n",p.x,p.y,p.z);
	// save_object(obj,"models/lines.mdl");

	v3dmc_object obj = load_object("models/lines.mdl");
	printf("%d\n",obj.nquads);
	v3dmc_quad_list element = get_quad_list_element(obj,50000);
	if(element!=NULL){
		v3dmc_quad q = element->quad;
		printf("%f,%f,%f\n",q.a.x,q.a.y,q.a.z);
		if(q.a.has_color){
			printf("The point has color\n");
		}
	}
	return 0;
}