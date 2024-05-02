add_executable(graph_theory
  jumping_rocks.cpp
 )
target_link_libraries(graph_theory gmock gtest gtest_main)
gtest_discover_tests(graph_theory)