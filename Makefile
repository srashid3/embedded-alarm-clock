CC:=gcc
CFLAGS:=-Iinclude

DEBUG_MODE:=true

ifeq ($(DEBUG_MODE), true)
	CFLAGS:=$(CFLAGS) -DDEBUG_MODE
endif

SRC_DIR:=src
SRC:=$(wildcard $(SRC_DIR)/**/*.c)

all: main

main: $(SRC)
	$(CC) -o main $^ -lpthread $(CFLAGS)

clean:
	rm -f main
