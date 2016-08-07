
# Google test
if(BUILD_TESTS AND NOT TARGET gmock)
	if(WIN32)
		set(gtest_force_shared_crt ON)
	endif()
	set(BUILD_GTEST ON)
	add_subdirectory(googletest)
endif()

# docopt.cpp
add_subdirectory(docopt.cpp)

