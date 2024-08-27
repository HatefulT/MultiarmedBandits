cmake_minimum_required(VERSION 3.0)
project(SteadyBandits)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MY_HEADER_FILES
	
)

file(GLOB MY_SOURCE_FILES
  "src/*.cpp"
  "src/*.hpp"
)

add_executable(SteadyBandits
	${MY_HEADER_FILES}
	${MY_SOURCE_FILES}
)

target_include_directories(SteadyBandits PUBLIC
  src/
)
