 #include "figures.h"
 #include <GL/gl.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

/***********************************************************/
GLclampf clampf(GLfloat value){
	if(value>1.0){
		return 1.0;
	}else if(value<0.0){
		return 0.0;
	}
	return value;
}

/***********************************************************/
v3dmc_color rgbi(GLint r, GLint g, GLint b){
	v3dmc_color color;
	color.r = clampf((float)r/255.0);
	color.g = clampf((float)g/255.0);
	color.b = clampf((float)b/255.0);
	color.a = 1.0;
	return color;
} 

/***********************************************************/
v3dmc_color rgbf(GLclampf r, GLclampf g, GLclampf b){
	v3dmc_color color;
	color.r = clampf(r);
	color.g = clampf(g);
	color.b = clampf(b);
	color.a = 1.0;
	return color;
}

/***********************************************************/
v3dmc_color rgbai(GLint r, GLint g, GLint b, GLint a){
	v3dmc_color color;
	color.r = clampf((float)r/255.0);
	color.g = clampf((float)g/255.0);
	color.b = clampf((float)b/255.0);
	color.a = clampf((float)a/255.0);
	return color;
}

/***********************************************************/
v3dmc_color rgbaf(GLclampf r, GLclampf g, GLclampf b, GLclampf a){
	v3dmc_color color;
	color.r = clampf(r);
	color.g = clampf(g);
	color.b = clampf(b);
	color.a = clampf(a);
	return color;
}

/***********************************************************/
v3dmc_point point(GLfloat x, GLfloat y, GLfloat z, v3dmc_color color){
	v3dmc_point point;
	point.x = x;
	point.y = y;
	point.z = z;
	point.color = color;
	return point;
}

/***********************************************************/
v3dmc_line line(v3dmc_point a, v3dmc_point b){
	v3dmc_line line;
	line.a = a;
	line.b = b;
	return line;
}

/***********************************************************/
v3dmc_triangle triangle(v3dmc_point a, v3dmc_point b, v3dmc_point c, v3dmc_texture texture){
	v3dmc_triangle triangle;
	triangle.a = a;
	triangle.b = b;
	triangle.c = c;
	triangle.texture = texture;
	return triangle;
}

/***********************************************************/
v3dmc_quad quad(v3dmc_point a, v3dmc_point b, v3dmc_point c, v3dmc_point d, v3dmc_texture texture){
	v3dmc_quad quad;
	quad.a = a;
	quad.b = b;
	quad.c = c;
	quad.d = d;
	quad.texture = texture;
	return quad;
}

/***********************************************************/
v3dmc_object object(){
	v3dmc_object object;
	object.npoints = 0;
	object.nlines = 0;
	object.ntriangles = 0;
	object.nquads = 0;
	object.points = NULL;
	object.last_point = NULL;
	object.lines = NULL;
	object.last_line = NULL;
	object.triangles = NULL;
	object.quads = NULL;
	object.last_quad = NULL;
	return object;
}

/***********************************************************/
void add_point(v3dmc_object* obj, v3dmc_point point){
	if(obj!=NULL){
		obj->npoints++;
		if(obj->points==NULL){
			obj->points = (v3dmc_point_list)malloc(sizeof(v3dmc_point_list_element));
			obj->points->point = point;
			obj->points->prev = NULL;
			obj->points->next = NULL;
			obj->last_point = obj->points;
		}else{
			obj->last_point->next = (v3dmc_point_list)malloc(sizeof(v3dmc_point_list_element));
			obj->last_point->next->prev = obj->last_point;
			obj->last_point = obj->last_point->next;
			obj->last_point->point = point;
			obj->last_point->next = NULL; 
		}
	}
}

/***********************************************************/
v3dmc_point_list get_point_list_element(v3dmc_object obj,GLint index){
	GLint i;
	if(index < 0 || index>obj.npoints){
		return NULL;
	}
	// split the search in 2 parts
	if(index<=obj.npoints/2){
		// if the searched element is in the lower part of list
		v3dmc_point_list list = obj.points;
		i = 0;
		while(list!=NULL && i!=index){
			list = list->next;
			i++;
		}
		return list;
	}else{
		// if the searched element is in the upper part of list
		v3dmc_point_list list = obj.last_point;
		i=obj.npoints-1;
		while(list!=NULL && i!=index){
			list = list->prev;
			i--;
		}
		return list;
	}
}

