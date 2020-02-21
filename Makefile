CC = g++
CFLAGS = -Wall -pedantic -Ofast -std=c++11
LDLIBS = -lm

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:%.cpp=%.o)

HEADERS := $(wildcard *.h)

.PHONY = clean run clean-log trim-log

run: main
	./main > run.log

main: ${OBJS}
	${CC} -o main main.o state.o vector.o ${LDLIBS}

%.o: %.cpp ${HEADERS}
	${CC} -c ${CFLAGS} $< -o $@

clean:
	rm -f *.o main

clean-log:
	rm -f *.log

trim-log:
	rm runTrimmed.log
	awk "NR % 10 == 0 {print}" run.log > runTrimmed.log
	@echo runTrimmed.log has $(wc -l runTrimmed.log) lines
