find_package(7zip CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

set(target_name smooth7zip)

add_library(${target_name} INTERFACE)

target_include_interface_directories(
  ${target_name} ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_BINARY_DIR}/git/include)

target_link_libraries(${target_name} INTERFACE 7zip::7zip spdlog::spdlog)

install_target(
  NAME
  ${target_name}
  VERSION
  ${CMAKE_PROJECT_VERSION}
  TARGETS
  ${target_name}
  INCLUDES
  ${CMAKE_CURRENT_SOURCE_DIR}/include/smooth7zip/
  ${CMAKE_BINARY_DIR}/git/include/
  LICENSE_FILE_LIST
  ${CMAKE_SOURCE_DIR}/LICENSE
  DEPENDENCIES
  7zip::7zip
  spdlog::spdlog)

if(BUILD_TESTING)
  add_subdirectory(tests)
endif()
