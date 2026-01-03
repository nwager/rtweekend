# Tests need to be added as executables first
add_executable(testlib test.c)

# Using C11 in the test
target_compile_features(testlib PRIVATE c_std_11)

# Should be linked to the main library
target_link_libraries(testlib PRIVATE vec3)

# If you register a test, then ctest and make test will run it.
# You can also run examples and check the output, as well.
add_test(NAME testlibtest COMMAND testlib) # Command can be a target
