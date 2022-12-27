(CXX) = g++
(CXXFLAGS) = -Wall

sim.o: sim.h sim.cpp
	$(CXX) $(CXXFLAGS) -c sim.cpp


gapBuffer.o: gapBuffer.h gapBuffer.cpp
	$(CXX) $(CXXFLAGS) -c gapBuffer.cpp

sim: sim.o gapBuffer.o run.cpp
	$(CXX) $(CXXFLAGS) sim.o gapBuffer.o run.cpp -o sim -lncurses
	
vg:
	valgrind --leak-check=full  --track-origins=yes ./sim
	



