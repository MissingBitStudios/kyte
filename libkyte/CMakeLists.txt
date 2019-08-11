add_library(libkyte STATIC
	src/kyte.cpp
	src/parser.cpp
	src/parser.yy

	include/kyte/kyte.hpp
)

target_include_directories(libkyte PUBLIC include)

set_target_properties(libkyte PROPERTIES FOLDER "kyte")

if(KYTE_UTIL)
	add_custom_target(libkyte_util ALL
		COMMAND bison parser.yy -o parser.cpp.re
		COMMAND re2c parser.cpp.re -o parser.cpp
		SOURCES src/parser.yy
		BYPRODUCTS src/parser.cpp.re src/parser.cpp
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
	)

	add_dependencies(libkyte libkyte_util)

	set_target_properties(libkyte_util PROPERTIES FOLDER "kyte")
endif()
