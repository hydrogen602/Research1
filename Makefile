CC = g++
CFLAGS = -Wall -pedantic -O -std=c99
LDLIBS = -lm

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:%.cpp=%.o)

HEADERS := $(wildcard *.h)

.PHONY = main clean

main: ${OBJS}
	${CC} -o main main.o body.o ${LDLIBS}

%.o: %.c ${HEADERS}
	${CC} -c ${CFLAGS} $< -o $@

clean:
	rm -f *.o main