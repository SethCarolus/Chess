cmake_minimum_required(VERSION 4.2.1)

project(Chess C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 5.5
)

FetchContent_MakeAvailable(raylib)

add_executable(${PROJECT_NAME}
  ./src/main.c
  ./src/piece.c
  ./src/board.c
  ./src/renderer.c
  ./src/movement.c
  ./src/asset_manager.c
  ./src/app.c
)

target_link_libraries(${PROJECT_NAME}
  raylib
)
