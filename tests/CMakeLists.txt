
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


include_directories(${Qt_sudoku_SOURCE_DIR}/src)

set(TEST_FILES
        sample_test.cpp
)


add_executable(Tests ${TEST_FILES})
target_link_libraries(Tests PUBLIC SudokuLib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(Tests)
