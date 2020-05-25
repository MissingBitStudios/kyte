add_executable(kytec
	src/kyte.cpp
)

target_link_libraries(kytec kyte argparse)

set_target_properties(kytec PROPERTIES FOLDER "kyte")

if(KYTE_INSTALL)
	include(GNUInstallDirs)
	install(TARGETS kytec DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()
