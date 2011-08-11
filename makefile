all:
	make hw7
hw7: hw7.o
	g++ -g -Wall -o hw7 hw7.o
hw7.o: hw7.cpp
	g++ -g -Wall -c hw7.cpp
clean:
	rm *.o hw7
