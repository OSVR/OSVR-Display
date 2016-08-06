#
# Tests on Display functions
#

add_executable(test_Orientation test_Orientation.cpp)

target_link_libraries(test_Orientation
	gtest
	osvrDisplay)

target_include_directories(test_Orientation
	SYSTEM PRIVATE
	"${gtest_SOURCE_DIR}/include"
	"${CMAKE_SOURCE_DIR}/osvr/Display")

add_test(NAME gtest-test_Orientation
	COMMAND test_Orientation)

set_target_properties(test_Orientation
	PROPERTIES
	FOLDER "osvrDisplay Tests")

