add_executable(main main.c)
target_compile_features(main PRIVATE c_std_11)

# Project libs
target_link_libraries(main PRIVATE camera)
target_link_libraries(main PRIVATE vec3)
target_link_libraries(main PRIVATE color)
target_link_libraries(main PRIVATE ray)
target_link_libraries(main PRIVATE sphere)
target_link_libraries(main PRIVATE hittable)
target_link_libraries(main PRIVATE hittable_list)

# stdlibs
target_link_libraries(main PRIVATE m)
