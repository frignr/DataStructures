CXX = g++
CXXFLAGS = -Wall

driver: joke.o driver.cpp
	$(CXX) $(CXXFLAGS) joke.o driver.cpp -o driver

joke.o: joke.h
	$(CXX) $(CXXFLAGS) -c joke.cpp

clean:
	rm driver
	rm *.o
	rm *~

run: driver
	./driver
