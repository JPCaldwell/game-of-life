all: life

life: life.o driver.o
	g++ -o life life.o driver.o

life.o: life.cpp life.h
	g++ -c life.cpp life.h

driver.o: driver.cpp
	g++ -c driver.cpp

clean:
	rm life.o driver.o life life.h.gch
