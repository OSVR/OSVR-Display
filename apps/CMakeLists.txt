#
# Applications for enumerating displays, changing display settings, etc.
#

# For our generated file
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(HAVE_DOCOPT)

	add_executable(osvr_display osvr_display.cpp)

	target_link_libraries(osvr_display
		PRIVATE
		osvrDisplay_static
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
else()
	message(WARNING "The osvr_display app requires Visual Studio 2015 or above.")
endif()

add_executable(osvr_edid_vendor_id osvr_edid_vendor_id.cpp)
target_link_libraries(osvr_edid_vendor_id
	PRIVATE
	osvrDisplay_static
	docopt_s)
target_include_directories(osvr_edid_vendor_id
	PRIVATE
	"${CMAKE_SOURCE_DIR}")
set_property(TARGET osvr_edid_vendor_id
	PROPERTY CXX_STANDARD 11)
target_compile_features(osvr_edid_vendor_id
	PRIVATE cxx_override)
install(TARGETS osvr_edid_vendor_id
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Runtime)

