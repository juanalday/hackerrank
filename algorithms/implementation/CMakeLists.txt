add_executable(implementation 
  beautiful_triplets.cpp
  between_two_sets.cpp
  bigger_is_greater.cpp
  chocolate_feast.cpp
  halloween_sale.cpp
  minimum_distances.cpp
  modified_kaprekar_numbers.cpp
  service_lane.cpp
  the_time_in_words.cpp
)
target_link_libraries(implementation gmock gtest gtest_main)
gtest_discover_tests(implementation)