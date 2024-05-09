add_executable(algorithm_strings
  camelcase.cpp
  strong_password.cpp)
target_link_libraries(algorithm_strings gmock gtest gtest_main)
gtest_discover_tests(algorithm_strings)