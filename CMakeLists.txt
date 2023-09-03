cmake_minimum_required(VERSION 3.16)

project(Qt_sudoku)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (!MSVC)
    add_compile_options(-Wall -Wextra -pedantic -Werror -O3)
endif()


find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)
qt_standard_project_setup()
set(CMAKE_AUTORCC  ON)

include_directories(src ${CMAKE_BINARY_DIR})


set(SOURCE_FILES
        main.cpp
        src/MainWindow.cpp
        src/QSudokuWidget.cpp
        src/Cell.cpp
        src/Sudoku.cpp
        )

set(UI_FILES
        stylesheet.qss
        )

qt_add_executable(Sudoku ${SOURCE_FILES} ${UI_FILES})
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

