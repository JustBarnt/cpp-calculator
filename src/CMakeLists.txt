# Set up our executable
file(GLOB_RECURSE sources "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_executable(calculator ${sources})

set(CALCULATOR_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/.bin")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set output directory
set_target_properties(calculator PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CALCULATOR_OUTPUT_PATH}")

# Set target includes
target_include_directories(calculator
    PUBLIC "${CMAKE_SOURCE_DIR}/include")
