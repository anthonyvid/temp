#ifndef SVGPARSER_H
#define SVGPARSER_H

#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include <libxml/xmlschemastypes.h>
#include "LinkedListAPI.h"

typedef enum COMP {
    SVG_IMG, CIRC, RECT, PATH, GROUP
} elementType;

//Represents a generic SVG element/XML node Attribute
typedef struct {
    //Attribute name.  Must not be NULL
    char* name;
    //Attribute value.  May be empty
    char	value[];
} Attribute;

//Represents a group of objects in an SVG file
typedef struct {

    //All objects in the list will be of type Rectangle.  It must not be NULL.  It may be empty.
    List* rectangles;
    //All objects in the list will be of type Circle.  It must not be NULL.  It may be empty.
    List* circles;
    //All objects in the list will be of type Path.  It must not be NULL.  It may be empty.
    List* paths;
    //All objects in the list will be of type Group.  It must not be NULL.  It may be empty.
    List* groups;

    //Additional rectangle attributes - i.e. attributes of the g XML element.  
    //All objects in the list will be of type Attribute.  It must not be NULL.  It may be empty.
    List* otherAttributes;
} Group;

//Represents a rectangle primitive 
typedef struct {
    //The X coordinate of the "starting" corner of the rectangle
    float x;
    //The Y coordinate of the "starting" corner of the rectangle
    float y;
    //Rectangle width.  Must be >= 0
    float width;
    //Rectangle height.  Must be >= 0
    float height;

    //Units for the rectable coordinates and size.  May be empty.
    char units[50];

    //Additional rectangle attributes - i.e. attributes of the rect XML element.  
    //All objects in the list will be of type Attribute.  It must not be NULL.  It may be empty.
    List* otherAttributes;

} Rectangle;

//Represents a circle primitive 
typedef struct {
    //The X coordinate of circle centre
    float cx;
    //The Y coordinate of circle centre
    float cy;
    //Circle radius. Must be >= 0
    float r;

    //Units for the circle coordinates and size.  May be empty.
    char units[50];

    //Additional circle attributes - i.e. attributes of the circle XML element.  
    //All objects in the list will be of type Attribute.  It must not be NULL.  It may be empty.
    List* otherAttributes;

} Circle;

//Represents a path primitive - i.e. a sequence of points connected with lines or curves
typedef struct {

    //Additional path attributes - i.e. attributes of the path XML element.  
    //All objects in the list will be of type Attribute.  It must not be NULL.  It may be empty.
    List* otherAttributes;

    //Path data.  Must not be NULL
    char data[];

} Path;

// The main struct, representing an svg elemnt of the format
// While a full SVG struct might have multiple svg components, we will assume that all of our input
// structs will only have one
typedef struct {

    //For the fixed-length fields below, verify that the relevant data fits before copying 
    //it into the field. 
    //If the data exceeds the field length, truncate the data to fit the max field length.

    //Namespace associated with our SVG struct.  May be not be empty.  While a real SVG struct might have
    //multiple namespaces associated with it, we will assume there is only one
    char namespace[256];

    //Title of our SVG struct - from the optional <title> element.  May be empty.
    char title[256];

    //Decription of our SVG struct - from the optional <desc> element.  May be empty.
    char description[256];

    //All objects in the list will be of type Rectangle.  It must not be NULL.  It may be empty.
    List* rectangles;
    //All objects in the list will be of type Circle.  It must not be NULL.  It may be empty.
    List* circles;
    //All objects in the list will be of type Path.  It must not be NULL.  It may be empty.
    List* paths;
    //All objects in the list will be of type Group.  It must not be NULL.  It may be empty.
    List* groups;

    //Additional SVG attributes - i.e. attributes of the svg XML element.  
    //All objects in the list will be of type Attribute.  It must not be NULL.  It may be empty.  
    //Do not put the namespace here, since it already has its own field
    List* otherAttributes;
} SVG;

//A1

/* Public API - main */

