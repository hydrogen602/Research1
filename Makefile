CC = g++
CFLAGS = -Wall -pedantic -std=c++11 -Ofast
LDLIBS = -lm -lncurses

SRCS := $(wildcard *.cpp)
SRCS += $(wildcard graphics/*.cpp)
SRCS += $(wildcard data/*.cpp)
OBJS := $(SRCS:%.cpp=%.o)

HEADERS := $(wildcard *.h)

.PHONY = clean run clean-log trim-log

run: main
	./main 2> run.err.log

main: ${OBJS}
	${CC} -o main main.o state.o vector.o graphics/graphics.o data/vector3.o graphics/screenState.o ${LDLIBS}

tests: ${OBJS}
	${CC} -o tests tests.o state.o vector.o graphics/graphics.o data/vector3.o ${LDLIBS}

%.o: %.cpp ${HEADERS}
	${CC} -c ${CFLAGS} $< -o $@

graphics/%.o: graphics/%.cpp ${HEADERS}
	${CC} -c ${CFLAGS} $< -o $@

data/%.o: data/%.cpp ${HEADERS}
	${CC} -c ${CFLAGS} $< -o $@

clean:
	rm -f *.o graphics/*.o data/*.o main

clean-log:
	rm -f *.log

trim-log:
	rm runTrimmed.log
	awk "NR % 10 == 0 {print}" run.log > runTrimmed.log
	@echo runTrimmed.log has $(wc -l runTrimmed.log) lines
