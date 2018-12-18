
TARGET ?= dye

SRCDIR := ./src
OUTDIR := ./out

SRC := $(SRCDIR)/dye.c
OBJ := $(OUTDIR)/dye.o
LIB := $(OUTDIR)/lib$(TARGET).a

CC ?= gcc
# Default compile flags
CFLAGS ?= -Wall -Wextra -O3 -static -std=gnu99 -c -o $(OBJ)
# Default compile macroses
DFLAGS ?= -DNDEBUG

AR := ar
ARFLAGS := rcs

RM := rm
RMFLAGS := -f

MD := mkdir
MDFLAGS := -p

.PHONY: all
all: build clean

.PHONY: build
build:
	$(MD) $(MDFLAGS) $(OUTDIR)
	$(CC) $(CFLAGS) $(DFLAGS) $(SRC)
	$(AR) $(ARFLAGS) $(LIB) $(OBJ)

.PHONY: rebuild
rebuild: clean build

.PHONY: clean
clean:
	$(RM) $(RMFLAGS) $(OBJ)
