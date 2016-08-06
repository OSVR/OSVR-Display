#
# Applications for enumerating displays, changing display settings, etc.
#

# For our generated file
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(osvr_display osvr_display.cpp)

target_link_libraries(osvr_display
	PRIVATE
	osvrDisplay
	docopt_s)

target_include_directories(osvr_display
	PRIVATE
	"${CMAKE_SOURCE_DIR}")

set_property(TARGET osvr_display
	PROPERTY CXX_STANDARD 11)

target_compile_features(osvr_display
	PRIVATE cxx_override)

install(TARGETS osvr_display
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Runtime)