/** Function to create an SVG struct based on the contents of an SVG file.
 *@pre File name cannot be an empty string or NULL.
       File represented by this name must exist and must be readable.
 *@post Either:
        A valid SVG struct has been created and its address was returned
        or
        An error occurred, and NULL was returned
 *@return the pinter to the new struct or NULL
 *@param fileName - a string containing the name of the SVG file
**/
SVG* createSVG(const char* fileName);

/** Function to create a string representation of an SVG struct.
 *@pre SVG struct exists, is not null, and is valid
 *@post SVG struct has not been modified in any way, and a string representing the SVG contents has been created
 *@return a string contaning a humanly readable representation of an SVG struct
 *@param obj - a pointer to an SVG struct
**/
char* SVGToString(const SVG* img);

/** Function to delete struct content and free all the memory.
 *@pre SVG struct exists, is not null, and has not been freed
 *@post SVG struct had been freed
 *@return none
 *@param obj - a pointer to an SVG struct
**/
void deleteSVG(SVG* img);

/* For the four "get..." functions below, make sure you return a list of opinters to the existing structs
 - do not allocate new structs.  They all share the same format, and only differ in the contents of the lists
 they return.

 *@pre SVG struct exists, is not null, and has not been freed
 *@post SVG struct has not been modified in any way
 *@return a newly allocated List of components.  While the List struct itself is new, the components in it are just pointers
  to the ones in the struct.

 The list must me empty if the element is not found - do not return NULL

 *@param obj - a pointer to an SVG struct
 */

 // Function that returns a list of all rectangles in the struct.  
List* getRects(const SVG* img);
// Function that returns a list of all circles in the struct.  
List* getCircles(const SVG* img);
// Function that returns a list of all groups in the struct.  
List* getGroups(const SVG* img);
// Function that returns a list of all paths in the struct.  
List* getPaths(const SVG* img);


/* For the four "num..." functions below, you need to search the SVG struct for components that match the search
  criterion.  You may wish to write some sort of a generic searcher fucntion that accepts a struct, a predicate function,
  and a dummy search record as arguments.  We will discuss such search functions in class

 NOTE: For consistency, use the ceil() function to round the floats up to the nearest integer once you have computed
 the number you need.  See A1 Module 2 for details.

 *@pre SVG struct exists, is not null, and has not been freed.  The search criterion is valid
 *@post SVG struct has not been modified in any way
 *@return an int indicating how many objects matching the criterion are contained in the struct
 *@param obj - a pointer to an SVG struct
 *@param 2nd - the second param depends on the function.  See details below
 */

 // Function that returns the number of all rectangles with the specified area
int numRectsWithArea(const SVG* img, float area);
// Function that returns the number of all circles with the specified area
int numCirclesWithArea(const SVG* img, float area);
// Function that returns the number of all paths with the specified data - i.e. Path.data field
int numPathsWithdata(const SVG* img, const char* data);
// Function that returns the number of all groups with the specified length - see A1 Module 2 for details
int numGroupsWithLen(const SVG* img, int len);

/*  Function that returns the total number of Attribute structs in the SVG struct - i.e. the number of Attributes
    contained in all otherAttributes lists in the structs making up the SVG struct
    *@pre SVG struct  exists, is not null, and has not been freed.
    *@post SVG has not been modified in any way
    *@return the total length of all attribute structs in the SVG
    *@param obj - a pointer to an SVG struct
*/
int numAttr(const SVG* img);

/* ******************************* List helper functions  - MUST be implemented *************************** */

void deleteAttribute(void* data);
char* attributeToString(void* data);
int compareAttributes(const void* first, const void* second);

void deleteGroup(void* data);
char* groupToString(void* data);
int compareGroups(const void* first, const void* second);

void deleteRectangle(void* data);
char* rectangleToString(void* data);
int compareRectangles(const void* first, const void* second);

void deleteCircle(void* data);
char* circleToString(void* data);
int compareCircles(const void* first, const void* second);

void deletePath(void* data);
char* pathToString(void* data);
int comparePaths(const void* first, const void* second);

#endif
