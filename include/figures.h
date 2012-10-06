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
 * @struct v3dmc_color
 * The v3dmc_color is a structure created for storing the color data in a single
 * variable. It is used for setting the color of primitives.
 * All the components values will be stored as float data, because
 * by float we can have an better definition of the color.
 * @brief The structure that contains the info of a color.
 */
typedef struct{
	/** The red component's value of the color. Should have values between 0.0-1.0. */
	GLclampf r;
	/** The green component's value of the color. Should have values between 0.0-1.0. */
	GLclampf g;
	/** The blue component's value of the color. Should have values between 0.0-1.0. */
	GLclampf b;
	/** The alfa component's value of the color. Should have values between 0.0-1.0. */
	GLclampf a;
}v3dmc_color;

/**
 * @struct v3dmc_point
 * This structure allows to store the coordinates of a point in the 3D space.
 * It also contains the info about the color of the point in an v3dmc_color attribute.
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
	v3dmc_color color;
}v3dmc_point;

/**
 * @struct v3dmc_point_list_element
 * The structure that defines the element of an point list.
 */
typedef struct v3dmc_point_list_element{
	/** The point */
	v3dmc_point point;
	/** Pointer to the next element of the list */
	struct v3dmc_point_list_element* next;
	/** Pointer to the previous element of the list */
	struct v3dmc_point_list_element* prev;
}v3dmc_point_list_element;

/**
 * @struct v3dmc_point_list
 */
typedef v3dmc_point_list_element* v3dmc_point_list;

/**
 * @struct v3dmc_line
 * This structure allows to store a line information. We need 2 v3dmc_point attributes
 * to define a line. The color information is stored in the v3dmc_point structure, so we
 * can use it to define the line color. Also this allows to have different color for
 * start and end points.
 * @brief A structure for storing the line info.
 */
typedef struct{
	/** The line start point */
	v3dmc_point a;
	/** The line end point */
	v3dmc_point b;
}v3dmc_line;

/**
 * @struct v3dmc_line_list_element
 */
typedef struct v3dmc_line_list_element{
	/** The line contained in this element of the list */
	v3dmc_line line;
	/** The pointer to the next element */
	struct v3dmc_line_list_element* next;
	/** The pointer to the previous element */
	struct v3dmc_line_list_element* prev;
}v3dmc_line_list_element;

/**
 * @struct v3dmc_line_list
 */
typedef v3dmc_line_list_element* v3dmc_line_list;

/**
 * @struct v3dmc_texcoord
 * This is the structure used for store the coordinates of texture coners, that allows to 
 * map parts of texture on primitives like triangles and quads.
 * @brief A structure for storing texture coordinates.
 */
typedef struct{
	/** The x coordinate. Should have values between 0.0-1.0. */
	GLfloat x;
	/** The y coordinate. Should have values between 0.0-1.0. */
	GLfloat y;
}v3dmc_texcoord;

/**
 * @struct v3dmc_texture
 * A structure for storing texture info.
 * Having a texture structure will allow to load the texture only for one time and
 * use it for more primitives.
 * @brief A structure that allows to contain the info of a texture.
 */
typedef struct{
	/** Upper-left corner coordinates. */
	v3dmc_texcoord a;
	/** Upper-right corner coordinates. */
	v3dmc_texcoord b;
	/** Lower-right corner coordinates. */
	v3dmc_texcoord c;
	/** Lower-left corner coordinates. */
	v3dmc_texcoord d;
	/** The texture's name. */
	GLchar name[255];
}v3dmc_texture;

/**
 * @struct v3dmc_triangle
 * The v3dmc_triangle structure allows to store data about a triangle primitive. This
 * structure also allows to store the texture info.
 * @brief A structure that allows to contain the info of a triangle.
 */
typedef struct{
	/** The first triangle vertex. */
	v3dmc_point a;
	/** The second triangle vertex. */
	v3dmc_point b;
	/** The third triangle vertex. */
	v3dmc_point c;
	/** The texture to map on the triangle. */
	v3dmc_texture texture;
}v3dmc_triangle;

/**
 * @struct v3dmc_triangle_list_element
 */
typedef struct v3dmc_triangle_list_element{
	v3dmc_triangle triangle;
	struct v3dmc_triangle_list_element* next;
	struct v3dmc_triangle_list_element* prev;
}v3dmc_triangle_list_element;

/**
 * @struct v3dmc_triangle_list
 */
typedef v3dmc_triangle_list_element* v3dmc_triangle_list;

/**
 * @struct v3dmc_quad
 * The v3dmc_quad structure allows to store data of a quad, including the texture.
 * @brief A structure that allows to contain the info of a quad.
 */
