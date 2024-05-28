add_executable(strings_easy
  alternating_characters.cpp
  anagram.cpp
  beautiful_binary_string.cpp
  caesar_cipher.cpp
  camelcase.cpp
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
 )
target_link_libraries(strings_easy gmock gtest gtest_main)
gtest_discover_tests(strings_easy)

 add_executable(strings_medium
   bear_and_steady_gene.cpp
   common_child.cpp
   maximum_palindrome.cpp
   sherlock_and_anagrams.cpp
   sherlock_and_the_valid_string.cpp
 )
target_link_libraries(strings_medium gmock gtest gtest_main)
gtest_discover_tests(strings_medium)

add_executable(strings_hard
  determining_dna_health.cpp
  string_function_calculation.cpp
)
target_link_libraries(strings_hard gmock gtest gtest_main)
gtest_discover_tests(strings_hard)

add_executable(strings_expert
  morgan_and_a_string.cpp
  count_strings.cpp
)
target_link_libraries(strings_expert gmock gtest gtest_main)
gtest_discover_tests(strings_expert)