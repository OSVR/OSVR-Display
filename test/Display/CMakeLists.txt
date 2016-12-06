#
# Tests on Display functions
#

function(osvr_add_test _test)
	add_executable(test_${_test} test_${_test}.cpp)

	target_link_libraries(test_${_test}
		gtest)

	# Use dynamic libraries on Windows
	if(WIN32)
		target_link_libraries(test_${_test}
			osvrDisplay)
	else()
		target_link_libraries(test_${_test}
			osvrDisplay_static)
	endif()

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

