add_executable(sorting
  activity_notifications.cpp
  big_sorting.cpp
  closest_numbers.cpp
  correctness_invariant.cpp
  counting_sort1.cpp
  counting_sort2.cpp
  find_the_median.cpp
  full_counting_sort.cpp
  insertion_sort1.cpp 
  insertion_sort2.cpp
  intro_tutorial.cpp
  lilys_homework.cpp
  quicksort_partition.cpp
  running_time.cpp
)
target_link_libraries(sorting gmock gtest gtest_main)
gtest_discover_tests(sorting)