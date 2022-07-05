set(UILibrary_SRS
        main.cpp
        MainWindow.cpp
        QUIHelper.cpp
        QLogHelper.cpp
        GlobalStatic.cpp
        LoginController.cpp
        EmojiModel.cpp
        TextDocument.cpp
        SessionController.cpp
        MessageController.cpp
        )

set(UILibrary_HEADERS
        MainWindow.h
        QUIHelper.h
        QLogHelper.h
        GlobalStatic.h
        LoginController.h
        EmojiModel.h
        TextDocument.h
        SessionController.h
        MessageController.h
        )

set(UILibrary_RCC
        res/qml.qrc
        )

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_executable(${CMAKE_PROJECT_NAME} WIN32 ${UILibrary_SRS} ${UILibrary_RCC})
#    add_custom_command(TARGET ${PROJECT_NAME}
#            POST_BUILD
#            COMMAND ${DEPLOYQT_EXECUTABLE} "$<TARGET_FILE:${PROJECT_NAME}>"
#            --$<LOWER_CASE:$<CONFIG>> --qmldir ${CMAKE_SOURCE_DIR}
#            )
else()
    add_executable(${CMAKE_PROJECT_NAME} ${UILibrary_SRS} ${UILibrary_RCC})
endif()

install(FILES ${UILibrary_HEADERS} DESTINATION include/${CMAKE_PROJECT_NAME}/ui)

target_link_libraries(${CMAKE_PROJECT_NAME}
        IM
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Quick
        Qt${QT_VERSION_MAJOR}::QuickControls2
        )

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(${CMAKE_PROJECT_NAME}
            ${THIRD_DIR_PATH}/frameless/lib/win64/debug/FramelessHelperd.lib
            ${THIRD_DIR_PATH}/glog/lib/win64/debug/glogd.lib
            ${THIRD_DIR_PATH}/hotkey/lib/win64/debug/qhotkeyd.lib
            )
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_link_libraries(${CMAKE_PROJECT_NAME}
            ${THIRD_DIR_PATH}/frameless/lib/win64/release/FramelessHelper.lib
            ${THIRD_DIR_PATH}/glog/lib/win64/release/glog.lib
            ${THIRD_DIR_PATH}/hotkey/lib/win64/release/qhotkey.lib
            )
endif()

target_include_directories(
        ${CMAKE_PROJECT_NAME} SYSTEM PUBLIC
        ${CMAKE_SOURCE_DIR}/src/ui
        ${CMAKE_SOURCE_DIR}/src/im
        ${THIRD_DIR_PATH}/frameless/include
        ${THIRD_DIR_PATH}/glog/include
        ${THIRD_DIR_PATH}/hotkey/include
)
