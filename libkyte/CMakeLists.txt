add_library(libkyte STATIC
	src/kyte.cpp

	include/kyte/kyte.hpp
)

target_link_libraries(libkyte PRIVATE )

target_include_directories(libkyte PUBLIC include)

set_target_properties(libkyte PROPERTIES FOLDER "kyte")

if(KYTE_UTIL)
  add_subdirectory(util)
endif()
