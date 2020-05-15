add_library(kyte STATIC
	src/kyte.cpp
	src/kyte_p.hpp
	src/binary.cpp
	src/binary.tpp
	src/parser.cpp
	src/parser.yy

	include/kyte/kyte.hpp
)

target_include_directories(kyte PUBLIC include)

target_link_libraries(kyte SPIRV-Tools SPIRV-Tools-opt SPIRV-Tools-link spirv-cross-glsl spirv-cross-msl spirv-cross-hlsl)

set_target_properties(kyte PROPERTIES FOLDER "kyte")

if(KYTE_GRAMMAR)
	add_custom_target(kyte_grammar ALL
		COMMAND bison parser.yy -o parser.cpp.re
		COMMAND re2c parser.cpp.re -o parser.cpp
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
	)
	set_target_properties(kyte_grammar PROPERTIES FOLDER "kyte" )
	add_dependencies(kyte kyte_grammar)
endif()
