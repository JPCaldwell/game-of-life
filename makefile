all: life

life: life.o driver.o
	g++ -o life life.o driver.o

life.o: life.cpp 
	g++ -c -g life.cpp 

driver.o: driver.cpp
	g++ -c -g driver.cpp

clean:
	rm life.o driver.o life
