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
COLOR RGBi(GLint r, GLint g, GLint b){
	COLOR color;
	color.r = clampf((float)r/255.0);
	color.g = clampf((float)g/255.0);
	color.b = clampf((float)b/255.0);
	color.a = 0.0;
	return color;
} 

/***********************************************************/
COLOR RGBf(GLclampf r, GLclampf g, GLclampf b){
	COLOR color;
	color.r = clampf(r);
	color.g = clampf(g);
	color.b = clampf(b);
	color.a = 0.0;
	return color;
}

/***********************************************************/
COLOR RGBAi(GLint r, GLint g, GLint b, GLint a){
	COLOR color;
	color.r = clampf((float)r/255.0);
	color.g = clampf((float)g/255.0);
	color.b = clampf((float)b/255.0);
	color.a = clampf((float)a/255.0);
	return color;
}

/***********************************************************/
COLOR RGBAf(GLclampf r, GLclampf g, GLclampf b, GLclampf a){
	COLOR color;
	color.r = clampf(r);
	color.g = clampf(g);
	color.b = clampf(b);
	color.a = clampf(a);
	return color;
}

/***********************************************************/
POINT point(GLfloat x, GLfloat y, GLfloat z, COLOR color){
	POINT point;
	point.x = x;
	point.y = y;
	point.z = z;
	point.color = color;
	return point;
}

/***********************************************************/
LINE line(POINT a, POINT b){
	LINE line;
	line.a = a;
	line.b = b;
	return line;
}

/***********************************************************/
TRIANGLE triangle(POINT a, POINT b, POINT c, TEXTURE texture){
	TRIANGLE triangle;
	triangle.a = a;
	triangle.b = b;
	triangle.c = c;
	triangle.texture = texture;
	return triangle;
}

/***********************************************************/
QUAD quad(POINT a, POINT b, POINT c, POINT d, TEXTURE texture){
	QUAD quad;
	quad.a = a;
	quad.b = b;
	quad.c = c;
	quad.d = d;
	quad.texture = texture;
	return quad;
}

/***********************************************************/
OBJECT object(){
	OBJECT object;
	object.npoints = 0;
	object.nlines = 0;
	object.ntriangles = 0;
	object.nquads = 0;
	object.points = NULL;
	object.last_point = NULL;
	object.lines = NULL;
	object.triangles = NULL;
	object.quads = NULL;
	return object;
}

/***********************************************************/
void addPoint(OBJECT* obj, POINT point){
	if(obj!=NULL){
		obj->npoints++;
		if(obj->points==NULL){
			obj->points = (POINTLIST)malloc(sizeof(PointListElement));
			obj->points->point = point;
			obj->points->prev = NULL;
			obj->points->next = NULL;
			obj->last_point = obj->points;
		}else{
			obj->last_point->next = (POINTLIST)malloc(sizeof(PointListElement));
			obj->last_point->next->prev = obj->last_point;
			obj->last_point = obj->last_point->next;
			obj->last_point->point = point;
			obj->last_point->next = NULL; 
		}
	}
}

/***********************************************************/
POINTLIST getPointListElement(OBJECT obj,GLint index){
	GLint i;
	if(index < 0 || index>obj.npoints){
		return NULL;
	}
	// split the search in 2 parts
	if(index<=obj.npoints/2){
		// if the searched element is in the lower part of list
		POINTLIST list = obj.points;
		i = 0;
		while(list!=NULL && i!=index){
			list = list->next;
			i++;
		}
		return list;
	}else{
		// if the searched element is in the upper part of list
		POINTLIST list = obj.last_point;
		i=obj.npoints-1;
		while(list!=NULL && i!=index){
			list = list->prev;
			i--;
		}
		return list;
	}
}

/***********************************************************/
void addLine(OBJECT* obj, LINE line){
	if(obj!=NULL){
		GLint i;
		LINE* _lines;
		obj->nlines++;
		_lines = obj->lines;
		obj->lines = (LINE*)calloc(obj->nlines,sizeof(LINE));
		for(i=0;i<obj->nlines-1;i++){
			*(obj->lines + i) = *(_lines + i);
		}
		*(obj->lines + obj->nlines-1) = line;
		if(_lines!=NULL){
			free(_lines);
		}
	}
}

/***********************************************************/
void addTriangle(OBJECT* obj, TRIANGLE triangle){
	if(obj!=NULL){
		GLint i;
		TRIANGLE* _triangles;
		obj->ntriangles++;
		_triangles = obj->triangles;
		obj->triangles = (TRIANGLE*)calloc(obj->ntriangles,sizeof(TRIANGLE));
		for(i=0;i<obj->ntriangles-1;i++){
			*(obj->triangles + i) = *(_triangles + i);
		}
		*(obj->triangles + obj->ntriangles - 1) = triangle;
		if(_triangles!=NULL){
			free(_triangles);
		}
	}
}

/***********************************************************/
void addQuad(OBJECT* obj, QUAD quad){
	if(obj!=NULL){
		GLint i;
		QUAD* _quads;
		obj->nquads++;
		_quads = obj->quads;
		obj->quads = (QUAD*)calloc(obj->nquads,sizeof(QUAD));
		for(i=0;i<obj->nquads-1;i++){
			*(obj->quads + i) = *(_quads + i);
		}
		*(obj->quads + obj->nquads - 1) = quad;
		if(_quads!=NULL){
			free(_quads);
		}
	}
}

/***********************************************************/
TEXCOORD texcoord(GLclampf x, GLclampf y){
	TEXCOORD texcoord;
	texcoord.x = clampf(x);
	texcoord.y = clampf(y);
	return texcoord;
}

/***********************************************************/
TEXTURE texture(GLchar* name, TEXCOORD a, TEXCOORD b, TEXCOORD c, TEXCOORD d){
	TEXTURE texture;
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
void saveObject(OBJECT obj, GLchar *filename){
	FILE* file;
	GLint i;
	POINTLIST points;
	file = fopen(filename,"w");
	if(file!=NULL){
		fwrite(&(obj.npoints),sizeof(int),1,file);
		fwrite(&(obj.nlines),sizeof(int),1,file);
		fwrite(&(obj.ntriangles),sizeof(int),1,file);
		fwrite(&(obj.nquads),sizeof(int),1,file);
		points = obj.points;
		for(i=0;i<obj.npoints;i++){
			fwrite(&(points->point),sizeof(POINT),1,file);
			points = points->next;
		}
		for(i=0;i<obj.nlines;i++){
			fwrite((obj.lines+i),sizeof(LINE),1,file);
		}
		for(i=0;i<obj.ntriangles;i++){
			fwrite((obj.triangles+i),sizeof(TRIANGLE),1,file);
		}
		for(i=0;i<obj.nquads;i++){
			fwrite((obj.quads+i),sizeof(QUAD),1,file);
		}
	}
}