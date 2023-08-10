all: compile link
	./sfml-app

compile:
	g++ -c main.cpp -Iinclude

link:
	g++ main.o -o sfml-app -Llib -lsfml-graphics -lsfml-window -lsfml-system