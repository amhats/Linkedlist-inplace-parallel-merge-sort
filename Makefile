CC = gcc
DFLAGS = 
LFLAGS = -lgmp -lcilkrts 
BINARY = testlist
INCLUDE = datatype.h error.h linkedlist.h test.h
SOURCE = error.c linkedlist.c main.c
MAPLE_INCLUDE = /home/user/maple2017/extern/include/
MAPLE_CLIBS = -lmaplec -lmaple -lhf

all: $(BINARY) 

debug: DFLAGS += -g
debug: $(BINARY) 

$(BINARY): $(SOURCE) 
	$(CC) -I$(MAPLE_INCLUDE) -fcilkplus -fopenmp -o $@ $^ $(DFLAGS) $(LFLAGS) $(MAPLE_CLIBS)

.PHONY:

clean:
	rm *.o testlist 

valgrind-test:
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes -v ./$(BINARY)
valgrind-simple-test:
	valgrind --leak-check=full ./$(BINARY)

remove-csv:
	rm record_time.csv
