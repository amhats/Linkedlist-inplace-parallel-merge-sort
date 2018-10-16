CC = gcc
CFLAGS = -Wall -Werror
# INCLUDE = /data/d1/maple2017/extern/include/  #use this on bpas cluster
INCLUDE = /home/user/maple2017/extern/include/
CLIBS = -lmaplec -lmaple -lhf
TARGET = example

all:$(TARGET)

test_framework.o: test_framework.h
	$(CC) -c $^ -o $@

maple_evaluate.o: maple_evaluate.h
	$(CC) -I $(INCLUDE) -c $^ -o $@

example.o: example.c
	$(CC) -I $(INCLUDE) -c $^ -o $@

$(TARGET): example.o test_framework.o maple_evaluate.o
	$(CC) -o $@ $< $(CLIBS) 



clean: 
	rm -f *.o example 
