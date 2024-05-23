add_executable(implemen_easy
  # acm_icpc_team.cpp https://www.hackerrank.com/challenges/acm-icpc-team/problem
  # angry_professor.cpp https://www.hackerrank.com/challenges/angry-professor/problem
  # append_and_delete.cpp https://www.hackerrank.com/challenges/append-and-delete/problem
  # beautiful_days_at_the_movies.cpp https://www.hackerrank.com/challenges/beautiful-days-at-the-movies/problem
  # bill_division.cpp https://www.hackerrank.com/challenges/bon-appetit/problem
  # breaking_best_and_worst_records.cpp https://www.hackerrank.com/challenges/breaking-best-and-worst-records/problem
  # cats_and_a_mouse.cpp https://www.hackerrank.com/challenges/cats-and-a-mouse/problem
  # circular_array_rotation.cpp https://www.hackerrank.com/challenges/circular-array-rotation/problem
  # counting_valleys.cpp https://www.hackerrank.com/challenges/counting-valleys/problem
  # cut_the_sticks.cpp https://www.hackerrank.com/challenges/cut-the-sticks/problem
  # day_of_the_programmer.cpp https://www.hackerrank.com/challenges/day-of-the-programmer/problem
  # designer_pdf_viewer.cpp https://www.hackerrank.com/challenges/designer-pdf-viewer/problem
  # divisible_sum_pairs.cpp https://www.hackerrank.com/challenges/divisible-sum-pairs/problem
  # drawing_book.cpp https://www.hackerrank.com/challenges/drawing-book/problem
  # electronics_shop.cpp https://www.hackerrank.com/challenges/electronics-shop/problem
  # equalize_the_array.cpp https://www.hackerrank.com/challenges/equality-in-a-array/problem
  # From here on, not checked properly.
  # library_fine.cpp https://www.hackerrank.com/challenges/library-fine/problem
  # migratory_birds.cpp https://www.hackerrank.com/challenges/migratory-birds/problem
  # organizing_containers_of_balls.cpp https://www.hackerrank.com/challenges/organizing-containers-of-balls/problem
  # permutation_equation.cpp https://www.hackerrank.com/challenges/permutation-equation/problem
  # picking_numbers.cpp https://www.hackerrank.com/challenges/picking-numbers/problem
  # repeated_string.cpp https://www.hackerrank.com/challenges/repeated-string/problem
  # sales_by_match.cpp https://www.hackerrank.com/challenges/sock-merchant/problem
  # save_the_prisoner.cpp https://www.hackerrank.com/challenges/save-the-prisoner/problem
  # sherlock_and_squares.cpp https://www.hackerrank.com/challenges/sherlock-and-squares/problem
  # subarray_division.cpp https://www.hackerrank.com/challenges/the-birthday-bar/problem?isFullScreen=true
  # taum_and_bday.cpp https://www.hackerrank.com/challenges/taum-and-bday/problem
  # the_hurdle_race.cpp https://www.hackerrank.com/challenges/the-hurdle-race/problem
  # utopian_tree.cpp https://www.hackerrank.com/challenges/utopian-tree/problem
  # viral_advertising.cpp https://www.hackerrank.com/challenges/strange-advertising/problem
  apple_and_orange.cpp
  beautiful_triplets.cpp
  between_two_sets.cpp
  cavity_map.cpp
  chocolate_feast.cpp
  fair_rations.cpp
  find_digits.cpp
  flatland_space_stations.cpp
  grading_students.cpp
  halloween_sale.cpp
  happy_ladybugs.cpp
  jumping_on_the_clouds.cpp
  jumping_on_the_clouds_revisited.cpp
  lisas_workbook.cpp
  manasa_and_stones.cpp
  minimum_distances.cpp
  modified_kaprekar_numbers.cpp
  number_line_jumps.cpp
  service_lane.cpp
  strange_counter.cpp
  )
target_link_libraries(implemen_easy gmock gtest gtest_main)
gtest_discover_tests(implemen_easy)

add_executable(implemen_medium
  3d_surface_area.cpp
  absolute_permutation.cpp
  almost_sorted.cpp
  bigger_is_greater.cpp
  forming_a_magic_square.cpp
  climbing_the_leaderboard.cpp
  encryption.cpp
  extra_long_factorials.cpp
  larrys_array.cpp
  non_divisive_subset.cpp
  organizing_containers_of_balls.cpp
  queens_attack_2.cpp
  the_bomberman_game.cpp
  the_grid_search.cpp
  the_time_in_words.cpp
  two_pluses.cpp
)

target_link_libraries(implemen_medium gmock gtest gtest_main)
gtest_discover_tests(implemen_medium)

add_executable(implemen_hard
    matrix_layer_rotation.cpp
  )
target_link_libraries(implemen_hard gmock gtest gtest_main)
gtest_discover_tests(implemen_hard)