typedef struct{
	/** The first triangle vertex. */
	v3dmc_point a;
	/** The second triangle vertex. */
	v3dmc_point b;
	/** The third triangle vertex. */
	v3dmc_point c;
	/** The fourth triangle vertex. */
	v3dmc_point d;
	/** The texture to map on the quad */
	v3dmc_texture texture;
}v3dmc_quad;

/**
 * @struct v3dmc_quad_list_element
 */
typedef struct v3dmc_quad_list_element{
	v3dmc_quad quad;
	struct v3dmc_quad_list_element* next;
	struct v3dmc_quad_list_element* prev;
}v3dmc_quad_list_element;

/**
 * @struct v3dmc_quad_list
 */
typedef v3dmc_quad_list_element* v3dmc_quad_list;

/**
 * @struct v3dmc_object
 * The v3dmc_object structure group more primitives(points,lines,...) in a single
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
	/** The pointer to the list of points */
	v3dmc_point_list points;
	/** The last point in the list of points */
	v3dmc_point_list last_point;
	/** The pointer to the list of lines */
	v3dmc_line_list lines;
	/** The last line of the list of lines */
	v3dmc_line_list last_line;
	/** The list of triangles */
	v3dmc_triangle_list triangles;
	/** The last triangle in the list */
	v3dmc_triangle_list last_triangle;
	/** The pointer to the list of quads */
	v3dmc_quad_list quads;
	/** The pointer to the last element of the lost of quads */
	v3dmc_quad_list last_quad;
}v3dmc_object;

/**
 * @fn rgbi(GLint r, GLint g, GLint b)
 * This function create a v3dmc_color object from 3 integers.
 * @param r the red component's value
 * @param g the green component's value
 * @param b the green component's value
 * @return a v3dmc_color object
 */
v3dmc_color rgbi(GLint r, GLint g, GLint b);

/**
 * @fn rgbf(GLfloat r, GLfloat g, GLfloat b)
 * This function create a v3dmc_color object by 3 float.
 * @param r the red component's value
 * @param g the green component's value
 * @param b the green component's value
 * @return a v3dmc_color object
 */
v3dmc_color rgbf(GLclampf r, GLclampf g, GLclampf b);

/**
 * @gn rgbai(GLint r, GLint g, GLint b, GLint a)
 * This function a v3dmc_color object by 4 integers.
 * @param r the red component's value
 * @param g the green component's value
 * @param b the green component's value
 * @param a the green component's value
 * @return a v3dmc_color object
 */
v3dmc_color rgbai(GLint r, GLint g, GLint b, GLint a);

/**
 * @gn rgbaf(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
 * This function a v3dmc_color object by 4 float.
 * @param r the red component's value
 * @param g the green component's value
 * @param b the green component's value
 * @param a the green component's value
 * @return a v3dmc_color object
 */
v3dmc_color rgbaf(GLclampf r, GLclampf g, GLclampf b, GLclampf a);

/**
 * @fn point(GLfloat x, GLfloat y, GLfloat z, v3dmc_color color)
 * This function create a v3dmc_point object.
 * @param x a float that represents the x coordinate of the point
 * @param y a float that represents the y coordinate of the point
 * @param z a float that represents the z coordinate of the point
 * @return a v3dmc_point object
 */
v3dmc_point point(GLfloat x, GLfloat y, GLfloat z, v3dmc_color color);

/**
 * @fn line(v3dmc_point a, v3dmc_point b)
 * This function create a v3dmc_line object.
 * @param a the start point of the line
 * @param b the end point of the line
 * @return a v3dmc_point object
 */
v3dmc_line line(v3dmc_point a, v3dmc_point b);

/**
 * @fn triangle(v3dmc_point a, v3dmc_point b, v3dmc_point c, v3dmc_texture texture)
 * This function create a v3dmc_triangle object.
 * @param a the first vertex
 * @param b the second vertex
 * @param c the third vertex
 * @param texture the texture to map on the triangle
 * @return a v3dmc_triangle object
 */
v3dmc_triangle triangle(v3dmc_point a, v3dmc_point b, v3dmc_point c, v3dmc_texture texture);

/**
 * @fn quad(v3dmc_point a, v3dmc_point b, v3dmc_point c, v3dmc_point d, v3dmc_texture texture)
 * This function create a v3dmc_quad object.
 * @param a the first vertex
 * @param b the second vertex
 * @param c the third vertex
 * @param d the fourth vertex
 * @param texture the texture to map on the quad
 * @return a v3dmc_quad object
 */
v3dmc_quad quad(v3dmc_point a, v3dmc_point b, v3dmc_point c, v3dmc_point d, v3dmc_texture texture);

/**
 * @fn object()
 * This function create an empty initialized v3dmc_object.
 * @return a v3dmc_object
 */
v3dmc_object object();

/**
 * @fn add_point(v3dmc_object* obj, v3dmc_point point)
 * This funtion adds a new v3dmc_point to an object.
 * @param [out] obj the object to which to add the new v3dmc_point
 * @param point the point to add to the object
 */
