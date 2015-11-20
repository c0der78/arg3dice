
add_executable(arg3dice_test arg3.test.cpp dice.test.cpp yaht/player.test.cpp yaht/scoresheet.test.cpp)

include_directories(SYSTEM vendor/bandit ../src)

target_link_libraries (arg3dice_test arg3dice)

