CC = g++
CFLAGS = -Wall -pedantic -O -std=c++11
LDLIBS = -lm -lncurses

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:%.cpp=%.o)

HEADERS := $(wildcard *.h)

.PHONY = clean run

run: colors
	./colors

colors: ${OBJS}
	${CC} -o colors colors.o graphics.o ${LDLIBS}

%.o: %.cpp ${HEADERS}
	${CC} -c ${CFLAGS} $< -o $@

clean:
	rm -f *.o colors
