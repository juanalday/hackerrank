add_executable(sorting
  big_sorting.cpp
 intro_tutorial.cpp
 "insertion_sort1.cpp")
target_link_libraries(sorting gmock gtest gtest_main)
gtest_discover_tests(sorting)