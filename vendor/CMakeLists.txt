
# Google test
if(BUILD_TESTS AND NOT TARGET gmock)
	if(WIN32)
		set(gtest_force_shared_crt ON CACHE BOOL "Use dynamic msvcrt.dll")
	endif()
	set(BUILD_GTEST ON)
	add_subdirectory(googletest)
endif()

# docopt.cpp
if(BUILD_APPS AND HAVE_DOCOPT)
	add_subdirectory(docopt.cpp)
endif()

