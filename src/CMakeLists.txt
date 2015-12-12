add_library(${PROJECT_NAME} dice.cpp yaht/player.cpp yaht/scoresheet.cpp)


set(${PROJECT_NAME}_HEADERS
	dice.h
)

set(${PROJECT_NAME}_YAHT_HEADERS
  yaht/constants.h
  yaht/player.h
  yaht/scoresheet.h
)

install(FILES ${${PROJECT_NAME}_HEADERS} DESTINATION "${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}")

install(FILES ${${PROJECT_NAME}_YAHT_HEADERS} DESTINATION "${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}/yaht")

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
