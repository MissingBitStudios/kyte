add_executable(kytec
	src/kyte.cpp
)

target_link_libraries(kytec kyte argparse)

set_target_properties(kytec PROPERTIES FOLDER "kyte")

if(KYTE_INSTALL)
	install(TARGETS kytec DESTINATION bin)
endif()
