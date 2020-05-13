add_executable(kytecli
	src/kyte.cpp
)

target_link_libraries(kytecli kyte argparse)

set_target_properties(kytecli PROPERTIES FOLDER "kyte")
