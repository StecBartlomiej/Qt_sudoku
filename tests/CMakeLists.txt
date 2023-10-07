
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(TEST_FILES
        SudokuModelCell.cpp
        SudokuModelRules.cpp
        SudokuModel.cpp
        SudokuBoard.cpp
        SudokuSolver.cpp
)


add_executable(Tests ${TEST_FILES})
target_link_libraries(Tests PUBLIC SudokuLib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(Tests)
