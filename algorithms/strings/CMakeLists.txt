add_executable(algorithm_strings
  caesar_cipher.cpp
  camelcase.cpp
  hackerrank_in_a_string.cpp
  mars_exploration.cpp
  pangrams.cpp
  separate_the_numbers.cpp
  strong_password.cpp 
  two_characters.cpp
  weighted_uniform_string.cpp

 "pattern_matching.cpp")
target_link_libraries(algorithm_strings gmock gtest gtest_main)
gtest_discover_tests(algorithm_strings)