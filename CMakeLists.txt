cmake_minimum_required(VERSION 3.0.0)
project(Json VERSION 0.1.0)

include(CTest)
enable_testing()
set (src 
    main.cpp
    Libraries/String.cpp

    src/Json.cpp
    src/Interface.cpp
    src/JsonFactory.cpp
    src/Interface.cpp
    
    src/JsonCreators/JsonCreator.cpp
    src/JsonCreators/NullCreator.cpp
    src/JsonCreators/BoolCreator.cpp
    src/JsonCreators/IntCreator.cpp
    src/JsonCreators/FloatCreator.cpp
    src/JsonCreators/StringCreator.cpp
    src/JsonCreators/ObjectCreator.cpp
    src/JsonCreators/ListCreator.cpp

    src/JsonChildren/JsonNull.cpp
    src/JsonChildren/JsonBool.cpp
    src/JsonChildren/JsonInt.cpp
    src/JsonChildren/JsonFloat.cpp
    src/JsonChildren/JsonString.cpp
    src/JsonChildren/JsonObject.cpp
    src/JsonChildren/JsonList.cpp
)

add_executable(Json ${src})
target_include_directories(Json PUBLIC 
                        Libraries/ 
                        Headers 
                        Headers/JsonChildren/
                        Headers/JsonCreators/
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
