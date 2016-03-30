all: main.cpp uuid.cpp uuid.hpp
	g++ main.cpp uuid.cpp -lrt -o uuid
