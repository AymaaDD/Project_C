cmake_minimum_required(VERSION 3.0.0)
set(project_name "PROJECT_1")
project(${project_name} VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(${project_name} main.c edid.c)

set_target_properties(
  ${project_name} PROPERTIES
  C_STANDARD 11
  C_STANDARD_REQUIRED ON
  COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
