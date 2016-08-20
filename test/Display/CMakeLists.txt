#
# Tests on Display functions
#

# Statically link unit test programs to gtest and osvrDisplay libraries
include(MSVCStaticRuntime)

function(osvr_add_test _test)
	add_executable(test_${_test} test_${_test}.cpp)

	target_link_libraries(test_${_test}
		gtest
		osvrDisplay_static)

	target_include_directories(test_${_test}
		SYSTEM PRIVATE
		"${gtest_SOURCE_DIR}/include"
		"${CMAKE_SOURCE_DIR}/osvr/Display")

	add_test(NAME gtest-test_${_test}
		COMMAND test_${_test})

	set_target_properties(test_${_test}
		PROPERTIES
		FOLDER "osvrDisplay Tests")
endfunction()

osvr_add_test(Orientation)
osvr_add_test(EdidVendorId)

