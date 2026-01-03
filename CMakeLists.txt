# Based on https://gitlab.com/CLIUtils/modern-cmake/-/blob/master/examples/extended-project/CMakeLists.txt

cmake_minimum_required(VERSION 3.15...4.1)

project(
  Raytracer
  VERSION 0.1
  DESCRIPTION "Personal implementation of 'Raytracing in One Weekend' in C"
  LANGUAGES C
)
set(PROJECT_NAME_LOWER "raytracer")

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  # Ensure -std=cxx instead of -std=gxx
  set(CMAKE_C_EXTENSIONS OFF)
  # Nicely support folders in IDEs
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  # Testing only available if this is the main app
  # Note this needs to be done in the main CMakeLists
  # since it calls enable_testing, which must be in the
  # main CMakeLists.
  include(CTest)

  # Docs only available if this is the main app
  find_package(Doxygen)
  if(Doxygen_FOUND)
    add_subdirectory(docs)
  else()
    message(STATUS "Doxygen not found, not building docs")
  endif()
endif()

# The compiled library code is here
add_subdirectory(src)


# The executable code is here
add_subdirectory(apps)

# Testing only available if this is the main app
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
   AND BUILD_TESTING)
  add_subdirectory(tests)
endif()

