/**
 * This file contains the structure definitions of the primitives
 * that will be used as the basic tools for models designing.
 */

#include <GL/gl.h>

/**
 * The structure for containing color data.
 * All the components values will be stored as float data, because
 * by float we can have an better definition of the color.
 */
typedef struct _color{
	GLfloat r; /* red component */
	GLfloat g; /* green component */
	GLfloat b; /* blue component */
}COLOR;

/**
 * The structure that allows to contain a point info.
 */
typedef struct _point{
	GLfloat x; /* x coordinate */
	GLfloat y; /* y coordinate */
	GLfloat z; /* z coordinate */
	COLOR color; /* the point color */
}POINT;

/**
 * The structure for storing the line data.
 * A line has a start point, an end point and a color.
 */
typedef struct _line{
	POINT a; /* start point */
	POINT b; /* end point */
	COLOR color; /* the line color */
}LINE;

/**
 * A structure for storing texture coordinates.
 */
typedef struct _texcoord{
	GLfloat x; /* x coordinate */
	GLfloat y; /* y coordinate */
}TEXCOORD;

/**
 * A structure for storing texture info.
 * Having a texture structure will allow to load the texture only for one time and
 * use it for more primitives.
 */
typedef struct _texture{
	TEXCOORD a; /* upper-left corner coordinates */
	TEXCOORD b; /* upper-right corner coordinates */
	TEXCOORD c; /* lower-right corner coordinates */
	TEXCOORD d; /* lower-left corner coordinates */
	GLchar* name[255]; /* for now we will use a string of a fixed length for the texture */
}TEXTURE;

/**
 * The structure for storing the triangle data. 
 */
typedef struct _triangle{
	POINT a;
	POINT b;
	POINT c;
	COLOR color; /* the color of the triangle */
	TEXTURE texture; /* the texture with coordinates */
}TRIANGLE;

/**
 * The structure for storing quad info.
 */
typedef struct _quad{
	POINT a;
	POINT b;
	POINT c;
	POINT d;
	COLOR color;
	TEXTURE texture;
}QUAD;

/**
 * The object structure that will be used for containing an object information.
 * An object contains primitive structures(points,lines,...)
 */
typedef struct _object{
	GLint npoints; /* the number of points */
	GLint nlines; /* the number of lines */
	GLint ntriangles; /* the number of triangles */
	GLint nquads; /* the number of quads */
	POINT* points; /* the pointer to the vector that contasin object's points */
	LINE* lines; /* the pointer to the vector that contasin object's lines */
	TRIANGLE* triangles; /* the pointer to the vector that contasin object's triangles */
	QUAD* quads; /* the pointer to the vector that contasin object's quads */
}OBJECT;