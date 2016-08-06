
# Google test
if(BUILD_TESTS)
	if(WIN32)
		set(gtest_force_shared_crt ON)
	endif()
	set(BUILD_GTEST ON)
	add_subdirectory(googletest)
endif()

# docopt.cpp
set(WITH_TESTS ON)
add_subdirectory(docopt.cpp)
unset(WITH_TESTS)

