
set(TEST_FILES
        tests/test_SudokuModel.cpp
        )


qt_add_executable(Tests ${TEST_FILES} ${SOURCE_FILES})
target_link_libraries(Tests PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui Qt6::Test)
add_test(NAME Sudoku COMMAND Tests)

