CC = g++
CFLAGS = -Wall -pedantic -O -std=c++11
LDLIBS = -lm -lncurses

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:%.cpp=%.o)

HEADERS := $(wildcard *.h)

.PHONY = clean run test

run: colors
	./colors

colors: ${OBJS}
	${CC} -o colors colors.o graphics.o ${LDLIBS}

test: test_graphics
	./test_graphics

test_graphics: ${OBJS}
	${CC} -o test_graphics test_graphics.o graphics.o screenState.o ${LDLIBS}

%.o: %.cpp ${HEADERS}
	${CC} -c ${CFLAGS} $< -o $@

clean:
	rm -f *.o colors
