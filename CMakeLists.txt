PROJECT(hts_ue1)

include_directories(include)
link_libraries(boost_serialization)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

ADD_EXECUTABLE(client src/networkbase.cpp src/client/client.cpp src/client/client_main.cpp)
ADD_EXECUTABLE(server src/networkbase.cpp src/server/server.cpp src/server/server_main.cpp)

