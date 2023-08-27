CC = g++
CGFLAGS = -O3 -std=c++14
DEBUGFLAGS = -g
#OBJ = PENDING

# Build miniray
all:
	$(CC) src/main.cpp -o miniray $(CFLAGS)

debug:
	$(CC) $(DEBUGFLAGS) src/main.cpp -o miniray

clean:
	rm src/main
	rm miniray
	rm *.ppm
	rm *.png