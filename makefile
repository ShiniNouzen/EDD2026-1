all: compile

compile: main.cpp
	g++ main.cpp -o tarea -Wall

run:
	./tarea

clean:
	rm -f ./tarea
