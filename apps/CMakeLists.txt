file(GLOB APPS_LIST CONFIGURE_DEPENDS "*.c")

add_executable(main "${APPS_LIST}")
target_compile_features(main PRIVATE c_std_11)
target_include_directories(main PRIVATE "${PROJECT_SOURCE_DIR}/include")

# stdlibs
target_link_libraries(main PRIVATE m)
