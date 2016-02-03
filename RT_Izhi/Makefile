CC = g++
DFLAG =

all: temp

temp: main.o Neuron.o GPe.o GPi.o STN.o TC.o
	$(CC) main.o Neuron.o GPe.o GPi.o STN.o TC.o -lm -lgsl -lgslcblas -o temp

main.o: main.cpp
	$(CC) $(DFLAG) -c main.cpp
Neuron.o: Neuron.cpp
	$(CC) -c Neuron.cpp

GPe.o: GPe.cpp
	$(CC) $(DFLAG) -c GPe.cpp

GPi.o: GPi.cpp
	$(CC) $(DFLAG) -c GPi.cpp
STN.o: STN.cpp
	$(CC) $(DFLAG) -c STN.cpp
TC.o: TC.cpp
	$(CC) $(DFLAG) -c TC.cpp

clean:
	rm -rf *o temp


