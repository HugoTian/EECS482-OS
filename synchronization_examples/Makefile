CFLAGS = -g
all: producerconsumer

producerconsumer: producerconsumer.o randomdelay.o
	g++ -g -o producerconsumer producerconsumer.o randomdelay.o -lpthread

.cc.o:
	g++ $(CFLAGS) -c $<

clean: 
	rm *.o producerconsumer
