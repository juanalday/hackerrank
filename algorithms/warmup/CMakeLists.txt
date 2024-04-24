add_executable(warmup 
  solve_me_first.cpp
)
target_link_libraries(warmup gmock gtest gtest_main)
gtest_discover_tests(warmup)