#include "SVGHelper.h"

const xmlChar* xmlCharToUpper(const xmlChar* name) {
    xmlChar* uppercaseName = malloc(sizeof(xmlChar) * xmlStrlen(name));
    int i = 0;

    while (name[i] != 0) {
        uppercaseName[i] = toupper(name[i]);
        i++;
    }

    return uppercaseName;
}

void addElementsToSVG(SVG* svg, xmlNode* a_node) {
    xmlNode* cur_node = NULL;
    const xmlChar* name = NULL;

    for (cur_node = a_node; cur_node; cur_node = cur_node->next)
    {
        if (cur_node->type == XML_ELEMENT_NODE)
        {
            name = xmlCharToUpper(cur_node->name);

            if (xmlStrcmp(name, (const xmlChar*)"SVG") == 0) {
                // Get namespace from svg tag and store in namespace property
                strcpy(svg->namespace, (char*)cur_node->ns->href);
            }
            else if (xmlStrcmp(name, (const xmlChar*)"TITLE") == 0) {
                
            }
            else if (xmlStrcmp(name, (const xmlChar*)"DESCRIPTION") == 0) {

            }
            else if (xmlStrcmp(name, (const xmlChar*)"G") == 0) {

            }
            else if (xmlStrcmp(name, (const xmlChar*)"PATH") == 0) {

            }
            else if (xmlStrcmp(name, (const xmlChar*)"CIRCLE") == 0) {

            }
            else if (xmlStrcmp(name, (const xmlChar*)"RECT") == 0) {

            }
            // This is where the otherAttributes are
            else {

            }
        }

        addElementsToSVG(svg, cur_node->children);
    }
}


