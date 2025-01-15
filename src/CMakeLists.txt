# Set up our executable
SET(sources
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/calculator.cpp"
)

ADD_EXECUTABLE(calculator ${sources})

INCLUDE(fetchcontent)

FETCHCONTENT_DECLARE(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG        e3ddede6c4ee818825c4e5a6dfa1d384860c27d9
) # 11.1.1

FETCHCONTENT_MAKEAVAILABLE(fmt)

TARGET_LINK_LIBRARIES(calculator fmt::fmt)

TARGET_COMPILE_OPTIONS(calculator PRIVATE -std=c++20)
SET(CALCULATOR_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/.bin")

# Set output directory
SET_TARGET_PROPERTIES(calculator PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CALCULATOR_OUTPUT_PATH}"
    CMAKE_CXX_STANDARD 20
    CMAKE_CXX_STANDARD_REQUIRED on
)

# Set target includes
TARGET_INCLUDE_DIRECTORIES(calculator
    PRIVATE "${CMAKE_SOURCE_DIR}/include")
