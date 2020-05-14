#argparse
add_subdirectory(argparse)

#googletest
if(KYTE_TESTS)
	set(gtest_force_shared_crt  ON CACHE INTERNAL "")
	set(BUILD_GMOCK             OFF CACHE INTERNAL "")
	set(INSTALL_GTEST           OFF CACHE INTERNAL "")
	add_subdirectory(googletest)
endif()

#SPIRV-Headers
add_subdirectory(SPIRV-Headers)

#SPIRV-Tools
add_subdirectory(SPIRV-Tools)

#SPIRV-Cross
add_subdirectory(SPIRV-Cross)
