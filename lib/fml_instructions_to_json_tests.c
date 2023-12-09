#include "fml/fml_instructions.h"
#include "fml_instructions_to_json.h"
#include "fml_test_utils.h"

void instructionsToJson_01()
{
    Instructions* instructions = NULL;
    char* json = instructionsToJson(instructions);
    TEST_ASSERT(strcmp(json, "[]") == 0, 1);
    free(json);
}

void instructionsToJson_02()
{
    Instructions instructions;
    instructions.size = 1;
    instructions.instructions = malloc(sizeof(Instruction*));
    instructions.instructions[0] = malloc(sizeof(Instruction));
    instructions.instructions[0]->kind = INSTRUCTION_MATCH;
    char* json = instructionsToJson(&instructions);
    TEST_ASSERT(strcmp(json, "[\"match\"]") == 0, 1);
}

void instructionsToJson_03()
{
    Instructions instructions;
    instructions.size = 1;
    instructions.instructions = malloc(sizeof(Instruction*));
    instructions.instructions[0] = malloc(sizeof(Instruction));
    instructions.instructions[0]->kind = INSTRUCTION_CHAR;
    instructions.instructions[0]->u.iChar.c = 'a';
    char* json = instructionsToJson(&instructions);
    TEST_ASSERT(strcmp(json, "[\"char a\"]") == 0, 1);
}

void instructionsToJson_04()
{
    Instructions instructions;
    instructions.size = 1;
    instructions.instructions = malloc(sizeof(Instruction*));
    instructions.instructions[0] = malloc(sizeof(Instruction));
    instructions.instructions[0]->kind = INSTRUCTION_SPLIT;
    instructions.instructions[0]->u.iSplit.pos1 = 1;
    instructions.instructions[0]->u.iSplit.pos2 = 2;
    char* json = instructionsToJson(&instructions);
    TEST_ASSERT(strcmp(json, "[\"split 1 2\"]") == 0, 1);
}

void instructionsToJson_05()
{
    Instructions instructions;
    instructions.size = 1;
    instructions.instructions = malloc(sizeof(Instruction*));
    instructions.instructions[0] = malloc(sizeof(Instruction));
    instructions.instructions[0]->kind = INSTRUCTION_JMP;
    instructions.instructions[0]->u.iJmp.pos = 1;
    char* json = instructionsToJson(&instructions);
    TEST_ASSERT(strcmp(json, "[\"jmp 1\"]") == 0, 1);
}

void instructionsToJson_06()
{
    Instructions instructions;
    instructions.size = 2;
    instructions.instructions = malloc(sizeof(Instruction*) * 2);
    instructions.instructions[0] = malloc(sizeof(Instruction));
    instructions.instructions[0]->kind = INSTRUCTION_MATCH;
    instructions.instructions[1] = malloc(sizeof(Instruction));
    instructions.instructions[1]->kind = INSTRUCTION_CHAR;
    instructions.instructions[1]->u.iChar.c = 'a';
    char* json = instructionsToJson(&instructions);
    TEST_ASSERT(strcmp(json, "[\"match\", \"char a\"]") == 0, 1);
}

int main()
{
    RUN_TEST(instructionsToJson_01);
    RUN_TEST(instructionsToJson_02);
    RUN_TEST(instructionsToJson_03);
    RUN_TEST(instructionsToJson_04);
    RUN_TEST(instructionsToJson_05);
    RUN_TEST(instructionsToJson_06);
    return 0;
}
