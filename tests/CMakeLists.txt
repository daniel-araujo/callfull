cmake_minimum_required(VERSION 3.10)

project(callfull_tests)

enable_testing()

add_library(callfull ../callfull.c ../callfull.h)

# For tests defined in a single C file.
function(test_single_c_file target)
    add_executable(${target} ${target}.c)
    target_link_libraries(${target} callfull)
    add_test(NAME ${target} COMMAND ${target})
endfunction(test_single_c_file)

# For tests defined in posix shell.
function(test_sh target)
    add_test(NAME ${target} COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/${target})
endfunction(test_sh)

test_sh(00000_readme_example)
test_single_c_file(00001_calls_callback_when_threshold_is_reached)
test_single_c_file(00002_buffer_is_filled)
test_single_c_file(00003_correct_buffer_data_passed_to_callback)
test_single_c_file(00004_user_is_passed_to_callback)
test_single_c_file(00005_default_user_is_null)
test_single_c_file(00006_increments_i_for_callback)
test_single_c_file(00007_callback_size_is_correct)
