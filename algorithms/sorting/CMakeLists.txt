add_executable(sorting
  big_sorting.cpp
  correctness_invariant.cpp
  insertion_sort1.cpp 
  insertion_sort2.cpp
  intro_tutorial.cpp
)
target_link_libraries(sorting gmock gtest gtest_main)
gtest_discover_tests(sorting)