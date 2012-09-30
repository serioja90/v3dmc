/**
 * This file contains the structure definitions of the primitives
 * that will be used as the basic tools for models designing.
 */

/**
 * The structure for containing color data.
 * All the components values will be stored as float data, because
 * by float we can have an better definition of the color.
 */
typedef struct{
	float r; /* red component */
	float g; /* green component */
	float b; /* blue component */
}COLOR;

/**
 * The structure that allows to contain a point info.
 */
 typedef struct{
 	float x; /* x coordinate */
 	float y; /* y coordinate */
 	float z; /* z coordinate */
 	COLOR color; /* the point color */
 }POINT;

/**
 * The structure for storing the line data.
 * A line has a start point, an end point and a color.
 */
 typedef struct{
 	POINT a; /* start point */
 	POINT b; /* end point */
 	COLOR color; /* the line color */
 }LINE;