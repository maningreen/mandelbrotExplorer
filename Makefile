SRC = src/*.cpp
CC = g++
LDFLAGS = -lraylib -lm
OUT = mandel

program:
	$(CC) $(SRC) $(LDFLAGS) -o $(OUT)
