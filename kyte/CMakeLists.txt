add_library(kyte STATIC
	src/kyte.cpp
	src/kyte_p.hpp

	src/parser.cpp
	src/parser.yy

	src/backend.cpp
	src/glsl.cpp
	src/hlsl.cpp
	src/msl.cpp
	src/spirv.cpp

	include/kyte/kyte.hpp
)

target_include_directories(kyte PUBLIC include)

set_target_properties(kyte PROPERTIES FOLDER "kyte")

if(KYTE_GRAMMAR)
	add_custom_command(TARGET kyte PRE_BUILD
		COMMAND bison parser.yy -o parser.cpp.re
		COMMAND re2c parser.cpp.re -o parser.cpp
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
		VERBATIM
		MAIN_DEPENDENCY src/parser.yy
	)
endif()
