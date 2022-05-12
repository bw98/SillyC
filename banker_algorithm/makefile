CXXFLAGS = -Wall -g -std=c++11
test : Banker.o
	g++ $(CXXFLAGS)  Banker.o -o test
Banker.o : Banker.cpp Banker_Process.h Banker_System.h
	g++ $(CXXFLAGS) -c Banker.cpp
Banker_System.o : Banker_System.cpp Banker_System.h
	g++ $(CXXFLAGS) -c Banker_System.cpp
Banker_Process.o : Banker_Process.cpp Banker_Process.h
	g++ $(CXXFLAGS) -c Banker_Process.cpp
clean : 
	rm Banker.o Banker_Process.o Banker_System.o
