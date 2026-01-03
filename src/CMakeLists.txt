# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME_LOWER}")

# Optionally glob, but only for CMake 3.12 or later:
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${INCLUDE_DIR}/*.h")

# Make an automatic library - will be static or dynamic based on user setting
add_library(vec3 vec3.c ${HEADER_LIST})
add_library(color color.c ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(vec3 PUBLIC ../include)
target_include_directories(color PUBLIC ../include)

# Pick C11 just because
target_compile_features(vec3 PUBLIC c_std_11)
target_compile_features(color PUBLIC c_std_11)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST}
)
