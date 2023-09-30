cmake_minimum_required(VERSION 3.16)

project(Qt_sudoku)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(FetchContent)


if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror -O3)
endif()


add_subdirectory(src)

enable_testing()
add_subdirectory(tests)

