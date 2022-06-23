add_subdirectory(ui)
add_subdirectory(im)

set(OPENSSL_BIN
        ${THIRD_DIR_PATH}/openssl/bin/win64/libcrypto-1_1-x64.dll
        ${THIRD_DIR_PATH}/openssl/bin/win64/libssl-1_1-x64.dll
        )

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(FRAMELESS_BIN
            ${THIRD_DIR_PATH}/frameless/bin/win64/debug/FramelessHelperd.dll
            )
    set(GLOG_BIN
            ${THIRD_DIR_PATH}/glog/bin/win64/debug/glogd.dll
            )
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(FRAMELESS_BIN
            ${THIRD_DIR_PATH}/frameless/bin/win64/release/FramelessHelper.dll
            )
    set(GLOG_BIN
            ${THIRD_DIR_PATH}/glog/bin/win64/release/glog.dll
            )
endif ()

install(FILES ${OPENSSL_BIN} DESTINATION bin)
install(FILES ${FRAMELESS_BIN} DESTINATION bin)
install(FILES ${GLOG_BIN} DESTINATION bin)
