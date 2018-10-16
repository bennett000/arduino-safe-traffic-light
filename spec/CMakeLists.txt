###############################################################################
# Unit test setup
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

find_package(Check REQUIRED)
include_directories(${CHECK_INCLUDE_DIRS})
link_directories(${CHECK_LIBRARY_DIRS})

set(TEST_SOURCES
  tests.c
  state-machine.spec.c
  traffic-light-circuit.spec.c
)

# I wonder howto use arrays in cmake :/
add_executable(check_trafficLight ${TEST_SOURCES})
target_link_libraries(check_trafficLight trafficLight ${CHECK_LIBRARIES})
