
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)
qt_standard_project_setup()

include_directories(src)

set(SOURCE_FILES
        MainWindow.cpp
        SudokuView.cpp
        SudokuModel.cpp
)

set(UI_FILES
        stylesheet.qss
)


qt_add_library(SudokuLib ${SOURCE_FILES})
target_link_libraries(SudokuLib PUBLIC Qt6::Core Qt6::Widgets Qt6::Gui)

target_precompile_headers(SudokuLib
        PRIVATE
        <QMainWindow>
        <QTableView>
        <QAbstractTableModel>
)


qt_add_executable(SudokuApp main.cpp)
target_link_libraries(SudokuApp PUBLIC SudokuLib)

if (CMAKE_BUILD_TYPE STREQUAL "Relase")
    set_target_properties(Sudoku PROPERTIES
            WIN32_EXECUTABLE ON
    )
endif()
