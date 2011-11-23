cmake_minimum_required(VERSION 2.6)

project(nuevo_juego)

find_package(SDL)
find_package(OpenGL)
find_package(Boost)

include_directories(${OPENGL_INCLUDE_DIR} ${SDL_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -Wall -Wextra")

set(SHARED_SOURCES
	engine
	game
	map
	player
)

set(MAIN_SOURCES main ${SHARED_SOURCES})
if(APPLE)
	set(MAIN_SOURCES ${MAIN_SOURCES} sdl/SDLMain.m)
endif(APPLE)

add_executable(nuevo_juego ${MAIN_SOURCES})
set(SHARED_LIBRARIES ${SDL_LIBRARY} ${SDL} ${OPENGL_LIBRARIES})
target_link_libraries(nuevo_juego ${SHARED_LIBRARIES})
