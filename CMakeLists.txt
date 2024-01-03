cmake_minimum_required(VERSION 3.27)
project(life C)

set(CMAKE_C_STANDARD 99)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG=1)
endif()

find_package(SDL2 REQUIRED COMPONENTS SDL2)
find_package(SDL2_ttf REQUIRED)

add_executable(life src/main.c
        src/log.h
        src/board.c
        src/board.h
        src/game.c
        src/game.h
        src/input.c
        src/input.h
        src/ui.c
        src/ui.h
        src/color.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} SDL2_ttf::SDL2_ttf)
