add_library(kyte STATIC
	src/kyte.cpp
	src/parser.cpp
	src/parser.yy
	src/kyte_p.hpp

	src/backend.cpp
	src/glsl.cpp
	src/hlsl.cpp
	src/metal.cpp
	src/spirv.cpp

	include/kyte/kyte.hpp
)

target_include_directories(kyte PUBLIC include)

set_target_properties(kyte PROPERTIES FOLDER "kyte")

if(KYTE_GRAMMAR)
	add_custom_target(kyte_grammar ALL
		COMMAND bison parser.yy -o parser.cpp.re
		COMMAND re2c parser.cpp.re -o parser.cpp
		SOURCES src/parser.yy
		BYPRODUCTS src/parser.cpp.re src/parser.cpp
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
	)

	add_dependencies(kyte kyte_grammar)

	set_target_properties(kyte_grammar PROPERTIES FOLDER "kyte")
endif()
