CC = g++
DFLAG = 

all: temp

temp: main.o STN.o
	$(CC) main.o STN.o -lm -lgsl -lgslcblas -o temp

main.o: main.cpp
	$(CC) $(DFLAG) -c main.cpp

STN.o: STN.cpp
	$(CC) $(DFLAG) -c STN.cpp

clean:
	rm -rf *o temp