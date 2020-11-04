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
        GIT_TAG 0.0.4
)
FetchContent_GetProperties(
        json
)
FetchContent_GetProperties(
        gmd5hash
)

if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
if(NOT gmd5hash_POPULATED)
    FetchContent_Populate(gmd5hash)
    add_subdirectory(${gmd5hash_SOURCE_DIR} ${gmd5hash_BINARY_DIR})
endif()



macro(print_all_variables)
    message(STATUS "print_all_variables------------------------------------------{")
    get_cmake_property(_variableNames VARIABLES)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach()
    message(STATUS "print_all_variables------------------------------------------}")
endmacro()
print_all_variables()

add_executable(cpddeployer main.cpp)
target_include_directories(cpddeployer PUBLIC ${gmd5hash_SOURCE_DIR})
target_link_libraries(cpddeployer PRIVATE nlohmann_json::nlohmann_json gmd5hash)