if(KYTE_INSTALL)
	include(GNUInstallDirs)
	install(DIRECTORY modules/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/kyte/modules
			FILES_MATCHING PATTERN "*.ky")
endif()

if(KYTE_GEN_STL)
	find_package (Python3 REQUIRED)

	add_custom_target(kyte_gen_stl ALL
		COMMAND ${Python3_EXECUTABLE} gen.py
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)
endif()
