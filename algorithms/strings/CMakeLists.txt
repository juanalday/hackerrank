add_executable(algorithm_strings
  alternating_characters.cpp
  beautiful_binary_string.cpp
  caesar_cipher.cpp
  camelcase.cpp
  funny_string.cpp
  gem_stones.cpp
  hackerrank_in_a_string.cpp
  highest_value_palindrome.cpp
  mars_exploration.cpp
  pangrams.cpp
  pattern_matching.cpp
  separate_the_numbers.cpp
  strong_password.cpp 
  two_characters.cpp
  weighted_uniform_string.cpp
   "the_love_letter_mistery.cpp")
  
target_link_libraries(algorithm_strings gmock gtest gtest_main)
gtest_discover_tests(algorithm_strings)