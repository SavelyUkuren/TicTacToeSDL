cmake_minimum_required(VERSION 3.5)

project(TicTacToe LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR src)
file(GLOB_RECURSE sources ${SOURCE_DIR}/*.cpp ${SOURCE_DIR}/*.h)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

add_executable(TicTacToe ${sources})


include(GNUInstallDirs)
install(TARGETS TicTacToe
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

target_include_directories(TicTacToe PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(TicTacToe PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
