all: server

server: server.o
	g++ -o server -pthread  server.o

server.o: ../server.cpp
	g++ -c -std=c++0x -pthread ../server.cpp

clean: 
	rm server.o server


