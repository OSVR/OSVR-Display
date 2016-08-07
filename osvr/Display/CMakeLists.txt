#
# Display detection
#

# Find path to osvr/Util/PlatformConfiguration.h
get_target_property(osvrUtil_INCLUDE_DIRS
	osvr::osvrUtil INTERFACE_INCLUDE_DIRECTORIES)

# Link against platform-specific libraries
if(APPLE)
	# find_library must be used for OS X frameworks
	find_library(COREFOUNDATION_LIBRARY CoreFoundation)
	find_library(COREGRAPHICS_LIBRARY CoreGraphics)
	find_library(IOKIT_LIBRARY IOKit)
	set(_osvrDisplay_deps
		${COREFOUNDATION_LIBRARY}
		${COREGRAPHICS_LIBRARY}
		${IOKIT_LIBRARY})
endif()

# Source files for both dynamic and static library
set(_osvrDisplay_src
	Display.h
	Display.cpp
	DisplayCommon_MacOSX.h
	DisplayCommon_Windows.h
	DisplayConfiguration.cpp
	DisplayConfiguration.h
	DisplayConfiguration_Linux.h
	DisplayConfiguration_MacOSX.h
	DisplayConfiguration_Windows.h
	DisplayEnumerator.cpp
	DisplayEnumerator.h
	DisplayEnumerator_Linux.h
	DisplayEnumerator_MacOSX.h
	DisplayEnumerator_Windows.h
	DisplayIO.h
	"${CMAKE_CURRENT_BINARY_DIR}/Export.h"
)

# Dynamic library
add_library(osvrDisplay
	SHARED ${_osvrDisplay_src})
target_link_libraries(osvrDisplay
	PRIVATE ${_osvrDisplay_deps})
target_include_directories(osvrDisplay
	PUBLIC ${osvrUtil_INCLUDE_DIRS})

# Static library
add_library(osvrDisplay_static
	STATIC ${_osvrDisplay_src})
target_link_libraries(osvrDisplay_static
	PRIVATE ${_osvrDisplay_deps})
target_include_directories(osvrDisplay_static
	PUBLIC ${osvrUtil_INCLUDE_DIRS})

#if(UNIX AND CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
#	set_target_properties(osvrDisplay
#		PROPERTIES COMPILE_FLAGS "-fPIC")
#endif()

set_property(TARGET osvrDisplay
	PROPERTY POSITION_INDEPENDENT_CODE 1)

# Generate export header
include(GenerateExportHeader)
generate_export_header(osvrDisplay
	BASE_NAME OSVR_DISPLAY
	EXPORT_FILE_NAME Export.h)
target_compile_definitions(osvrDisplay_static
	PUBLIC OSVR_DISPLAY_STATIC_DEFINE)

