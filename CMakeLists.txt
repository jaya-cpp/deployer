cmake_minimum_required(VERSION 3.16)
project(cpddeployer CXX)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_VERBOSE_MAKEFILE TRUE)


include(FetchContent)
FetchContent_Declare(
        json
        GIT_REPOSITORY git@github.com:ArthurSonzogni/nlohmann_json_cmake_fetchcontent
        GIT_TAG v3.9.1
)
FetchContent_Declare(
        gmd5hash
        GIT_REPOSITORY git@github.com:jaya-cpp/super-duper-md5-hash.git
        GIT_TAG 0.0.1
)
FetchContent_GetProperties(
        json
)

if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
FetchContent_MakeAvailable(gmd5hash)

add_executable(cpddeployer main.cpp)
target_link_libraries(cpddeployer PRIVATE nlohmann_json::nlohmann_json)