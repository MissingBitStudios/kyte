find_package (Python3 REQUIRED)

add_custom_target(kyte_gen_stl ALL
	COMMAND ${Python3_EXECUTABLE} gen.py
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
