#include "SVGParser.h"


int main(int argc, char** argv)
{
    // Structs related to parser functions
    SVG* svg = NULL;


    svg = createSVG(argv[1]);

    printf("%s\n", svg->namespace);


    return 0;
}





// xmlAttr* attribute = cur_node->properties;
                // while (attribute)
                // {
                //     // xmlChar* attrName = attribute->name;
                //     xmlChar* attrValue = xmlNodeListGetString(cur_node->doc, attribute->children, 1);

                //     printf("%s : %s\n", attribute->name, attrValue);

                //     xmlFree(attrValue);
                //     attribute = attribute->next;
                // }