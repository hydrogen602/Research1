CC = g++
CFLAGS = -Wall -pedantic -Ofast -std=c++11
LDLIBS = -lm -lncurses

SRCS := $(wildcard *.cpp)
SRCS += $(wildcard graphics/*.cpp)
OBJS := $(SRCS:%.cpp=%.o)

HEADERS := $(wildcard *.h)

.PHONY = clean run clean-log trim-log

run: main
	./main 2> run.err.log

main: ${OBJS}
	${CC} -o main main.o state.o vector.o graphics/graphics.o ${LDLIBS}

%.o: %.cpp ${HEADERS}
	${CC} -c ${CFLAGS} $< -o $@

graphics/%.o: graphics/%.cpp ${HEADERS}
	${CC} -c ${CFLAGS} $< -o $@

clean:
	rm -f *.o main

clean-log:
	rm -f *.log

trim-log:
	rm runTrimmed.log
	awk "NR % 10 == 0 {print}" run.log > runTrimmed.log
	@echo runTrimmed.log has $(wc -l runTrimmed.log) lines
