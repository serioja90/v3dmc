/**
 * @file figures.c
 * This file is used for the 'libfigures.so' dynamic library creation
 * and contains the definitions of the methods that allows to initialize
 * and create new instances of the structures declared inside the 
 * 'include/figures.h' header.
 * @author Groza Sergiu
 * @version 0.1.0
 * @brief The file that contains the definitions of the functions declared in 'figures.h'.
 */

/**
 * @include "figures.h"
 * @include <GL/gl.h>
 * @include <stdio.h>
 * @include <stdlib.h>
 */
 #include "figures.h"
 #include <GL/gl.h>
 #include <stdio.h>
 #include <stdlib.h>

/**
 * @fn clampf(GLfloat value)
 * This function check if the passed value is between 0.0 and 1.0 and if not
 * returns a float value in this interval. If the value is greater than 1.0, than
 * the function returns 1.0 and if the passed value is smaller than 0.0, returns 0.0.
 * @param value the value to normalize
 * @return a GLclampf value between 0.0 and 1.0
 */
GLclampf clampf(GLfloat value){
	if(value>1.0){
		return 1.0;
	}else if(value<0.0){
		return 0.0;
	}
	return value;
}

/**
 * @fn RGBi(GLint r, GLint g, GLint b)
 * This function create a COLOR object from 3 integers.
 * @param r the red component's value
 * @param g the green component's value
 * @param b the green component's value
 * @return a COLOR object
 */
COLOR RGBi(GLint r, GLint g, GLint b){
	COLOR color;
	color.r = clampf((float)r/255.0);
	color.g = clampf((float)g/255.0);
	color.b = clampf((float)b/255.0);
	color.a = 0.0;
	return color;
} 

/**
 * @fn RGBf(GLfloat r, GLfloat g, GLfloat b)
 * This function create a COLOR object by 3 float.
 * @param r the red component's value
 * @param g the green component's value
 * @param b the green component's value
 * @return a COLOR object
 */
COLOR RGBf(GLclampf r, GLclampf g, GLclampf b){
	COLOR color;
	color.r = clampf(r);
	color.g = clampf(g);
	color.b = clampf(b);
	color.a = 0.0;
	return color;
}

/**
 * @gn RGBAi(GLint r, GLint g, GLint b, GLint a)
 * This function a COLOR object by 4 integers.
 * @param r the red component's value
 * @param g the green component's value
 * @param b the green component's value
 * @param a the green component's value
 * @return a COLOR object
 */
COLOR RGBAi(GLint r, GLint g, GLint b, GLint a){
	COLOR color;
	color.r = clampf((float)r/255.0);
	color.g = clampf((float)g/255.0);
	color.b = clampf((float)b/255.0);
	color.a = clampf((float)a/255.0);
	return color;
}

/**
 * @gn RGBAf(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
 * This function a COLOR object by 4 float.
 * @param r the red component's value
 * @param g the green component's value
 * @param b the green component's value
 * @param a the green component's value
 * @return a COLOR object
 */
COLOR RGBAf(GLclampf r, GLclampf g, GLclampf b, GLclampf a){
	COLOR color;
	color.r = clampf(r);
	color.g = clampf(g);
	color.b = clampf(b);
	color.a = clampf(a);
	return color;
}

/**
 * @fn point(GLfloat x, GLfloat y, GLfloat z, COLOR color)
 * This function create a POINT object.
 * @param x a float that represents the x coordinate of the point
 * @param y a float that represents the y coordinate of the point
 * @param z a float that represents the z coordinate of the point
 * @return a POINT object
 */
POINT point(GLfloat x, GLfloat y, GLfloat z, COLOR color){
	POINT point;
	point.x = x;
	point.y = y;
	point.z = z;
	point.color = color;
	return point;
}

/**
 * @fn line(POINT a, POINT b)
 * This function create a LINE object.
 * @param a the start point of the line
 * @param b the end point of the line
 * @return a POINT object
 */
LINE line(POINT a, POINT b){
	LINE line;
	line.a = a;
	line.b = b;
	return line;
}

/**
 * @fn triangle(POINT a, POINT b, POINT c, TEXTURE texture)
 * This function create a TRIANGLE object.
 * @param a the first vertex
 * @param b the second vertex
 * @param c the third vertex
 * @param texture the texture to map on the triangle
 * @return a TRIANGLE object
 */
TRIANGLE triangle(POINT a, POINT b, POINT c, TEXTURE texture){
	TRIANGLE triangle;
	triangle.a = a;
	triangle.b = b;
	triangle.c = c;
	triangle.texture = texture;
	return triangle;
}

/**
 * @fn quad(POINT a, POINT b, POINT c, POINT d, TEXTURE texture)
 * This function create a QUAD object.
 * @param a the first vertex
 * @param b the second vertex
 * @param c the third vertex
 * @param d the fourth vertex
 * @param texture the texture to map on the quad
 * @return a QUAD object
 */
QUAD quad(POINT a, POINT b, POINT c, POINT d, TEXTURE texture){
	QUAD quad;
	quad.a = a;
	quad.b = b;
	quad.c = c;
	quad.d = d;
	quad.texture = texture;
	return quad;
}

/**
 * @fn object()
 * This function create an empty initialized OBJECT.
 * @return a OBJECT
 */
OBJECT object(){
	OBJECT object;
	object.npoints = 0;
	object.nlines = 0;
	object.ntriangles = 0;
	object.nquads = 0;
	object.points = NULL;
	object.lines = NULL;
	object.triangles = NULL;
	object.quads = NULL;
	return object;
}

/**
 * @fn addPoint(OBJECT* obj, POINT point)
 * This funtion adds a new POINT to an object.
 * @param [out] obj the object to which to add the new POINT
 * @param point the point to add to the object
 */
void addPoint(OBJECT* obj, POINT point){
	if(obj!=NULL){
		GLint i;
		POINT* _points;
		obj->npoints++;
		_points = obj->points;
		obj->points = (POINT*)calloc(obj->npoints,sizeof(POINT));
		for(i=0;i<obj->npoints-1;i++){
			*(obj->points + i) = *(_points + i); 
		}
		*(obj->points + obj->npoints-1) = point;
		if(_points!=NULL){
			free(_points);
		}
	}
}

/**
 * @fn addLine(OBJECT* obj, LINE line)
 * This function adds a new LINE to an object
 * @param [out] obj the object to which to add the new LINE
 * @param line the line to add to the object
 */
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

/**
 * @fn addTriangle(OBJECT* obj, TRIANGLE triangle)
 * This function add a new TIANGLE to the object.
 * @param [out] obj the object to which to add the new TRIANGLE
 * @param triangle the triangle to add to the object
 */
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