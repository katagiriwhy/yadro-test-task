list( APPEND ${PROJECT_NAME}-includes
        ${CMAKE_CURRENT_LIST_DIR}/
        ${CMAKE_CURRENT_LIST_DIR}/time/
        ${CMAKE_CURRENT_LIST_DIR}/club/
        ${CMAKE_CURRENT_LIST_DIR}/event_handler/
        ${CMAKE_CURRENT_LIST_DIR}/scope_guard/
)

list( APPEND ${PROJECT_NAME}-sources
        ${CMAKE_CURRENT_LIST_DIR}/
        ${CMAKE_CURRENT_LIST_DIR}/time/time.cpp
        ${CMAKE_CURRENT_LIST_DIR}/club/club.cpp
        ${CMAKE_CURRENT_LIST_DIR}/event_handler/event_handler.cpp
        ${CMAKE_CURRENT_LIST_DIR}/scope_guard/scope_guard.cpp
)
