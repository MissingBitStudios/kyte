macro(setup_test ARG_NAME)
    cmake_parse_arguments(ARG "" "" "SOURCES" ${ARGN})

    if(NOT ARG_SOURCES)
      message(FATAL_ERROR "setup_test: You must provide sources.")
    endif()

    add_executable(${ARG_NAME} ${ARG_SOURCES})
    target_link_libraries(${ARG_NAME} gtest gtest_main kyte)
    add_test(${ARG_NAME} ${ARG_NAME})
    set_target_properties(${ARG_NAME} PROPERTIES FOLDER "kyte/test")
endmacro()

add_subdirectory(kyte)
