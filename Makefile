# all:
# 	g++ -Iinclude -Iinclude/SDL2 -Iinclude/headers -Izlib128-dll/include -Llib -Lzlib128-dll/lib -o Main src/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lz
# CXX = g++
# CXXFLAGS = -Iinclude -Iinclude/SDL2 -Iinclude/headers -Izlib128-dll/include -g

# LIBS = -Llib -Lzlib128-dll/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lz

# SRC = src/*.cpp
# EXE = game

# all: $(EXE)

# $(EXE): $(SRC)
# 	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

# debug: $(EXE)
# 	gdb -ex run --args ./$(EXE)

# clean:
# 	rm -f $(EXE)
CXX = g++
CXXFLAGS = -O1 -Wall -Wno-missing-braces -Iinclude -Izlib128-dll/include
LIBS = -Llib -Lzlib128-dll/lib -lraylib -lopengl32 -lgdi32 -lwinmm -lz
SRC = $(wildcard src/*.cpp)
EXE = game

all: $(EXE)

$(EXE): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

debug: $(EXE)
	gdb -ex run --args ./$(EXE)

clean:
	rm -f $(EXE)