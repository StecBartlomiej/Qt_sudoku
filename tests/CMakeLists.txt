FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(TEST_FILES
        tests/sample_test.cpp
        )


qt_add_executable(Tests ${TEST_FILES} ${SOURCE_FILES})
target_link_libraries(Tests PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui GTest::gtest_main)

include(GoogleTest)
add_test(Sudoku Tests)
