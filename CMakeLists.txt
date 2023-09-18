cmake_minimum_required(VERSION 3.16)

project(Qt_sudoku)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

enable_testing()

if (!MSVC)
    add_compile_options(-Wall -Wextra -pedantic -Werror -O3)
endif()


find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui Test)
qt_standard_project_setup()

include_directories(src)

set(SOURCE_FILES
        src/MainWindow.cpp
        src/SudokuWidget.cpp
        src/Cell.cpp
        src/Sudoku.cpp
        src/SudokuModel.cpp
        )

set(UI_FILES
        stylesheet.qss
        )

qt_add_executable(Sudoku main.cpp ${SOURCE_FILES} ${UI_FILES})
target_link_libraries(Sudoku PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui)


target_precompile_headers(Sudoku
        PUBLIC
        <QApplication>
        <QMainWindow>
        <QTableWidget>
        <QTableWidgetItem>
        )

if (CMAKE_BUILD_TYPE STREQUAL "Relase")
    set_target_properties(Sudoku PROPERTIES
            WIN32_EXECUTABLE ON
            )
endif()

include(tests/CMakeLists.txt)

