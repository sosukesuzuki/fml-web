#include "fml_instructions_to_json.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* instructionToJson(Instruction* instr)
{
    char buffer[50];
    switch (instr->kind) {
    case INSTRUCTION_MATCH:
        strcpy(buffer, "\"match\"");
        break;
    case INSTRUCTION_CHAR:
        sprintf(buffer, "\"char %c\"", instr->u.iChar.c);
        break;
    case INSTRUCTION_SPLIT:
        sprintf(buffer, "\"split %d %d\"", instr->u.iSplit.pos1, instr->u.iSplit.pos2);
        break;
    case INSTRUCTION_JMP:
        sprintf(buffer, "\"jmp %d\"", instr->u.iJmp.pos);
        break;
    default:
        strcpy(buffer, "\"unknown\"");
    }
    return strdup(buffer);
}

char* instructionsToJson(Instructions* instructions)
{
    if (instructions == NULL || instructions->size == 0) {
        return strdup("[]");
    }

    char* json = strdup("[");
    for (int i = 0; i < instructions->size; i++) {
        char* instrJson = instructionToJson(instructions->instructions[i]);
        json = realloc(json, strlen(json) + strlen(instrJson) + 3);
        if (i > 0) {
            strcat(json, ", ");
        }
        strcat(json, instrJson);
        free(instrJson);
    }
    json = realloc(json, strlen(json) + 2);
    strcat(json, "]");

    return json;
}
