#include "fml_node_to_json.h"
#include "fml_test_utils.h"

void nodeToJson_01()
{
    Node* node = NULL;
    char* json = nodeToJson(node);
    TEST_ASSERT(strcmp(json, "{}") == 0, 1);
    free(json);
}

int main()
{
    RUN_TEST(nodeToJson_01);
    return 0;
}
