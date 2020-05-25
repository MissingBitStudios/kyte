add_library(kyte STATIC
	src/binary.cpp
	src/binary.tpp
	src/compiler.cpp
	src/kyte_p.hpp
	src/parser.cpp
	src/parser.yy

	include/kyte/kyte.hpp
)

target_include_directories(kyte PUBLIC include)

target_link_libraries(kyte SPIRV-Tools SPIRV-Tools-opt SPIRV-Tools-link)

set_target_properties(kyte PROPERTIES PUBLIC_HEADER include/kyte/kyte.hpp)
set_target_properties(kyte PROPERTIES FOLDER "kyte")

if(KYTE_INSTALL)
	include(GNUInstallDirs)
	install(TARGETS kyte
			PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
	)
endif()

if(KYTE_GRAMMAR)
	add_custom_target(kyte_grammar ALL
		COMMAND bison parser.yy -o parser.cpp.re
		COMMAND re2c parser.cpp.re -o parser.cpp
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
	)
	set_target_properties(kyte_grammar PROPERTIES FOLDER "kyte" )
	add_dependencies(kyte kyte_grammar)
endif()
