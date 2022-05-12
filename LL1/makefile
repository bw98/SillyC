CXXFLAGS = -Wall -g -std=c++11
test : Base.o Table.o main.o
	g++ $(CXXFLAGS) Base.o Table.o main.o -o test
main.o : main.cpp Base.h Table.h
	g++ $(CXXFLAGS) -c main.cpp
Table.o : Table.cpp Table.h
	g++ $(CXXFLAGS) -c Table.cpp
Base.o: Base.cpp Base.h
	g++ $(CXXFLAGS) -c Base.cpp
clean : 
	rm Base.o Table.o main.o
