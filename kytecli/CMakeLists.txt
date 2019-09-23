add_executable(kytecli
	src/kyte.cpp
)

target_link_libraries(kytecli kyte)

set_target_properties(kytecli PROPERTIES FOLDER "kyte")
