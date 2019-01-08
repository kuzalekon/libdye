
TARGET ?= dye

INCLUDE_DIR := ./include
SOURCE_DIR  := ./src
BUILD_DIR   := ./build
RELEASE_DIR := $(BUILD_DIR)/release
DEBUG_DIR   := $(BUILD_DIR)/debug

SOURCES := $(SOURCE_DIR)/dye.c

CC      ?= gcc
CCFLAGS := -c -I"$(INCLUDE_DIR)" -Wall -Wextra -static -std=gnu99

AR      := ar
ARFLAGS := rcs

MD      := mkdir
MDFLAGS := -p

RM      := rm
RMFLAGS := -rf

.PHONY: all
all: release debug

.PHONY: release
release:
	$(MD) $(MDFLAGS) "$(BUILD_DIR)/$@"
	$(CC) $(CCFLAGS) -D"NDEBUG" -O3 -o "$(BUILD_DIR)/$@/dye.o" $(UCCFLAGS) $(SOURCES)
	$(AR) $(ARFLAGS) $(UARFLAGS) "$(BUILD_DIR)/$@/lib$(TARGET).a" "$(BUILD_DIR)/$@/dye.o"

.PHONY: debug
debug:
	$(MD) $(MDFLAGS) "$(BUILD_DIR)/$@"
	$(CC) $(CCFLAGS) -D"DEBUG" -D"_DEBUG" -g -Og -o "$(BUILD_DIR)/$@/dye.o" $(UCCFLAGS) $(SOURCES)
	$(AR) $(ARFLAGS) $(UARFLAGS) "$(BUILD_DIR)/$@/lib$(TARGET).a" "$(BUILD_DIR)/$@/dye.o"

.PHONY: clean
clean:
	$(RM) $(RMFLAGS) $(BUILD_DIR)
