find_package(GTest CONFIG REQUIRED)

include(GoogleTest)

file(GLOB files "*.cpp")

foreach(_file ${files})
  get_filename_component(file_basename ${_file} NAME_WE)
  add_executable(${file_basename} ${_file})
  target_link_libraries(${file_basename} PRIVATE GTest::gtest_main
                                                 _core_internal)
  add_custom_command(
    TARGET ${file_basename}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${7zip_locatioin}
            $<TARGET_FILE_DIR:${file_basename}>;
    COMMENT "Sync 7zip runtime to build path.")
  target_compile_definitions(
    ${file_basename}
    PRIVATE LIB_7ZIP_DIR="$<TARGET_FILE_DIR:${file_basename}>"
    PRIVATE TESTS_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
  warn_target(${file_basename})
  harden_target(${file_basename})
  sanitize_target(${file_basename})
  target_code_coverage(${file_basename} ALL)
  gtest_discover_tests(${file_basename})
endforeach()
