CC = g++
CFLAGS = -Wall -pedantic -Ofast
LDLIBS = -lm

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:%.cpp=%.o)

HEADERS := $(wildcard *.h)

.PHONY = main clean run

run: main
	./main | tee run.log | less

main: ${OBJS}
	${CC} -o main state.o vector.o ${LDLIBS}

mainOld: ${OBJS}
	${CC} -o main main.o body.o kDeltaVector.o ${LDLIBS}

%.o: %.c ${HEADERS}
	${CC} -c ${CFLAGS} $< -o $@

clean:
	rm -f *.o main
