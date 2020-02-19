CC = g++
CFLAGS = -Wall -pedantic -Ofast -std=c++11
LDLIBS = -lm

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:%.cpp=%.o)

HEADERS := $(wildcard *.h)

.PHONY = clean run clean-log

run: main
	./main > run.log

main: ${OBJS}
	${CC} -o main state.o vector.o ${LDLIBS}

mainOld: ${OBJS}
	${CC} -o main main.o body.o kDeltaVector.o ${LDLIBS}

%.o: %.c ${HEADERS}
	${CC} -c ${CFLAGS} $< -o $@

clean:
	rm -f *.o main

clean-log:
	rm -f *.log