CC = g++
CGFLAGS = -O3 -std=c++14
#OBJ = PENDING

# Build miniray
all:
	$(CC) src/main.cpp -o miniray

clean:
	rm miniray