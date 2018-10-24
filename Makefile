CXX = g++
CXXFLAGS = -std=c++17 -Wall -fext-numeric-literals
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

snake: main.o gamepiece.o playerpiece.o gameboard.o
	$(CXX) $(CXXFLAGS) main.o gamepiece.o playerpiece.o gameboard.o -o snake $(LDLIBS)

main.o: gameboard.o main.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c main.cpp $(LDLIBS)

gameboard.o: gameboard.h playerpiece.o
	$(CXX) $(CXXFLAGS) -o $@ -c gameboard.cpp $(LDLIBS)

playerpiece.o: playerpiece.h gamepiece.o
	$(CXX) $(CXXFLAGS) -o $@ -c playerpiece.cpp $(LDLIBS)

gamepiece.o: gamepiece.h
	$(CXX) $(CXXFLAGS) -o $@ -c gamepiece.cpp $(LDLIBS)