/***********************************************************/
void add_line(v3dmc_object* obj, v3dmc_line line){
	if(obj!=NULL){
		obj->nlines++;
		if(obj->lines==NULL){
			obj->lines = (v3dmc_line_list)malloc(sizeof(v3dmc_line_list_element));
			obj->lines->line = line;
			obj->lines->prev = NULL;
			obj->lines->next = NULL;
			obj->last_line = obj->lines;
		}else{
			obj->last_line->next = (v3dmc_line_list)malloc(sizeof(v3dmc_line_list_element));
			obj->last_line->next->prev = obj->last_line;
			obj->last_line = obj->last_line->next;
			obj->last_line->line = line;
			obj->last_line->next = NULL; 
		}
	}
}

/***********************************************************/
v3dmc_line_list get_line_list_element(v3dmc_object obj, GLint index){
	GLint i;
	if(index < 0 || index>obj.nlines){
		return NULL;
	}
	// split the search in 2 parts
	if(index<=obj.nlines/2){
		// if the searched element is in the lower part of list
		v3dmc_line_list list = obj.lines;
		i = 0;
		while(list!=NULL && i!=index){
			list = list->next;
			i++;
		}
		return list;
	}else{
		// if the searched element is in the upper part of list
		v3dmc_line_list list = obj.last_line;
		i=obj.nlines-1;
		while(list!=NULL && i!=index){
			list = list->prev;
			i--;
		}
		return list;
	}
}

/***********************************************************/
void add_triangle(v3dmc_object* obj, v3dmc_triangle triangle){
	if(obj!=NULL){
		obj->ntriangles++;
		if(obj->triangles==NULL){
			obj->triangles = (v3dmc_triangle_list)malloc(sizeof(v3dmc_triangle_list_element));
			obj->triangles->triangle = triangle;
			obj->triangles->prev = NULL;
			obj->triangles->next = NULL;
			obj->last_triangle = obj->triangles;
		}else{
			obj->last_triangle->next = (v3dmc_triangle_list)malloc(sizeof(v3dmc_triangle_list_element));
			obj->last_triangle->next->prev = obj->last_triangle;
			obj->last_triangle = obj->last_triangle->next;
			obj->last_triangle->triangle = triangle;
			obj->last_triangle->next = NULL; 
		}
	}
}

/***********************************************************/
v3dmc_triangle_list get_triangle_list_element(v3dmc_object obj, GLint index){
	GLint i;
	if(index < 0 || index>obj.ntriangles){
		return NULL;
	}
	// split the search in 2 parts
	if(index<=obj.ntriangles/2){
		// if the searched element is in the lower part of list
		v3dmc_triangle_list list = obj.triangles;
		i = 0;
		while(list!=NULL && i!=index){
			list = list->next;
			i++;
		}
		return list;
	}else{
		// if the searched element is in the upper part of list
		v3dmc_triangle_list list = obj.last_triangle;
		i=obj.ntriangles-1;
		while(list!=NULL && i!=index){
			list = list->prev;
			i--;
		}
		return list;
	}
}

/***********************************************************/
void add_quad(v3dmc_object* obj, v3dmc_quad quad){
	if(obj!=NULL){
		obj->nquads++;
		if(obj->quads==NULL){
			obj->quads = (v3dmc_quad_list)malloc(sizeof(v3dmc_quad_list_element));
			obj->quads->quad = quad;
			obj->quads->prev = NULL;
			obj->quads->next = NULL;
			obj->last_quad = obj->quads;
		}else{
			obj->last_quad->next = (v3dmc_quad_list)malloc(sizeof(v3dmc_quad_list_element));
			obj->last_quad->next->prev = obj->last_quad;
			obj->last_quad = obj->last_quad->next;
			obj->last_quad->quad = quad;
			obj->last_quad->next = NULL; 
		}
	}
}

