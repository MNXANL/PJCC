all:
	g++ -o PJCC Bin/*.cc -lSDL2 -lSDL_mixer

clean:
	rm PJCC