# Set up our executable
file(GLOB_RECURSE sources "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_executable(calculator ${sources})

include(FetchContent)

fetchcontent_declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG        e3ddede6c4ee818825c4e5a6dfa1d384860c27d9) # 11.1.1
fetchcontent_makeavailable(fmt)

target_link_libraries(calculator fmt::fmt)

set(CALCULATOR_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/.bin")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set output directory
set_target_properties(calculator PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CALCULATOR_OUTPUT_PATH}")

# Set target includes
target_include_directories(calculator
    PUBLIC "${CMAKE_SOURCE_DIR}/include")
