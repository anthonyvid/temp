#include "SVGParser.h"
#include "SVGHelper.h"


SVG* createSVG(const char* fileName) {
    if (fileName == NULL || fileName[0] == '\0' || strlen(fileName) == 0)
        return NULL;

    FILE* fp = fopen(fileName, "r");

    if (fp == NULL) return NULL;


    // Use libxml2 to help us parse the svg file
    xmlDoc* doc = NULL;
    xmlNode* root_element = NULL;
    doc = xmlReadFile(fileName, NULL, 0);

    if (doc == NULL) return NULL;

    root_element = xmlDocGetRootElement(doc);

    SVG* svg = NULL;
    svg = malloc(sizeof(SVG));

    if (svg == NULL) return NULL;



    // Sort elements into proper svg struct properties
    addElementsToSVG(svg, root_element);

    xmlFreeDoc(doc);
    xmlCleanupParser();

    return svg;
}

// char* SVGToString(const SVG* img) {

// }

// void deleteSVG(SVG* img) {

// }

/*

// Function that returns a list of all rectangles in the struct.
List* getRects(const SVG* img) {

}

// Function that returns a list of all circles in the struct.
List* getCircles(const SVG* img) {

}

// Function that returns a list of all groups in the struct.
List* getGroups(const SVG* img) {

}

// Function that returns a list of all paths in the struct.
List* getPaths(const SVG* img) {

}



// Function that returns the number of all rectangles with the specified area
int numRectsWithArea(const SVG* img, float area) {

}

// Function that returns the number of all circles with the specified area
int numCirclesWithArea(const SVG* img, float area) {

}

// Function that returns the number of all paths with the specified data - i.e. Path.data field
int numPathsWithdata(const SVG* img, const char* data) {

}

// Function that returns the number of all groups with the specified length - see A1 Module 2 for details
int numGroupsWithLen(const SVG* img, int len) {

}


int numAttr(const SVG* img) {

}


void deleteAttribute(void* data) {

}

char* attributeToString(void* data) {

}

int compareAttributes(const void* first, const void* second) {

}

void deleteGroup(void* data) {

}

char* groupToString(void* data) {

}

int compareGroups(const void* first, const void* second) {

}


void deleteRectangle(void* data) {

}

char* rectangleToString(void* data) {

}

int compareRectangles(const void* first, const void* second) {

}

void deleteCircle(void* data) {

}

char* circleToString(void* data) {

}

int compareCircles(const void* first, const void* second) {

}

void deletePath(void* data) {

}

char* pathToString(void* data) {

}

int comparePaths(const void* first, const void* second) {

}
*/