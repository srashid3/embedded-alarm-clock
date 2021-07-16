CC:=gcc
CFLAGS:=-Iinclude

DEBUG_MODE:=true

ifeq ($(DEBUG_MODE), true)
	CFLAGS:=$(CFLAGS) -DDEBUG_MODE
endif

SRC_DIR:=src
SRC:=$(wildcard $(SRC_DIR)/**/*.c)

TEST_DIR:=tests
TEST:=$(wildcard $(TEST_DIR)/*.c)
TEST_DEP:=$(SRC_DIR)/pic/18f4520.c $(SRC_DIR)/lcd/hd44780.c

all: main utest

main: $(SRC)
	$(CC) -o main $^ -lpthread $(CFLAGS)

utest: $(TEST) $(TEST_DEP)
	$(CC) -o utest $^ $(CFLAGS)

clean:
	rm -f main utest
