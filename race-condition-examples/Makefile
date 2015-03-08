
CFLAGS = -g
all: race1 race2 race3
race1: race1.o
	g++ -g -o race1 race1.o

race2: race2.o randomdelay.o
	g++ -g -o race2 race2.o randomdelay.o

race3: race3.o randomdelay.o
	g++ -g -o race3 race3.o randomdelay.o -lpthread

.cpp.o:
	g++ $(CFLAGS) -c $<

clean: 
	rm *.o race1 race2 race3