/***********************************************************/
v3dmc_quad_list get_quad_list_element(v3dmc_object obj, GLint index){
	GLint i;
	if(index < 0 || index>obj.nquads){
		return NULL;
	}
	// split the search in 2 parts
	if(index<=obj.nquads/2){
		// if the searched element is in the lower part of list
		v3dmc_quad_list list = obj.quads;
		i = 0;
		while(list!=NULL && i!=index){
			list = list->next;
			i++;
		}
		return list;
	}else{
		// if the searched element is in the upper part of list
		v3dmc_quad_list list = obj.last_quad;
		i=obj.nquads-1;
		while(list!=NULL && i!=index){
			list = list->prev;
			i--;
		}
		return list;
	}
}

/***********************************************************/
v3dmc_texcoord texcoord(GLclampf x, GLclampf y){
	v3dmc_texcoord texcoord;
	texcoord.x = clampf(x);
	texcoord.y = clampf(y);
	return texcoord;
}

/***********************************************************/
v3dmc_texture texture(GLchar* name, v3dmc_texcoord a, v3dmc_texcoord b, v3dmc_texcoord c, v3dmc_texcoord d){
	v3dmc_texture texture;
	texture.name[0] = '\0';
	if(name!=NULL){
		strcpy(texture.name,name);
	}
	texture.a = a;
	texture.b = b;
	texture.c = c;
	texture.d = d;
	return texture;
}

/***********************************************************/
void save_object(v3dmc_object obj, GLchar *filename){
	FILE* file;
	GLint i;
	v3dmc_point_list points = obj.points;
	v3dmc_line_list lines = obj.lines;
	v3dmc_triangle_list triangles = obj.triangles;
	v3dmc_quad_list quads = obj.quads;
	file = fopen(filename,"w");
	if(file!=NULL){
		fwrite(&(obj.npoints),sizeof(int),1,file);
		fwrite(&(obj.nlines),sizeof(int),1,file);
		fwrite(&(obj.ntriangles),sizeof(int),1,file);
		fwrite(&(obj.nquads),sizeof(int),1,file);
		for(i=0;i<obj.npoints;i++){
			fwrite(&(points->point),sizeof(v3dmc_point),1,file);
			points = points->next;
		}
		for(i=0;i<obj.nlines;i++){
			fwrite(&(lines->line),sizeof(v3dmc_line),1,file);
			lines = lines->next;
		}
		for(i=0;i<obj.ntriangles;i++){
			fwrite(&(triangles->triangle),sizeof(v3dmc_triangle),1,file);
			triangles = triangles->next;
		}
		for(i=0;i<obj.nquads;i++){
			fwrite(&(quads->quad),sizeof(v3dmc_quad),1,file);
			quads = quads->next;
		}
		fclose(file);
	}
}

/***********************************************************/
v3dmc_object load_object(GLchar *filename){
	FILE *file;
	GLint i,npoints,nlines,ntriangles,nquads;
	v3dmc_object obj = object();
	v3dmc_point p;
	v3dmc_line l;
	v3dmc_triangle t;
	v3dmc_quad q;
	file = fopen(filename,"r");
	if(file!=NULL){
		fread(&npoints,sizeof(int),1,file);
		fread(&nlines,sizeof(int),1,file);
		fread(&ntriangles,sizeof(int),1,file);
		fread(&nquads,sizeof(int),1,file);
		for(i=0;i<npoints;i++){
			fread(&p,sizeof(v3dmc_point),1,file);
			add_point(&obj,p);
		}
		for(i=0;i<nlines;i++){
			fread(&l,sizeof(v3dmc_line),1,file);
			add_line(&obj,l);
		}
		for(i=0;i<ntriangles;i++){
			fread(&t,sizeof(v3dmc_triangle),1,file);
			add_triangle(&obj,t);
		}
		for(i=0;i<nquads;i++){
			fread(&q,sizeof(v3dmc_quad),1,file);
			add_quad(&obj,q);
		}
		fclose(file);
	}
	return obj;
}