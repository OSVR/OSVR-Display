#
# Applications for enumerating displays, changing display settings, etc.
#

# For our generated file
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(CMakeParseArguments REQUIRED)

function(add_osvr_display_executable appname)
	set(options "") # no options
	set(singleValueArgs "") # no single-value arguments
	set(multiValueArgs LIBS SOURCES INCLUDE_DIRS) # lists of additional libraries and source files
	cmake_parse_arguments(add_osvr_display_executable "${options}" "${singleValueArgs}" "${multiValueArgs}" ${ARGN})

	add_executable(${appname} ${appname}.cpp ${add_osvr_display_executable_SOURCES})
	target_link_libraries(${appname} PRIVATE ${add_osvr_display_executable_LIBS})
	target_include_directories(${appname} PRIVATE ${add_osvr_display_executable_INCLUDE_DIS})
	set_property(TARGET ${appname} PROPERTY CXX_STANDARD 11)
	target_compile_features(${appname} PRIVATE cxx_override)
	install(TARGETS ${appname}
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Runtime)
endfunction()

if(HAVE_DOCOPT)
	add_osvr_display_executable(osvr_display
		LIBS osvrDisplay_static docopt_s
		INCLUDE_DIRS "${CMAKE_SOURCE_DIR}")
else()
	message(WARNING "The osvr_display app requires Visual Studio 2015 or above.")
endif()

add_osvr_display_executable(osvr_edid_vendor_id
	LIBS osvrDisplay_static
	INCLUDE_DIRS "${CMAKE_SOURCE_DIR}")

add_osvr_display_executable(osvr_print_displays
	LIBS osvrDisplay_static
	INCLUDE_DIRS "${CMAKE_SOURCE_DIR}")


