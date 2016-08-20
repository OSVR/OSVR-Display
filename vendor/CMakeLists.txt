
# Google test
if(BUILD_TESTS AND NOT TARGET gmock)
	message(STATUS "BUILD_SHARED_LIBS = ${BUILD_SHARED_LIBS}")
	if(WIN32)
		set(gtest_force_shared_crt OFF)
	endif()
	set(BUILD_GTEST ON)
	add_subdirectory(googletest)
endif()

# docopt.cpp
if(BUILD_APPS AND HAVE_DOCOPT)
	add_subdirectory(docopt.cpp)
endif()

