

CC=gcc

SOURCE_FILES_DIRECTORY=src
OBJECT_FILES_DIRECTORY=obj
BINARY_DIRECTORY=bin

##
## >>>>>>>>>> Main section >>>>>>>>>>
##
PROD_CFLAGS=-Wall -Wextra -Werror -ansi -pedantic
PROD_LDFLAGS=

PROD_SOURCE_FILES=$(shell find $(SOURCE_FILES_DIRECTORY) -name '*.c')
PROD_OBJECT_FILES=$(subst $(SOURCE_FILES_DIRECTORY),$(OBJECT_FILES_DIRECTORY),$(PROD_SOURCE_FILES:.c=.o))

.PHONY: default
default: run-tests

.PHONY: obj-directory
obj-directory:
	@mkdir -p $(OBJECT_FILES_DIRECTORY)

.PHONY: objects
objects: obj-directory $(PROD_OBJECT_FILES)

$(OBJECT_FILES_DIRECTORY)/%.o: $(SOURCE_FILES_DIRECTORY)/%.c
	$(CC) $(PROD_CFLAGS) $^ -c -o $@
##
## <<<<<<<<<< Main section <<<<<<<<<<
##




##
## >>>>>>>>>> Tests section >>>>>>>>>>
##
# Criterion is not C89 compliant
TESTS_CFLAGS=$(subst -ansi,,$(PROD_CFLAGS))
TESTS_LDFLAGS=-lcriterion

# Tests directories
TESTS_DIRECTORY=tests
TESTS_SOURCES_DIRECTORY=$(addprefix $(TESTS_DIRECTORY)/,$(SOURCE_FILES_DIRECTORY))
TESTS_BINARIES_DIRECTORY=$(addprefix $(TESTS_DIRECTORY)/,$(BINARY_DIRECTORY))

# Tests files
TESTS_SOURCE_FILES=$(shell find $(TESTS_SOURCES_DIRECTORY) -name '*.c')
TESTS_BINARIES=$(subst $(TESTS_SOURCES_DIRECTORY),$(TESTS_BINARIES_DIRECTORY),$(TESTS_SOURCE_FILES:.c=))

.PHONY: tests-bin-directory
tests-bin-directory:
	@mkdir -p $(TESTS_BINARIES_DIRECTORY)

.PHONY: tests-binaries
tests-binaries: tests-bin-directory objects $(TESTS_BINARIES)

$(TESTS_BINARIES_DIRECTORY)/%: $(TESTS_SOURCES_DIRECTORY)/%.c
	$(CC) $(TESTS_LDFLAGS) $(PROD_OBJECT_FILES) $^ -o $@

.PHONY: run-tests
run-tests: tests-binaries
	for binary in $(TESTS_BINARIES); do ./$$binary --verbose; done
##
## <<<<<<<<<< Tests section <<<<<<<<<<
##




##
## >>>>>>>>>> Common section >>>>>>>>>>
##
.PHONY: clean
clean:
	rm -f $(PROD_OBJECT_FILES)

.PHONY: cleanall
cleanall: clean
	rm -f $(TESTS_BINARIES)
##
## <<<<<<<<<< Common section <<<<<<<<<<
##
