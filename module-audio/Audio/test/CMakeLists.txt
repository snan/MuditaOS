
# audio tests
add_catch2_executable(
    NAME
        audio-test
    SRCS
        unittest_audio.cpp
    LIBS
        module-audio
)

add_gtest_executable(
    NAME
        audio-stream
    SRCS
        unittest_stream.cpp
    LIBS
        module-audio
)

add_gtest_executable(
    NAME
        audio-misc
    SRCS
        unittest.cpp
        unittest_format.cpp
        unittest_transcode.cpp
        TestEndpoint.cpp
        TestStream.cpp
    LIBS
        module-audio
)

add_catch2_executable(
    NAME
        audio-volume-scaler
    SRCS
        unittest_scaler.cpp
    LIBS
        module-audio
)

add_catch2_executable(
    NAME
        audio-equalizer
    SRCS
        unittest_equalizer.cpp
    LIBS
        module-audio
        module-utils
)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/testfiles" DESTINATION "${CMAKE_BINARY_DIR}")
