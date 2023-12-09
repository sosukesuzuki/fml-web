#include "fml/fml_parser.h"
#include <emscripten.h>
#include <stdlib.h>

EMSCRIPTEN_KEEPALIVE
int parse(char* input) { return 1 }
