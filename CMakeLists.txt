cmake_minimum_required(VERSION 3.5)

project(TicTacToe LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SDL2_TTF_INCLUDE_DIR /opt/homebrew/Cellar/sdl2_ttf/2.22.0/include/SDL2)
set(SDL2_TTF_LIBRARY /opt/homebrew/Cellar/sdl2_ttf/2.22.0/lib/libSDL2_ttf.dylib)

set(SOURCE_DIR src)
file(GLOB_RECURSE sources ${SOURCE_DIR}/*.cpp ${SOURCE_DIR}/*.h)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${SDL2_TTF_INCLUDE_DIR})

add_executable(TicTacToe ${sources}
        src/GameMode.h)


target_include_directories(TicTacToe PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(TicTacToe PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARY})

add_custom_command(TARGET TicTacToe POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:TicTacToe>/assets)