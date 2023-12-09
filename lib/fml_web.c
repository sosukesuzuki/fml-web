#include "fml/fml_parser.h"
#include "fml_node_to_json.h"
#include <emscripten.h>
#include <stdlib.h>

EMSCRIPTEN_KEEPALIVE
char* parse(char* input)
{
    Node* node = malloc(sizeof(Node));
    int result = parseRegexp(node, input);
    char* output = nodeToJson(node);
    return output;
}

EMSCRIPTEN_KEEPALIVE
void freeString(char* str)
{
    free(str);
}
