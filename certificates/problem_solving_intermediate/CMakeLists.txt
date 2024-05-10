add_executable(p_s_intermediate
  bitwise_and.cpp
  equalizing_array_elements.cpp
  file_renaming.cpp
  hotel_construction.cpp
  largest_area.cpp
  maximum_subarray_value.cpp
  nice_teams.cpp
  sorted_sums.cpp
  task_of_pairing.cpp 
  user_friendly_password_system.cpp
)
target_link_libraries(p_s_intermediate gmock gtest gtest_main)
gtest_discover_tests(p_s_intermediate)