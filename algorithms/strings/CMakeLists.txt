add_executable(a_strings
  alternating_characters.cpp
  anagram.cpp
  beautiful_binary_string.cpp
  caesar_cipher.cpp
  camelcase.cpp
  determining_dna_health.cpp
  funny_string.cpp
  game_of_thrones.cpp
  gem_stones.cpp
  hackerrank_in_a_string.cpp
  highest_value_palindrome.cpp
  making_anagrams.cpp
  mars_exploration.cpp
  palindrome_index.cpp
  pangrams.cpp
  pattern_matching.cpp
  separate_the_numbers.cpp
  string_construction.cpp
  strong_password.cpp
  the_love_letter_mistery.cpp
  two_characters.cpp
  two_strings.cpp 
  weighted_uniform_string.cpp
 "sherlock_and_the_valid_string.cpp" "maximum_palindrome.cpp")
  
target_link_libraries(a_strings gmock gtest gtest_main)
gtest_discover_tests(a_strings)