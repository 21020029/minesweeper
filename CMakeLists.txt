cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 14)

project(minesweeper)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${project_SOURCE_DIR}/cmake")
set(SDL2_INCLUDE_DIR /usr/local/include/SDL2/)
set(SDL2_LIB_DIR /usr/local/lib/)


include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(minesweeper main.cpp 
InitWindows.hpp 
Texture.hpp 
Button.hpp
loadMedia.hpp 
Variables.hpp 
Constances.hpp )

target_link_libraries(minesweeper ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_MIXER_LIBRARY} ${SDL2_TTF_LIBRARY} -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf)



