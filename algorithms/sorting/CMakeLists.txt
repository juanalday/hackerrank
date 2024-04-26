add_executable(sorting
  big_sorting.cpp
)
target_link_libraries(sorting gmock gtest gtest_main)
gtest_discover_tests(sorting)