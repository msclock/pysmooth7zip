set(PYBIND11_FINDPYTHON ON)

find_package(7zip CONFIG REQUIRED)
find_package(pybind11 CONFIG REQUIRED)
find_package(unofficial-bit7z CONFIG REQUIRED)

# The internal target will not be installed and only act as requirements for
# main and tests internally
set(target_name_internal _core_internal)

file(GLOB_RECURSE internal_srcs "src/*.cpp")
file(GLOB_RECURSE internal_hdrs "include/*.hpp")

list(FILTER internal_srcs EXCLUDE REGEX "pybind.cpp")

add_library(${target_name_internal} OBJECT)
warn_target(${target_name_internal})
harden_target(${target_name_internal})
sanitize_target(${target_name_internal})
target_code_coverage(${target_name_internal} ALL)

generate_git_header(VERSION_NAMESPACE_PREFIX _core)

target_sources(${target_name_internal} PRIVATE ${internal_srcs}
                                               ${internal_hdrs})

target_include_interface_directories(
  ${target_name_internal} ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_BINARY_DIR}/git_version)

target_link_libraries(${target_name_internal} PUBLIC 7zip::7zip
                                                     unofficial::bit7z::bit7z64)

# The main target only contains main logits. Here it is recommended to put the
# parts that need to be verified and tested in the target target_name_internal
set(target_name _core)

pybind11_add_module(${target_name} MODULE src/pybind.cpp)
warn_target(${target_name})
harden_target(${target_name})
sanitize_target(${target_name})
target_code_coverage(${target_name} ALL)

target_link_libraries(${target_name} PRIVATE ${target_name_internal})

if(CMAKE_BUILD_TYPE STREQUAL Debug)
  get_target_property(7zip_locatioin 7zip::7zip IMPORTED_LOCATION_DEBUG)
else()
  get_target_property(7zip_locatioin 7zip::7zip IMPORTED_LOCATION_RELEASE)
endif()

add_custom_command(
  TARGET ${target_name}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${7zip_locatioin}
          $<TARGET_FILE_DIR:${target_name}>;
  COMMENT "Sync 7zip runtime lib to build path.")

install(FILES ${7zip_locatioin} DESTINATION ${SKBUILD_PROJECT_NAME})

install(TARGETS ${target_name} DESTINATION ${SKBUILD_PROJECT_NAME})

install_dependency(TARGETS ${target_name} INSTALL_SYSTEM_LIBS
                   DEPENDS_DESTINATION ${SKBUILD_PROJECT_NAME})

if(BUILD_TESTING)
  add_test_subdirectory(tests)
endif()
