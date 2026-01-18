# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME_LOWER}")

# Optionally glob, but only for CMake 3.12 or later:
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${INCLUDE_DIR}/*.h")

function(new_library lib_name)
	# Make an automatic library - will be static or dynamic based on user setting
	add_library(${lib_name} ${ARGN})
	# We need this directory, and users of our library will need it too
	target_include_directories(${lib_name} PUBLIC ../include)
	# Pick C11 just because
	target_compile_features(${lib_name} PUBLIC c_std_11)
endfunction()

new_library(vec3 vec3.c "${HEADER_LIST}")
new_library(color color.c "${HEADER_LIST}")
new_library(ray ray.c "${HEADER_LIST}")
new_library(sphere sphere.c "${HEADER_LIST}")
new_library(hittable hittable.c "${HEADER_LIST}")
new_library(hittable_list hittable_list.c "${HEADER_LIST}")
new_library(camera camera.c "${HEADER_LIST}")

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST}
)
