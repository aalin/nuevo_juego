# Nuevo juego

Another of my game ideas. RPG-thingy set in a strange world.

Map consisting of tiles of different heights and slopes.
Tiles could either be connected to neighbors to form longer slopes, or not at all to form very steep walls.

# Requirements

* CMake
* SDL
* Boost

Math from https://github.com/peteb/p-math
To initialize:

    git submodule init

# Building

    cd src
    cmake .
    make

# Running

Right now you need to run it from the src-directory.

    ./nuevo-juego
