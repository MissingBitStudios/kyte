add_executable(kyte
	src/kyte.cpp
)

target_link_libraries(kyte libkyte)

set_target_properties(kyte PROPERTIES FOLDER "kyte")
