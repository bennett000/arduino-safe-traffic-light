###############################################################################
# Mock setup
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

set(MOCK_SOURCES
  mock.c
)

add_executable(mock ${MOCK_SOURCES})
target_link_libraries(mock trafficLight)
