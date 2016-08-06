#
# OSVR-Display is a library and set of utilities
# that can detect displays (monitors) and set their
# properties (e.g., resolution, orientation)
#

cmake_minimum_required(VERSION 3.1.0)
project(osvrDisplay)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(UseBackportedModules)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(EnableExtraCompilerWarnings)
globally_enable_extra_compiler_warnings()

#
# Options
#
option(BUILD_TESTS "Build test programs and unit tests." ON)

#
# Dependencies
#
find_package(osvr REQUIRED)

# For our generated file
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#
# Third-party libraries
#
add_subdirectory(vendor)


#
# Default installation directories
#

include(GNUInstallDirs)


add_subdirectory(osvr/Display)
add_subdirectory(apps)

if(BUILD_TESTS)
	add_subdirectory(test)
endif()

