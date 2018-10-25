CC = g++
CFLAGS = -Wall -g
LDFLAGS = -lglfw -lGLEW -lGL -lassimp

test: main.o camera.o input.hpp render.hpp shader.hpp mesh.hpp instance.hpp
	$(CC) $(CFLAGS) main.o camera.o $(LDFLAGS) -o test

camera.o: camera.cpp camera.hpp
	$(CC) $(CFLAGS) -c camera.cpp

main.o: main.cpp world.hpp utility.hpp superheader.hpp input.hpp render.hpp shader.hpp mesh.hpp instance.hpp camera.hpp
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm -r *.o test
