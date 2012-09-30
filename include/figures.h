/**
 * @file figures.h
 *
 * This file contains the structure definitions of the primitives
 * that will be used as the basic tools for models designing. Also here
 * are placed the declarations of the functions defined in the 'lib/figures.c'.
 *
 * @brief Definitions of the primitives structures.
 *
 * @author Groza Sergiu
 * @version 0.1.0
 */

/**
 * @include GL/gl.h
 */
#include <GL/gl.h>

/*!
 * @struct COLOR
 * The COLOR is a structure created for storing the color data in a single
 * variable. It is used for setting the color of primitives.
 * All the components values will be stored as float data, because
 * by float we can have an better definition of the color.
 * @brief The structure that contains the info of a color.
 */
typedef struct{
	/** The red component's value of the color. Should have values between 0.0-1.0. */
	GLfloat r;
	/** The green component's value of the color. Should have values between 0.0-1.0. */
	GLfloat g;
	/** The blue component's value of the color. Should have values between 0.0-1.0. */
	GLfloat b;
	/** The alfa component's value of the color. Should have values between 0.0-1.0. */
	GLfloat a;
}COLOR;

/**
 * @struct POINT
 * This structure allows to store the coordinates of a point in the 3D space.
 * It also contains the info about the color of the point in an COLOR attribute.
 * All the coordinates are expressed as GLfloats, because it is easier to use
 * with OpenGL library.
 * @brief The structure that allows to contain a point info.
 */
typedef struct{
	/** The x coordinate of the point */
	GLfloat x;
	/** The y coordinate of the point */
	GLfloat y;
	/** The z coordinate of the point */
	GLfloat z;
	/** The point's color */
	COLOR color;
}POINT;

/**
 * @struct LINE
 * This structure allows to store a line information. We need 2 POINT attributes
 * to define a line. The color information is stored in the POINT structure, so we
 * can use it to define the line color. Also this allows to have different color for
 * start and end points.
 * @brief A structure for storing the line info.
 */
typedef struct{
	/** The line start point */
	POINT a;
	/** The line end point */
	POINT b;
}LINE;

/**
 * @struct TEXCOORD
 * This is the structure used for store the coordinates of texture coners, that allows to 
 * map parts of texture on primitives like triangles and quads.
 * @brief A structure for storing texture coordinates.
 */
typedef struct{
	/** The x coordinate. Should have values between 0.0-1.0. */
	GLfloat x;
	/** The y coordinate. Should have values between 0.0-1.0. */
	GLfloat y;
}TEXCOORD;

/**
 * @struct TEXTURE
 * A structure for storing texture info.
 * Having a texture structure will allow to load the texture only for one time and
 * use it for more primitives.
 * @brief A structure that allows to contain the info of a texture.
 */
typedef struct{
	/** Upper-left corner coordinates. */
	TEXCOORD a;
	/** Upper-right corner coordinates. */
	TEXCOORD b;
	/** Lower-right corner coordinates. */
	TEXCOORD c;
	/** Lower-left corner coordinates. */
	TEXCOORD d;
	/** The texture's name. */
	GLchar* name[255];
}TEXTURE;

/**
 * @struct TRIANGLE
 * The TRIANGLE structure allows to store data about a triangle primitive. This
 * structure also allows to store the texture info.
 * @brief A structure that allows to contain the info of a triangle.
 */
typedef struct{
	/** The first triangle vertex. */
	POINT a;
	/** The second triangle vertex. */
	POINT b;
	/** The third triangle vertex. */
	POINT c;
	/** The texture to map on the triangle. */
	TEXTURE texture;
}TRIANGLE;

/**
 * @struct QUAD
 * The QUAD structure allows to store data of a quad, including the texture.
 * @brief A structure that allows to contain the info of a quad.
 */
typedef struct{
	/** The first triangle vertex. */
	POINT a;
	/** The second triangle vertex. */
	POINT b;
	/** The third triangle vertex. */
	POINT c;
	/** The fourth triangle vertex. */
	POINT d;
	/** The texture to map on the quad */
	TEXTURE texture;
}QUAD;

/**
 * @struct OBJECT
 * The OBJECT structure group more primitives(points,lines,...) in a single
 * object, that allows to have a single object for a model with all the necessary
 * primitives.
 * @brief A structure that allows to contain the info of an object.
 */
