CC = gcc

CFLAGS = -Wall -Wextra -std=c99

TARGET = snail

SRC_DIR = src

${TARGET}: ${SRC_DIR}/snail.c
	${CC} ${CFLAGS} $^ -o $@
