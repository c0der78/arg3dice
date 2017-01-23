
add_executable(${TEST_PROJECT_NAME} main.test.cpp dice.test.cpp yaht/player.test.cpp yaht/scoresheet.test.cpp)

target_include_directories(${TEST_PROJECT_NAME} SYSTEM PUBLIC vendor/bandit PUBLIC ${PROJECT_SOURCE_DIR}/src)

target_link_libraries (${TEST_PROJECT_NAME} ${PROJECT_NAME})

