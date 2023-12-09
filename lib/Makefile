# ====================================================================
# Variables
# ====================================================================
CC := gcc
CFLAGS := -Wall -Wextra

CLANG_FORMAT := clang-format
FORMAT_FILES := $(wildcard *.c) $(wildcard *.h)

# ====================================================================
# Files
# ====================================================================

FML_NODE_TO_JSON_TESTS_SRC_FILES := fml_node_to_json_tests.c fml_node_to_json.c ./fml/fml_parser.c

FML_NODE_TO_JSON_TESTS_OBJECT_FILES = $(FML_NODE_TO_JSON_TESTS_SRC_FILES:.c=.o)

FML_NODE_TO_JSON_TESTS_EXECUTABLE_FILE := fml_node_to_json_tests

PHONY: format

# ====================================================================
# Build targets
# ====================================================================

fml_node_to_json_tests: $(FML_NODE_TO_JSON_TESTS_OBJECT_FILES)
	$(CC) $(CFLAGS) -o $(FML_NODE_TO_JSON_TESTS_EXECUTABLE_FILE) $^ -lm

# ====================================================================
# Run tests
# ====================================================================

run-fml-node-to-json-tests: fml_node_to_json_tests
	./$(FML_NODE_TO_JSON_TESTS_EXECUTABLE_FILE)

# ====================================================================
# Development utils
# ====================================================================

format:
	$(CLANG_FORMAT) -i $(FORMAT_FILES)