typedef struct{
	/** The number of points in the object */
	GLint npoints;
	/** The number of lines in the object */
	GLint nlines;
	/** The number of triangles in the object */
	GLint ntriangles;
	/** The number of quads in the object */
	GLint nquads;
	/** The pointer to the vector of points */
	POINT* points;
	/** The pointer to the vector of lines */
	LINE* lines;
	/** The pointer to the vector of triangles */
	TRIANGLE* triangles;
	/** The pointer to the vector of quads */
	QUAD* quads;
}OBJECT;

/**
 * @fn RGBi(GLint r, GLint g, GLint b)
 * This function create a COLOR object from 3 integers.
 * @param r the red component's value
 * @param g the green component's value
 * @param b the green component's value
 * @return a COLOR object
 */
COLOR RGBi(GLint r, GLint g, GLint b);

/**
 * @fn RGBf(GLfloat r, GLfloat g, GLfloat b)
 * This function create a COLOR object by 3 float.
 * @param r the red component's value
 * @param g the green component's value
 * @param b the green component's value
 * @return a COLOR object
 */
COLOR RGBf(GLfloat r, GLfloat g, GLfloat b);

/**
 * @gn RGBAi(GLint r, GLint g, GLint b, GLint a)
 * This function a COLOR object by 4 integers.
 * @param r the red component's value
 * @param g the green component's value
 * @param b the green component's value
 * @param a the green component's value
 * @return a COLOR object
 */
COLOR RGBAi(GLint r, GLint g, GLint b, GLint a);

/**
 * @gn RGBAf(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
 * This function a COLOR object by 4 float.
 * @param r the red component's value
 * @param g the green component's value
 * @param b the green component's value
 * @param a the green component's value
 * @return a COLOR object
 */
COLOR RGBAf(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

/**
 * @fn point(GLfloat x, GLfloat y, GLfloat z, COLOR color)
 * This function create a POINT object.
 * @param x a float that represents the x coordinate of the point
 * @param y a float that represents the y coordinate of the point
 * @param z a float that represents the z coordinate of the point
 * @return a POINT object
 */
POINT point(GLfloat x, GLfloat y, GLfloat z, COLOR color);

/**
 * @fn line(POINT a, POINT b)
 * This function create a LINE object.
 * @param a the start point of the line
 * @param b the end point of the line
 * @return a POINT object
 */
LINE line(POINT a, POINT b);

/**
 * @fn triangle(POINT a, POINT b, POINT c, TEXTURE texture)
 * This function create a TRIANGLE object.
 * @param a the first vertex
 * @param b the second vertex
 * @param c the third vertex
 * @param texture the texture to map on the triangle
 * @return a TRIANGLE object
 */
TRIANGLE triangle(POINT a, POINT b, POINT c, TEXTURE texture);

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
QUAD quad(POINT a, POINT b, POINT c, POINT d, TEXTURE texture);

/**
 * @fn object()
 * This function create an empty initialized OBJECT.
 * @return a OBJECT
 */
OBJECT object();

/**
 * @fn addPoint(OBJECT* obj, POINT point)
 * This funtion adds a new POINT to an object.
 * @param [out] obj the object to which to add the new POINT
 * @param point the point to add to the object
 */
void addPoint(OBJECT* obj, POINT point);

/**
 * @fn addLine(OBJECT* obj, LINE line)
 * This function adds a new LINE to an object
 * @param [out] obj the object to which to add the new LINE
 * @param line the line to add to the object
 */
void addLine(OBJECT* obj, LINE line);

/**
 * @fn addTriangle(OBJECT* obj, TRIANGLE triangle)
 * This function add a new TIANGLE to the object.
 * @param [out] obj the object to which to add the new TRIANGLE
 * @param triangle the triangle to add to the object
 */
void addTriangle(OBJECT* obj, TRIANGLE triangle);

/**
 * @fn addQuad(OBJECT* obj, QUAD quad)
 * This function add a new QUAD to the object.
 * @param [out] obj the object to which to add the new QUAD
 * @param quad the quad to add to the object
 */
void addQuad(OBJECT* obj, QUAD quad);