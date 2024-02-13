cmake_minimum_required(VERSION 3.23)
project(LakeSuperiorStreams)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR})

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.0.1 # or a later release
)

FetchContent_Declare(
        rapidcsv
        GIT_REPOSITORY "https://github.com/d99kris/rapidcsv.git"
        GIT_TAG        v8.50
)

FetchContent_MakeAvailable(rapidcsv)
FetchContent_MakeAvailable(Catch2)
include_directories(${CMAKE_SOURCE_DIR})
add_library(DataBase
        lib/DataBase/Time.h
        lib/DataBase/DataManager.cpp
        lib/DataBase/DataSet.cpp
        lib/DataBase/DataSetBuilder.cpp
        lib/DataBase/Datum.cpp
        lib/DataBase/IDataProcessor.h
        lib/DataBase/CSVProcessor.cpp
        lib/DataBase/QueryManager.cpp
)

target_link_libraries(DataBase rapidcsv)

add_executable(LakeSuperiorStreams main.cpp)
target_link_libraries(LakeSuperiorStreams PRIVATE DataBase)

add_executable(tests
        tests/test01_Variance.cpp
        tests/test00_IDataProcessor.cpp
        tests/test_getTime.cpp
        tests/test01_Variance.cpp
        tests/test01_SearchByTime.cpp
        tests/test_TimeSeries.cpp
        tests/test_DataSet.cpp
        tests/test_DataSetBuilder.cpp
)

target_link_libraries(tests
        Catch2::Catch2WithMain
        rapidcsv
        DataBase
)


# doxygen enabler
find_package(Doxygen OPTIONAL_COMPONENTS dot)
if (DOXYGEN_FOUND)

    set(DOXYGEN_CALLER_GRAPH YES)
    set(DOXYGEN_CALL_GRAPH YES)
    set(DOXYGEN_EXTRACT_ALL YES)

    doxygen_add_docs(docs ${PROJECT_SOURCE_DIR})
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

