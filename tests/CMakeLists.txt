
add_executable(${PROJECT_NAME}_test main.test.cpp dice.test.cpp yaht/player.test.cpp yaht/scoresheet.test.cpp)

include_directories(SYSTEM vendor/bandit ${PROJECT_SOURCE_DIR}/src)

target_link_libraries (${PROJECT_NAME}_test ${PROJECT_NAME})

