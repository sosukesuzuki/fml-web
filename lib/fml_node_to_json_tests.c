#include "fml/fml_parser.h"
#include "fml_node_to_json.h"
#include "fml_test_utils.h"

void nodeToJson_01()
{
    Node* node = NULL;
    char* json = nodeToJson(node);
    TEST_ASSERT(strcmp(json, "{}") == 0, 1);
    free(json);
}

void nodeToJson_02()
{
    Node node;
    char* input = "a";
    parseRegexp(&node, input);
    char* json = nodeToJson(&node);
    TEST_ASSERT(strcmp(json, "{\"char\":\"a\"}") == 0, 1);
    free(json);
}

void nodeToJson_03()
{
    Node node;
    char* input = "a|b";
    parseRegexp(&node, input);
    char* json = nodeToJson(&node);
    TEST_ASSERT(strcmp(json, "{\"alt\":[{\"char\":\"a\"},{\"char\":\"b\"}]}") == 0, 1);
    free(json);
}

void nodeToJson_04()
{
    Node node;
    char* input = "ab";
    parseRegexp(&node, input);
    char* json = nodeToJson(&node);
    TEST_ASSERT(strcmp(json, "{\"concat\":[{\"char\":\"a\"},{\"char\":\"b\"}]}") == 0, 1);
    free(json);
}

void nodeToJson_05()
{
    Node node;
    char* input = "a*";
    parseRegexp(&node, input);
    char* json = nodeToJson(&node);
    TEST_ASSERT(strcmp(json, "{\"qtfr\":{\"char\":\"a\"}}") == 0, 1);
    free(json);
}

int main()
{
    RUN_TEST(nodeToJson_01);
    RUN_TEST(nodeToJson_02);
    RUN_TEST(nodeToJson_03);
    RUN_TEST(nodeToJson_04);
    RUN_TEST(nodeToJson_05);
    return 0;
}
