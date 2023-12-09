#include "fml/fml_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* nodeToJson(Node* node);

char* charNodeToJson(CharNode* charNode)
{
    char* json = malloc(15);
    if (json) {
        sprintf(json, "{\"char\":\"%c\"}", charNode->c);
    }
    return json;
}

char* altNodeToJson(AltNode* altNode)
{
    char* leftJson = nodeToJson(altNode->left);
    char* rightJson = nodeToJson(altNode->right);
    int length = strlen(leftJson) + strlen(rightJson) + 20;
    char* json = malloc(length);
    if (json) {
        sprintf(json, "{\"alt\":[%s,%s]}", leftJson, rightJson);
    }
    free(leftJson);
    free(rightJson);
    return json;
}

char* concatNodeToJson(ConcatNode* concatNode)
{
    char* leftJson = nodeToJson(concatNode->left);
    char* rightJson = nodeToJson(concatNode->right);
    int length = strlen(leftJson) + strlen(rightJson) + 25;
    char* json = malloc(length);
    if (json) {
        sprintf(json, "{\"concat\":[%s,%s]}", leftJson, rightJson);
    }
    free(leftJson);
    free(rightJson);
    return json;
}

char* qtfrNodeToJson(QtfrNode* qtfrNode)
{
    char* childJson = nodeToJson(qtfrNode->child);
    int length = strlen(childJson) + 15;
    char* json = malloc(length);
    if (json) {
        sprintf(json, "{\"qtfr\":%s}", childJson);
    }
    free(childJson);
    return json;
}

char* nodeToJson(Node* node)
{
    if (node == NULL) {
        return strdup("{}");
    }
    switch (node->kind) {
    case NODE_CHAR:
        return charNodeToJson(&node->u.charNode);
    case NODE_ALT:
        return altNodeToJson(&node->u.altNode);
    case NODE_CONCAT:
        return concatNodeToJson(&node->u.concatNode);
    case NODE_QTFR:
        return qtfrNodeToJson(&node->u.qtfrNode);
    default:
        return strdup("{}");
    }
}
