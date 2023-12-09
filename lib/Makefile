# ====================================================================
# Variables
# ====================================================================
CC := gcc
CFLAGS := -Wall -Wextra

EMCC := emcc

CLANG_FORMAT := clang-format
FORMAT_FILES := $(wildcard *.c) $(wildcard *.h)

# ====================================================================
# Files
# ====================================================================

FML_NODE_TO_JSON_TESTS_SRC_FILES := fml_node_to_json_tests.c fml_node_to_json.c ./fml/fml_parser.c
FML_WEB_SRC_FILES := fml_web.c fml_node_to_json.c ./fml/fml_parser.c

FML_NODE_TO_JSON_TESTS_OBJECT_FILES = $(FML_NODE_TO_JSON_TESTS_SRC_FILES:.c=.o)

FML_NODE_TO_JSON_TESTS_EXECUTABLE_FILE := fml_node_to_json_tests

PHONY: format

# ====================================================================
# Build targets
# ====================================================================

fml_node_to_json_tests: $(FML_NODE_TO_JSON_TESTS_OBJECT_FILES)
	$(CC) $(CFLAGS) -o $(FML_NODE_TO_JSON_TESTS_EXECUTABLE_FILE) $^ -lm

fml_web.js: $(FML_WEB_SRC_FILES)
	$(EMCC) -o fml_web.js $^ -s -s EXPORTED_RUNTIME_METHODS="['cwrap']" -s ALLOW_MEMORY_GROWTH=1 -s WASM=1 -s MODULARIZE=1 -s 'EXPORT_NAME="fml_web"' -s 'EXPORT_ES6=1' -s 'EXPORTED_RUNTIME_METHODS=["cwrap"]'

# ====================================================================
# Run tests
# ====================================================================

run-fml-node-to-json-tests: fml_node_to_json_tests
	./$(FML_NODE_TO_JSON_TESTS_EXECUTABLE_FILE)

run-all-tests: run-fml-node-to-json-tests

# ====================================================================
# Development utils
# ====================================================================

format:
	$(CLANG_FORMAT) -i $(FORMAT_FILES)

clean:
	rm -f $(FML_NODE_TO_JSON_TESTS_EXECUTABLE_FILE) $(FML_NODE_TO_JSON_TESTS_OBJECT_FILES)
