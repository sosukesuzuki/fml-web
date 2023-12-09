#include "fml/fml_compiler.h"
#include "fml/fml_instructions.h"
#include "fml/fml_parser.h"
#include "fml/fml_vm.h"
#include "fml/fml_vm_stack.h"

#include "fml_instructions_to_json.h"
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
char* compileToInstructions(char* input)
{
    Node* node = malloc(sizeof(Node));
    parseRegexp(node, input);

    Instructions* instructions = malloc(sizeof(Instructions));
    initInstructions(instructions);
    compile(node, instructions);

    char* output = instructionsToJson(instructions);

    return output;
}

EMSCRIPTEN_KEEPALIVE
int test(char* regexp, char* input)
{
    Node* node = malloc(sizeof(Node));
    parseRegexp(node, regexp);

    Instructions* instructions = malloc(sizeof(Instructions));
    initInstructions(instructions);
    compile(node, instructions);

    VMStack* stack = malloc(sizeof(VMStack));
    initVMStack(stack);

    VMContext* context = malloc(sizeof(VMContext));
    initVM(context, &input, instructions, stack);

    int r = runVM(context);
    return r;
}
