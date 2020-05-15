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
set(SPIRV_HEADERS_SKIP_EXAMPLES ON  CACHE INTERNAL "")
set(SPIRV_HEADERS_SKIP_INSTALL  ON  CACHE INTERNAL "")
add_subdirectory(SPIRV-Headers)

#SPIRV-Tools
set(SPIRV_SKIP_EXECUTABLES      ON  CACHE INTERNAL "")
set(SPIRV_SKIP_TESTS            ON  CACHE INTERNAL "")
set(SPIRV_CHECK_CONTEXT         OFF CACHE INTERNAL "")
set(SKIP_SPIRV_TOOLS_INSTALL    ON  CACHE INTERNAL "")
add_subdirectory(SPIRV-Tools)

#SPIRV-Cross
set(SPIRV_CROSS_ENABLE_TESTS    OFF CACHE INTERNAL "")
set(SPIRV_CROSS_ENABLE_C_API    OFF CACHE INTERNAL "")
add_subdirectory(SPIRV-Cross)
