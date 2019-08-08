add_custom_target(libkyte_util ALL
	COMMAND bison -d kyte.y
	COMMAND flex kyte.l
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(libkyte_util PROPERTIES FOLDER "kyte")
