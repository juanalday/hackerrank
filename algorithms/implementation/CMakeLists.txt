add_executable(implementation 
  beautiful_triplets.cpp
  modified_kaprekar_numbers.cpp
)
target_link_libraries(implementation gtest gtest_main)
gtest_discover_tests(implementation)