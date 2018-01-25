OBJS = main.o bin_sem_test1.o bin_sem_test2.o count_sem_test1.o pthr.o threads_test.o
TARGET = test_call
FLAGS = -std=c++11 -Wall -Werror
CC = g++
LIBS = -pthread -ucontext

default: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(FLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CC) $(FLAGS) -c $<

clean:
	rm -rf *.o

clean-all:
	rm -rf *.o $(TARGET)

run:
	./test_call

.PHONY: clean clean-all run

main.o: tests.h
pthr.o: pthr.h