void add_point(v3dmc_object* obj, v3dmc_point point);

/**
 * @fn get_point_list_element(v3dmc_object obj,GLint index)
 * This function allows to get an object's point by the index of the element
 * inside the list of points.
 * @param obj the object from which to get the point
 * @param index the index of the element in the list to get
 * @return a v3dmc_point_list in the position indicated by index or NULL if the element wasn't found
 */
v3dmc_point_list get_point_list_element(v3dmc_object obj, GLint index);

/**
 * @fn add_line(v3dmc_object* obj, v3dmc_line line)
 * This function adds a new v3dmc_line to an object
 * @param [out] obj the object to which to add the new v3dmc_line
 * @param line the line to add to the object
 */
void add_line(v3dmc_object* obj, v3dmc_line line);

/**
 * @fn v3dmc_line_list get_line_list_element(v3dmc_object obj, GLint index)
 * This function allows to get an object's line by specifying the index of the element 
 * to return.
 * @param obj the object in which to search the v3dmc_line_list_element
 * @param index the index of the element in the lines list
 * @return a v3dmc_line_list in the position indicated by index or NULL if the element wasn't found
 */
v3dmc_line_list get_line_list_element(v3dmc_object obj, GLint index);

/**
 * @fn add_triangle(v3dmc_object* obj, v3dmc_triangle triangle)
 * This function add a new TIANGLE to the object.
 * @param [out] obj the object to which to add the new v3dmc_triangle
 * @param triangle the triangle to add to the object
 */
void add_triangle(v3dmc_object* obj, v3dmc_triangle triangle);

/**
 * @fn get_triangle_list_element(v3dmc_object obj, GLint index)
 * This function allows to get an object's triangle by specifying the index of the element
 * to return.
 * @param obj the object in which to search the v3dmc_triangle_list_element
 * @param index the index of the element in the triangles list
 * @return a v3dmc_triangle_list_element in the position indicated by index or NULL if the element wasn't found
 */
v3dmc_triangle_list get_triangle_list_element(v3dmc_object obj, GLint index);

/**
 * @fn add_quad(v3dmc_object* obj, v3dmc_quad quad)
 * This function add a new v3dmc_quad to the object.
 * @param [out] obj the object to which to add the new v3dmc_quad
 * @param quad the quad to add to the object
 */
void add_quad(v3dmc_object* obj, v3dmc_quad quad);


/**
 * @fn get_quad_list_element(v3dmc_object obj, GLint index)
 * This function allows to get an object's quad by specifying the index of the element
 * to return.
 * @param obj the object in which to search the v3dmc_quad_list_element
 * @param index the index of the element in the quads list
 * @return a v3dmc_quad_list_element in the position indicated by index or NULL if the element wasn't found
 */
v3dmc_quad_list get_quad_list_element(v3dmc_object obj, GLint index);

/**
 * @fn clampf(GLfloat value)
 * This function check if the passed value is between 0.0 and 1.0 and if not
 * returns a float value in this interval. If the value is greater than 1.0, than
 * the function returns 1.0 and if the passed value is smaller than 0.0, returns 0.0.
 * @param value the value to normalize
 * @return a GLclampf value between 0.0 and 1.0
 */
 GLclampf clampf(GLfloat value);

/**
 * @fn texcoord(GLclampf a, GLclampf b)
 * This function create a v3dmc_texcoord object;
 * @param x the x texture coordinate
 * @param y the y texture coordinate
 * @return a v3dmc_texcoord object
 */
v3dmc_texcoord texcoord(GLclampf x, GLclampf y);

/**
 * @fn texture(GLchar* name, v3dmc_texcoord a, v3dmc_texcoord b, v3dmc_texcoord c, v3dmc_texcoord d)
 * This function create a new v3dmc_texture object.
 * @param name the path and name of the texture
 * @param a the upper-left corner's coordinates
 * @param b the upper-right corner's coordinates
 * @param c the lower-right corner's coordinates
 * @param d the lower-left corner's coordinates
 * @return a v3dmc_texture coordinates
 */
v3dmc_texture texture(GLchar* name, v3dmc_texcoord a, v3dmc_texcoord b, v3dmc_texcoord c, v3dmc_texcoord d);

/**
 * @fn save_object(v3dmc_object obj, GLchar *filename)
 * This function allows to save an v3dmc_object to a binary file.
 * @param obj the object to save to a file
 * @param filename the name of the file to whici to save the object
 */
void save_object(v3dmc_object obj, GLchar *filename);

/**
 * @fn load_object(GLchar *filename)
 * This function allows to create a new object by loading its information from an
 * saved model file.
 * @param filename the name of the file from which to get the object data
 * @return an v3dmc_object that correspond to the object saved in that file
 */
v3dmc_object load_object(GLchar *filename);