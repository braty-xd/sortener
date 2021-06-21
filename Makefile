all:
	g++ -lncurses main.cpp -o main

install:
	g++ -lncurses main.cpp -o /usr/local/bin/sortener

clean:
	rm -rf /usr/local/bin/sortener
