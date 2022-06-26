set(IM_HEADERS
    ByteBuf.h
    QIM.h
    IMGlobalStatic.h
)

set(IM_SRS
    ByteBuf.cpp
    QIM.cpp
    IMGlobalStatic.cpp
    ./proto/result.pb.h ./proto/result.pb.cc
    ./proto/message.pb.h ./proto/message.pb.cc
    ./proto/online.pb.h ./proto/online.pb.cc
    ./proto/session.pb.h ./proto/session.pb.cc
    ./proto/team.pb.h ./proto/team.pb.cc
    ./proto/user.pb.h ./proto/user.pb.cc
    ./proto/friends.pb.h ./proto/friends.pb.cc
)

add_library(IM STATIC ${IM_SRS})

install(TARGETS IM LIBRARY DESTINATION lib)
install(FILES ${IM_HEADERS} DESTINATION include/${CMAKE_PROJECT_NAME}/im)

target_link_libraries(IM
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::WebSockets
    Qt${QT_VERSION_MAJOR}::Concurrent
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(${CMAKE_PROJECT_NAME}
            ${THIRD_DIR_PATH}/protobuf/lib/win64/debug/libprotobufd.lib
            )
endif()

target_include_directories(
    IM SYSTEM PUBLIC
    ${THIRD_DIR_PATH}/protobuf/include
)
