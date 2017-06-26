all:
	g++ -o PJCC Bin/*.cc -lSDL2

clean:
	rm PJCC