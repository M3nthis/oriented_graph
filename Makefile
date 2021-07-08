CXXFLAGS = -std=c++0x #-DNDEBUG -O3

main.exe: main.o
	g++ $(CXXFLAGS) *.o -o main.exe 

main.o: main.cpp graph.h
	g++ $(CXXFLAGS) -c main.cpp -o main.o

.PHONY: clear
clear:
	rm *.o *.exe